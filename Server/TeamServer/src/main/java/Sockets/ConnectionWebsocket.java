package Sockets;

import Classes.DBConnector;
import DataModels.Group;
import DataModels.User;
import org.json.JSONObject;
import javax.websocket.*;
import javax.websocket.server.ServerEndpoint;
import java.sql.ResultSet;
import java.util.ArrayList;

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
                    if (rs.getString("password").equals(key)) {
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
                                Group group = new Group(
                                        groupId,
                                        rs.getString("name")
                                );
                                group.users.add(user);
                                groups.add(group);
                            }
                        }
                    }
                    break;
                case "group_message":
                    groupByUserSession(session).sendGroupMessage(message);
                    break;
            }
        } catch (Exception ex) {

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
}