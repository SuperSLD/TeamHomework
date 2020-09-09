package Sockets.MessageReply;

import Classes.DBConnector;
import DataModels.Group;
import DataModels.User;
import Sockets.ConnectionWebsocket;
import org.json.JSONObject;

import javax.websocket.Session;
import java.sql.ResultSet;

/**
 *  Ответ на запрос подключения пользователя.
 */
@ReplyType(messageType = "connect_user")
public class ConnectMessageReply implements MessageReply {
    @Override
    public void reply(ConnectionWebsocket cw, String message, Session session) throws Exception {
        JSONObject messageObject = new JSONObject(message);

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
                for(Group group : ConnectionWebsocket.getGroups()) {
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
                        ConnectionWebsocket.getGroups().add(group);
                    }
                }
                ConnectionWebsocket.sendLastMessages(session, groupId, messageObject.getString("timeCode"));
            }
        }
        System.out.println("create user");
    }
}
