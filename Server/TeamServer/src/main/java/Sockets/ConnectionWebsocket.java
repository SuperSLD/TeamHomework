package Sockets;

import Classes.DBConnector;
import DataModels.Group;
import DataModels.User;
import org.json.JSONObject;
import javax.websocket.*;
import javax.websocket.server.ServerEndpoint;
import java.sql.ResultSet;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;

/**
 * Вебсокет для обработки потока данных от
 * клментов и занесения изменений в базу данных.
 *
 * @author Solyanoy Leonid(solyanoy.leonid@gmail.com)
 */
@ServerEndpoint("/connection")
public class ConnectionWebsocket {
    private static ArrayList<Group> groups = new ArrayList<>();

    @OnOpen
    public void onOpen(Session session) {
        System.out.println("onOpen::" + session.getId());
    }

    @OnClose
    public void onClose(Session session) {
        System.out.println("onClose::" +  session.getId());
        for (Group group : groups) {
            User user = group.findUserBySession(session);
            if (user != null) {
                group.users.remove(user);
                if (group.users.size() == 0) {
                    groups.remove(group);
                }
            }
        }
    }

    @OnMessage
    public void onMessage(String message, Session session) {
        try {
            JSONObject messageObject = new JSONObject(message);
            switch (messageObject.getString("type")) {
                case "connect_user":
                    int user_id = Integer.parseInt(messageObject.getString("id"));
                    String key = messageObject.getString("key");

                    ResultSet rs = DBConnector.executeQuery(
                            "SELECT password, name, lastname, email FROM users WHERE id=" + user_id);
                    //Проверка пользователя.
                    if (rs.next() && rs.getString("password").equals(key)) {
                        User user = new User(
                                user_id,
                                rs.getString("name"),
                                rs.getString("lastname"),
                                rs.getString("email"),
                                key
                        );
                        user.setSession(session);
                        //Определение группы пользователя
                        rs = DBConnector.executeQuery(
                                "SELECT group_id FROM user_group WHERE user_id=" + user_id);
                        if (rs.next()) {
                            //Поиск группы пользователя
                            int groupId = Integer.parseInt(rs.getString("group_id"));
                            boolean newGroup = true;
                            for(Group group : groups) {
                                if (group.getId() == groupId) {
                                    newGroup = false;
                                    group.users.add(user);
                                    break;
                                }
                            }
                            //Создание группы
                            if (newGroup) {
                                rs = DBConnector.executeQuery(
                                        "SELECT name FROM team_groups WHERE id=" + groupId);
                                if (rs.next()) {
                                    Group group = new Group(
                                            groupId,
                                            rs.getString("name")
                                    );
                                    group.users.add(user);
                                    groups.add(group);
                                }
                            }
                            sendLastMessages(session, groupId, messageObject.getString("timeCode"));
                        }
                    }
                    System.out.println("create user");
                    break;
                case "group_message":
                    Group currentGroup = groupByUserSession(session);
                    if (currentGroup != null) {
                        User user = currentGroup.findUserBySession(session);

                        String date = new SimpleDateFormat("yyyy.MM.dd HH:mm:ss").format(Calendar.getInstance().getTime());

                        DBConnector.executeUpdate("INSERT messages VALUE(0, " + currentGroup.getId() + ", "
                                + user.getId() + ", '" + messageObject.getString("message_type") + "', '"
                                + messageObject.getString("message") + "', '"
                                + date + "', '" + messageObject.getString("author") + "')");

                        currentGroup.sendGroupMessage(new JSONObject(message).put("time", date).toString());
                    }
                    break;
            }
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    @OnError
    public void onError(Throwable t) {
        System.out.println("onError::" + t.getMessage());
    }

    /**
     * Поиск группы по сессии пользователя.
     * @param session сессия пользователя.
     * @return группа.
     *
     * @author Solyanoy Leonid(solyanoy.leonid@gmail.com)
     */
    private Group groupByUserSession(Session session) {
        for (Group group : groups) {
            if (group.findUserBySession(session) != null) {
                return group;
            }
        }
        return null;
    }

    /**
     * Отправка занесенных в базу сообщений.
     * @param session сессия пользователя.
     * @param groupId id группы.
     *
     * @author Solyanoy Leonid(solyanoy.leonid@gmail.com)
     */
    private void sendLastMessages(Session session, int groupId, String timeCode) {
        try {
            ResultSet rs = DBConnector.executeQuery(
                    "SELECT text_message, time_send, author, type FROM messages WHERE group_id=" + groupId
                            + " and time_send > '"+timeCode+"'  ORDER BY time_send"
            );
            while (rs.next()) {
                JSONObject message = new JSONObject();
                message.put("message", rs.getString("text_message"));
                message.put("type", "group_message");
                message.put("message_type",rs.getString("type"));
                message.put("author", rs.getString("author"));
                message.put("time", rs.getString("time_send"));
                System.out.println(message.toString());
                session.getBasicRemote().sendText(message.toString());
            }
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }
}