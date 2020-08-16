package Sockets.MessageReply;

import Classes.DBConnector;
import DataModels.Group;
import DataModels.User;
import Sockets.ConnectionWebsocket;
import org.json.JSONObject;

import javax.websocket.Session;
import java.text.SimpleDateFormat;
import java.util.Calendar;

/**
 *  Ответ на полученное груповое сообщение.
 */
@ReplyType(messageType = "group_message")
public class GroupMessageReply implements MessageReply {
    @Override
    public void reply(ConnectionWebsocket cw, String message, Session session) throws Exception {
        JSONObject messageObject = new JSONObject(message);

        Group currentGroup = ConnectionWebsocket.groupByUserSession(session);
        if (currentGroup != null) {
            User user = currentGroup.findUserBySession(session);

            String date = new SimpleDateFormat("yyyy.MM.dd HH:mm:ss").format(Calendar.getInstance().getTime());

            DBConnector.executeUpdate("INSERT messages VALUE(0, " + currentGroup.getId() + ", "
                    + user.getId() + ", '" + messageObject.getString("message_type") + "', '"
                    + messageObject.getString("message") + "', '"
                    + date + "', '" + messageObject.getString("author") + "')");

            currentGroup.sendGroupMessage(new JSONObject(message).put("time", date).toString());
        }
    }
}
