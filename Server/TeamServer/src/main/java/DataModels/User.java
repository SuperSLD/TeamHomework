package DataModels;

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


}
