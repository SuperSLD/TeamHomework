package Servlets;

import Classes.DBConnector;
import org.json.JSONObject;


import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.URLEncoder;
import java.security.MessageDigest;
import java.sql.ResultSet;
import java.sql.SQLException;

/**
 * Сервлет для редактирования базы данных.
 *
 * @author Solyanoy Leonid(solyanoy.leonid@gmail.com)
 */
public class DBEditorServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        req.getRequestDispatcher("dbeditor.jsp").forward(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        resp.setCharacterEncoding("UTF-8");
        req.setCharacterEncoding("UTF-8");

        String act = req.getParameter("act");
        JSONObject jsonObject = new JSONObject();
        System.out.println(act);

        try {
            if (act != null) switch (act) {
                case "create_user":
                    if (req.getParameter("name") != null && req.getParameter("name").length() > 2 &&
                            req.getParameter("lastname") != null && req.getParameter("lastname").length() > 2 &&
                            req.getParameter("email") != null && req.getParameter("email").length() > 2 &&
                            req.getParameter("password") != null && req.getParameter("password").length() > 2) {

                        MessageDigest messageDigest = MessageDigest.getInstance("SHA-256");
                        messageDigest.update(req.getParameter("password").getBytes());
                        String encryptedPassword = new String(messageDigest.digest());
                        encryptedPassword = URLEncoder.encode(encryptedPassword, "UTF-8");

                        System.out.println("password " +req.getParameter("password"));
                        System.out.println("password sha256 " + encryptedPassword);

                        ResultSet rs = DBConnector.executeQuery("SELECT id FROM users WHERE email='"+req.getParameter("email")+"'");
                        if (!rs.next()) {
                            DBConnector.executeUpdate(
                                    "INSERT users VALUE (0, '" + req.getParameter("name") +
                                            "', '" + req.getParameter("lastname") + "'," +
                                            " '" + req.getParameter("email") + "', '" + encryptedPassword + "')"
                            );
                            jsonObject.put("err_code", "0");
                            jsonObject.put("err_message", "Пользователь успешно добавлен.");
                            jsonObject.put("err_local", "все норм");
                        } else {
                            jsonObject.put("err_code", "1");
                            jsonObject.put("err_message", "Почта уже используется другим пользователем.");
                            jsonObject.put("err_local", "все норм, ошибка не в коде");
                        }
                    } else {
                        jsonObject.put("err_code", "2");
                        jsonObject.put("err_message", "Данные введены некорректно.");
                        jsonObject.put("err_local", "все норм, ошибка не в коде");
                    }
                    break;
            }
        } catch (Exception ex) {
            ex.printStackTrace();
            jsonObject.put("err_code", "3");
            jsonObject.put("err_message", "Ошибка на сервере.");
            jsonObject.put("err_local", ex.getMessage() + " " + ex.getLocalizedMessage());
        }
        PrintWriter writer = resp.getWriter();
        writer.print(jsonObject.toString());
    }
}
