package DataModels;

import javax.websocket.Session;

/**
 * Класс для обраьотки данных пользвателя.
 *
 * @author Solyanoy Leonid(solyanoy.leonid@gmail.com)
 */
public class User {
    private int id;
    private String name;
    private String lastname;
    private String email;
    private String password;

    private Session session;
    private int groupId;

    public User(int id,
                String name,
                String lastname,
                String email,
                String password) {
        this.id = id;
        this.name = name;
        this.lastname = lastname;
        this.email = email;
        this.password = password;
    }

    /**
     * Проверка на корректность ключа.
     * @param key ключ из сообщения.
     * @return верен ключ или нет
     */
    public boolean isCorrect(String key) {
        return key.equals(password);
    }

    public int getId() {
        return id;
    }

    public String getLastname() {
        return lastname;
    }

    public String getName() {
        return name;
    }

    public String getEmail() {
        return email;
    }

    public String getPassword() {
        return password;
    }

    public int getGroupId() {
        return groupId;
    }

    public Session getSession() {
        return session;
    }

    public void setSession(Session session) {
        this.session = session;
    }

    public void setGroupId(int groupId) {
        this.groupId = groupId;
    }
}
