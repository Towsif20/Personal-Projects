package sample;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class SignUpController {

    public Button back_button;
    private Main main;

    public void setMain(Main main) {
        this.main = main;
    }

    @FXML
    private TextField name_field;

    @FXML
    private TextField email_field;

    @FXML
    private TextField dob_field;

    @FXML
    private Button singupButton;

    @FXML
    private TextField gender_field;

    @FXML
    private PasswordField pass_field;

    @FXML
    void signUpAction(ActionEvent event)
    {

        String name = name_field.getText();

        String mail = email_field.getText();

        String dob = dob_field.getText();

        String gender = gender_field.getText();

        String pass = pass_field.getText();

        boolean found = false;

        Connection c = null;
        Statement statement = null;

        try
        {
            c = Main.createConnection();

            statement = c.createStatement();
            String sql = "select email from user_table where email = '" + mail + "'";
            ResultSet rs = statement.executeQuery(sql);


            if (rs.next())
            {
                found = true;
            }
            rs.close();
            statement.close();
            c.close();

        } catch (Exception e)
        {
            e.printStackTrace();
        }

        if (found)
        {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Alert!!");
            alert.setHeaderText("Incorrect input");
            alert.setContentText("The email is already used.");
            alert.showAndWait();
        }
        else
        {
            try
            {

                c = Main.createConnection();

                statement = c.createStatement();

                String sql = "insert into user_table (user_name, email, date_of_birth, gender, pass) " +
                        "values('" + name + "', '" + mail + "', to_date('" + dob + "','DD Mon YYYY'), '" + gender + "', '" + pass + "')";

                System.out.println(name);

                statement.executeUpdate(sql);

                ResultSet rs = statement.executeQuery("select * from user_table;");

                while (rs.next())
                {
                    System.out.println(rs.getInt("user_id"));
                }

                rs.close();

                statement.close();

                c.commit();

                c.close();

            } catch (SQLException e)
            {
                e.printStackTrace();
            }

        }
    }

    public void backAction(ActionEvent event)
    {
        try
        {
            main.showLoginPage();
        } catch (Exception e)
        {
            e.printStackTrace();
        }
    }
}