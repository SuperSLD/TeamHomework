package Sockets;

import org.json.JSONObject;
import javax.websocket.*;
import javax.websocket.server.ServerEndpoint;
import java.util.ArrayList;

@ServerEndpoint("/connection")
public class ConnectionWebsocket {
    private static  ArrayList<Session> connections = new ArrayList<>();
    private static Thread ping = new Thread(() -> {
        JSONObject jsonObject = new JSONObject();
        jsonObject.put("message", "test ping message");
        jsonObject.put("type", "ping");
        long pingCount = 0;
        while (true) {
            try {
                jsonObject.put("count", Long.toString(pingCount));
                pingCount++;
                for (Session session : connections) {
                    session.getBasicRemote().sendText(jsonObject.toString());
                }
                Thread.sleep(1000);
            } catch (Exception ex) {

            }
        }
    });

    @OnOpen
    public void onOpen(Session session) {
        System.out.println("onOpen::" + session.getId());
        connections.add(session);

        if (!ping.isAlive()) ping.start();
    }
    @OnClose
    public void onClose(Session session) {
        System.out.println("onClose::" +  session.getId());
        connections.remove(session);
    }

    @OnMessage
    public void onMessage(String message, Session session) {
    }

    @OnError
    public void onError(Throwable t) {
        System.out.println("onError::" + t.getMessage());
    }
}