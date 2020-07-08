package Classes;

import com.sun.mail.smtp.SMTPTransport;

import javax.mail.Message;
import javax.mail.Session;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeMessage;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.util.Date;
import java.util.Properties;
import java.util.Scanner;

/**
 * Отправка сообщений через почтовый сервер.
 * (Рабтает только при запуске приложения на основном сервере)
 *
 * @author Solyanoy Leonid(solyanoy.leonid@gmail.com)
 */
public class MailCreator {

    /**
     * Отправка сообщения.
     * @param email почта получателя.
     * @param subject тема сообщения.
     * @param data тело сообщения.
     */
    static void sendEmail(String email, String subject, String data) {
        ClassLoader classLoader = MailCreator.class.getClassLoader();

        InputStream inputStream = DBConnector.class.getResourceAsStream("/config.properties");
        Properties properties = new Properties();
        try {
            properties.load(inputStream);
        } catch (IOException e) {
            e.printStackTrace();
        }

        Session session = Session.getInstance(properties, null);
        Message msg = new MimeMessage(session);

        try {
            msg.setFrom(new InternetAddress(properties.getProperty("email.from")));
            msg.setRecipients(Message.RecipientType.TO,
                    InternetAddress.parse(email, false));
            /*msg.setRecipients("",
                    InternetAddress.parse(properties.getProperty("email.to.cc"), false));*/

            // subject
            msg.setSubject(subject);
            // content
            msg.setContent(data, "text/html");

            msg.setSentDate(new Date());
            SMTPTransport t = (SMTPTransport) session.getTransport("smtp");
            t.connect(properties.getProperty("mail.smtp.host"), "", "");
            t.sendMessage(msg, msg.getAllRecipients());

            System.out.println("Response: " + t.getLastServerResponse());

            t.close();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
