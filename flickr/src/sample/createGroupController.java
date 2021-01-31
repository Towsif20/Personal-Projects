package sample;

import java.io.IOException;
import java.net.URL;
import java.sql.Connection;
import java.sql.Statement;
import java.util.ResourceBundle;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;

public class createGroupController {

    Main main;

    public void setMain(Main main)
    {
        this.main = main;
    }

    @FXML
    private ResourceBundle resources;

    @FXML
    private URL location;

    @FXML
    private TextField GroupName_field;

    @FXML
    private Button create_button;

    @FXML
    private Button back_button;

    @FXML
    void createGroupAction(ActionEvent event)
    {
        String s = GroupName_field.getText();

        Connection c = null;

        Statement statement = null;

        try
        {
            c = Main.createConnection();

            statement = c.createStatement();

            String sql = "insert into group_table(group_name, admin_id) values('"+s+"', "+Main.user_id+")";

            statement.executeUpdate(sql);

            statement.close();

            c.commit();

            c.close();

        }catch (Exception e)
        {
            e.printStackTrace();
        }

    }

    @FXML
    void goBack(ActionEvent event)
    {
        try
        {
            main.showHomePage();
        } catch (IOException e)
        {
            e.printStackTrace();
        }

    }

    @FXML
    void initialize() {
        assert GroupName_field != null : "fx:id=\"GroupName_field\" was not injected: check your FXML file 'creategroup.fxml'.";
        assert create_button != null : "fx:id=\"create_button\" was not injected: check your FXML file 'creategroup.fxml'.";
        assert back_button != null : "fx:id=\"back_button\" was not injected: check your FXML file 'creategroup.fxml'.";

    }
}
