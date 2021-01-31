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
import javafx.scene.control.Label;

public class profileController {

    Main main;
    int id;

    public void setId(int id)
    {
        this.id = id;
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
    private Label owner_field;

    @FXML
    private Label photos_number;

    @FXML
    private Label follower_number;

    @FXML
    private Button follow_button;

    @FXML
    void followAction(ActionEvent event)
    {
        if(id == 0 || Main.user_id == id)
            return;

        Connection c = null;
        Statement statement = null;

        try
        {
            c = Main.createConnection();

            statement = c.createStatement();

            String sql = "select * from follow where follower_id = "+Main.user_id+ " and followed_id = "+id;

            ResultSet rs = statement.executeQuery(sql);

            if(!rs.next())
            {
                sql = "insert into follow(follower_id, followed_id) values(" + Main.user_id+ ","+id+");";

                statement.executeUpdate(sql);
            }

            else
            {
                sql = "delete from follow where follower_id = "+Main.user_id+ " and followed_id = "+id;

                statement.executeUpdate(sql);
            }

            rs.close();

            statement.close();

            c.commit();

            c.close();

        }catch (Exception e)
        {
            e.printStackTrace();
        }

        initialize();
    }

    @FXML
    void initialize()
    {
        Connection c = null;

        Statement statement = null;

        try
        {
            c = Main.createConnection();

            statement = c.createStatement();

            String sql = "select * from user_table where user_id = "+id+";";

            ResultSet rs = statement.executeQuery(sql);

            while (rs.next())
            {
                owner_field.setText(rs.getString("user_name"));
            }

            sql = "select count(*) from photos where owner_id = "+id;

            rs = statement.executeQuery(sql);

            while (rs.next())
            {
                photos_number.setText(rs.getString("count") + " photos");
            }

            sql = "select count(*) from follow where followed_id = "+id;

            rs = statement.executeQuery(sql);

            while (rs.next())
            {
                follower_number.setText(rs.getString("count") + " followers");
            }

            rs.close();

            statement.close();

            c.close();

        }catch (Exception e)
        {
            e.printStackTrace();
        }
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
