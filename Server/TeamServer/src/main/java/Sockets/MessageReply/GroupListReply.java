package Sockets.MessageReply;

import Sockets.ConnectionWebsocket;

import javax.websocket.Session;

@ReplyType(messageType = "group_list")
public class GroupListReply implements MessageReply {
    @Override
    public void reply(ConnectionWebsocket cw, String message, Session session) throws Exception {
        
    }
}
