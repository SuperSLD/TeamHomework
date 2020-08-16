package Sockets;

import Classes.DBConnector;
import DataModels.Group;
import DataModels.User;
import Sockets.MessageReply.MessageReply;
import Sockets.MessageReply.ReplyType;
import org.json.JSONObject;
import javax.websocket.*;
import javax.websocket.server.ServerEndpoint;
import java.io.File;
import java.sql.ResultSet;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.HashMap;

/**
 * Вебсокет для обработки потока данных от
 * клментов и занесения изменений в базу данных.
 *
 * @author Solyanoy Leonid(solyanoy.leonid@gmail.com)
 */
@ServerEndpoint("/connection")
public class ConnectionWebsocket {
    private static ArrayList<Group> groups = new ArrayList<>();

    private static HashMap<String, MessageReply> replies = new HashMap<>();
    private static boolean isInit = false;

    /**
     * Инициализация сокета.
     */
    private static void init() {
        if (!isInit) {
            System.out.println("INITIALISATION WEBSOCKET STATIC OBJECT");
            isInit = true;
            File file = new File(
                    ConnectionWebsocket.class.getProtectionDomain().getCodeSource().getLocation().getPath()
                    + "/Sockets/MessageReply"
            );
            for(String fileName : file.list()) {
                System.out.println("Check class -> " + fileName);
                try {
                    Class<?> classData = Class.forName("Sockets.MessageReply." + fileName.replaceAll("\\.class", ""));
                    ReplyType replyType = classData.getAnnotation(ReplyType.class);
                    if (replyType != null) {
                        MessageReply reply = (MessageReply) classData.newInstance();
                        replies.put(replyType.messageType(), reply);
                        System.out.println("    .annotation load [" + replyType.messageType() + "]");
                    }
                } catch (Exception ex) {
                    ex.printStackTrace();
                }
            }
            System.out.println("MessageReply open [" + file.isDirectory() + "]");
        }
    }

    /**
     * Поиск классов MessageReply.
     */
    private static void findClassList(File file) {

    }

    @OnOpen
    public void onOpen(Session session) {
        init();
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
            MessageReply messageReply = replies.get(messageObject.getString("type"));

            if (messageReply != null) {
                messageReply.reply(this, message, session);
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
    public static Group groupByUserSession(Session session) {
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
    public static void sendLastMessages(Session session, int groupId, String timeCode) {
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

    /**
     * Получение текущего списка активных групп.
     * @return список групп.
     */
    public static ArrayList<Group> getGroups() {
        return groups;
    }
}