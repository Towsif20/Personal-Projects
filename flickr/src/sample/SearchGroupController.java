package sample;

import java.net.URL;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ResourceBundle;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;

public class SearchGroupController {

    int button_id;
    Main main;

    public void setMain(Main main)
    {
        this.main = main;
    }

    public void setButton_id(int button_id)
    {
        this.button_id = button_id;
    }

    @FXML
    private ResourceBundle resources;

    @FXML
    private URL location;

    @FXML
    private Button group_button;

    @FXML
    void showGroupAction(ActionEvent event)
    {
        try
        {
            main.showGroup(button_id);
        } catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    @FXML
    void initialize() {
        Connection c = null;

        Statement statement = null;

        String s = "";

        try
        {
            c = Main.createConnection();

            statement = c.createStatement();

            String sql = "select * from group_table where group_id = "+button_id+";";

            ResultSet rs = statement.executeQuery(sql);


            while (rs.next())
            {
                System.out.println("is it here?");
                //owner_field.setText(rs.getString("user_name"));
                group_button.setText(rs.getString("group_name"));
            }

            rs.close();

            statement.close();

            c.close();

        }catch (Exception e)
        {
            e.printStackTrace();
        }

        System.out.println("working? "+s);

    }


}
