package DataModels;

import Classes.DBConnector;

import javax.websocket.Session;
import java.sql.ResultSet;
import java.util.ArrayList;

/**
 * Группа пользователей.
 *
 * @author Solyanoy Leonid(solyanoy.leonid@gmail.com)
 */
public class Group {
    private String name;
    private int id;
    public ArrayList<User> users;
    public ArrayList<Task> taskList;

    public Group(int id, String name) {
        this.name = name;
        this.id = id;
        this.users = new ArrayList<>();

        this.taskList = new ArrayList<>();

        try {
            ResultSet rs = DBConnector.executeQuery("SELECT id, type, status, text_task, author FROM task_list" +
                                                        "WHERE group_id = '"+this.id+"'");
            while (rs.next()) {
                Task task = new Task(
                        Integer.parseInt(rs.getString("id")),
                        rs.getString("status"),
                        rs.getString("content"),
                        rs.getString("author"),
                        rs.getString("type")
                );
                taskList.add(task);
            }
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    /**
     * Отправка группового сообщения каждому пользователю.
     * @param message текстовое сообщение.
     *
     * @author Solyanoy Leonid(solyanoy.leonid@gmail.com)
     */
    public void sendGroupMessage(String message) {
        for (User user : users) {
            try {
                user.getSession().getBasicRemote().sendText(message);
            } catch (Exception ex) { }
        }
    }

    /**
     * Поиск пользователя по websocket сессии.
     * @param session сессия.
     * @return пользователь.
     *
     * @author Solyanoy Leonid(solyanoy.leonid@gmail.com)
     */
    public User findUserBySession(Session session) {
        for (User user : users) {
            if (user.getSession().equals(session)) {
                return user;
            }
        }
        return null;
    }

    public String getName() {
        return name;
    }

    public int getId() {
        return id;
    }
}
