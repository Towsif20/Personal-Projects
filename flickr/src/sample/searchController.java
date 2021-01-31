package sample;

import java.io.IOException;
import java.net.URL;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ResourceBundle;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;

public class searchController
{
    Main main;

    int button_id;

    public void setButton_id(int button_id)
    {
        this.button_id = button_id;
    }

    public void setMain(Main main)
    {
        this.main = main;
    }

    @FXML
    private Button home_button;

    @FXML
    private ResourceBundle resources;

    @FXML
    private URL location;

    @FXML
    private Button profile_button;

    @FXML
    void showProfile(ActionEvent event)
    {
        try
        {
            main.showProfilePage(button_id);
        } catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    @FXML
    void initialize()
    {
        //assert profile_button != null : "fx:id=\"profile_button\" was not injected: check your FXML file 'searchpage.fxml'.";

        Connection c = null;

        Statement statement = null;

        String s = "";

        try
        {
            c = Main.createConnection();

            statement = c.createStatement();

            String sql = "select * from user_table where user_id = "+button_id+";";

            ResultSet rs = statement.executeQuery(sql);


            while (rs.next())
            {
                System.out.println("is it here?");
                //owner_field.setText(rs.getString("user_name"));
                profile_button.setText(rs.getString("user_name"));
            }

            rs.close();

            statement.close();

            c.close();

        }catch (Exception e)
        {
            e.printStackTrace();
        }

        System.out.println("working? "+s);

        //profile_button.setText(s);
    }

    public void goHome(ActionEvent event)
    {
        try
        {
            main.showHomePage();
        } catch (IOException e)
        {
            e.printStackTrace();
        }
    }
}
