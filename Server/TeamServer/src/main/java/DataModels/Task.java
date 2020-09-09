package DataModels;

/**
 * Модель хранения задачи группы.
 */
public class Task {
    private int id;
    private String status;
    private String content;
    private String author;
    private String type;

    public Task(int id,
                String status,
                String content,
                String author,
                String type) {
        this.id = id;
        this.author = author;
        this.content = content;
        this.status = status;
        this.type = type;
    }
}
