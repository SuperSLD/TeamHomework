package Servlets;

import Classes.DBConnector;
import org.json.JSONObject;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.URLDecoder;
import java.net.URLEncoder;
import java.security.MessageDigest;
import java.sql.ResultSet;

/**
 * Авторизация пользователя в системме.
 * Проверка его данных.
 *
 * @author Solyanoy Leonid(solyanoy.leonid@gmail.com)
 */
public class AuthorisationServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        req.setCharacterEncoding("UTF-8");
        resp.setCharacterEncoding("UTF-8");
        resp.setContentType("text/json; charset=windows-1251");

        JSONObject jsonObject = new JSONObject();
        PrintWriter writer = resp.getWriter();

        try {
            ResultSet rs = DBConnector.executeQuery(
                    "SELECT id, name, lastname, email, password " +
                            "FROM users WHERE email='"+req.getParameter("email")+"'");
            if (rs.next()) {
                MessageDigest messageDigest = MessageDigest.getInstance("SHA-256");
                messageDigest.update(req.getParameter("password").getBytes());
                String encryptedPassword = new String(messageDigest.digest());
                encryptedPassword = URLEncoder.encode(encryptedPassword, "UTF-8");

                System.out.println("password " +req.getParameter("password"));
                System.out.println("password sha256 " + encryptedPassword);
                System.out.println("password sha256 " + rs.getString("password"));

                if (encryptedPassword.equals(rs.getString("password"))) {
                    jsonObject.put("errcode", "0");
                    jsonObject.put("id", rs.getString("id"));
                    jsonObject.put("name", URLDecoder.decode(rs.getString("name"), "UTF-8"));
                    jsonObject.put("lastname", URLDecoder.decode(rs.getString("lastname"), "UTF-8"));
                    jsonObject.put("email", rs.getString("email"));
                    jsonObject.put("password", encryptedPassword);
                    System.out.println("user connect: " + URLDecoder.decode(rs.getString("name"), "WINDOWS-1251") + " | "
                                    + rs.getString("lastname"));
                } else {
                    jsonObject.put("errcode", "2");
                    jsonObject.put("error_message", "invalid password");
                }
            } else {
                jsonObject.put("errcode", "1");
                jsonObject.put("error_message", "email not found");
            }
        } catch (Exception ex) {
            ex.printStackTrace();
            jsonObject.put("errcode", "3");
            jsonObject.put("error_message", "server error");
        }

        writer.print(jsonObject.toString());
    }
}
