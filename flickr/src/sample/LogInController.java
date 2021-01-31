package sample;

import java.io.IOException;
import java.net.URL;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ResourceBundle;
import java.util.Scanner;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;

public class LogInController {

    private Main main;

    public void setMain(Main main)
    {
        this.main = main;
    }

    @FXML
    private ResourceBundle resources;

    @FXML
    private URL location;

    @FXML
    private TextField email_field;

    @FXML
    private PasswordField password_field;

    @FXML
    private Button logInButton;

    @FXML
    private Button signUpButton;

    @FXML
    private Label message;

    @FXML
    void logInAction(ActionEvent event)
    {
        boolean success = false;

        String email = email_field.getText();
        String pass = password_field.getText();

        Statement stmt = null;
        Connection c = null;
        try {
            c = Main.createConnection();

            stmt = c.createStatement();

            ResultSet rs = stmt.executeQuery( "select user_id, user_name from user_table where email= '"+email+"' and pass='"+pass+"';" );

            if(rs.next())
            {
                success = true;

                if(email.compareTo("")==0 || pass.compareTo("")==0)
                    success = false;

                Main.user_id = rs.getInt("user_id");
                Main.userName = rs.getString("user_name");
            }

            System.out.println(Main.user_id);
                //success = true;

                //main.showHomePage();
//                String name = rs.getString("user_name");
                //System.out.println(name);

            rs.close();

            stmt.close();

            c.close();

        } catch (Exception e) {
            e.printStackTrace();
            System.err.println(e.getClass().getName()+": "+e.getMessage());
            System.exit(0);
        }
        //System.out.println("Opened database successfully");
        //System.out.println("log in");

        if(success)
        {
            try {
                main.showHomePage();
            } catch (Exception e) {
                e.printStackTrace();
            }
            //message.setText("flickr");
        }


        if(!success)
        {
            //Alertbox.display("flickr","log in failed");
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Alert!!");
            alert.setHeaderText("Incorrect input");
            alert.setContentText("The username and password you provided is not correct.");
            alert.showAndWait();
        }
    }

    @FXML
    void signUpAction(ActionEvent event)
    {
        try {
            main.showSignUpPage();
        } catch (Exception e) {
            e.printStackTrace();
        }

        System.out.println("sign up");
    }

    @FXML
    void initialize() {
        /*assert email_field != null : "fx:id=\"email_field\" was not injected: check your FXML file 'log in page.fxml'.";
        assert password_field != null : "fx:id=\"password_field\" was not injected: check your FXML file 'log in page.fxml'.";
        assert logInButton != null : "fx:id=\"logInButton\" was not injected: check your FXML file 'log in page.fxml'.";
        assert signUpButton != null : "fx:id=\"signUpButton\" was not injected: check your FXML file 'log in page.fxml'.";
*/
    }
}
