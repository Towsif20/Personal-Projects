package sample;

import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ResourceBundle;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

public class GroupController {

    public Button browse_buttom;
    public TextField directory_field;
    public AnchorPane window;
    public TextField caption_field;
    public TextField tag_field;
    public Button show_button;
    Main main;
    int id;

    public void setMain(Main main)
    {
        this.main = main;
    }

    public void setId(int id)
    {
        this.id = id;
    }

    @FXML
    private ResourceBundle resources;

    @FXML
    private URL location;

    @FXML
    private Label name_field;

    @FXML
    private Label memeber_count;

    @FXML
    private Label photo_count;

    @FXML
    private Button join_button;

    @FXML
    private Button add_button;

    @FXML
    private Button home_button;

    @FXML
    void addAction(ActionEvent event)
    {
        String cap = caption_field.getText();
        String tag = tag_field.getText();
        String dir = directory_field.getText();

        Connection c = null;
        Statement statement = null;

        try
        {
            c = Main.createConnection();

            statement = c.createStatement();

            String sql = "select * from memberofgroup where member_id = " + Main.user_id + " and group_id = " + id;

            ResultSet rs = statement.executeQuery(sql);

            if (!rs.next())
            {
                CommentBox.display("alert", "you are not a member of this group");

            }

            else
            {
                sql = "insert into photos(owner_id, caption, timeofpost, location, photo_directory, group_id) " +
                        "values("+Main.user_id+",'"+cap+"',current_timestamp(0),'dhaka','"+dir+"' ,"+id+")";

                statement.executeUpdate(sql);

                statement.close();

                c.commit();

                c.close();

            }


        } catch (SQLException e)
        {
            e.printStackTrace();
        }
    }
        @FXML
    void goHome(ActionEvent event)
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
    void joinAction(ActionEvent event)
    {
        Connection c = null;
        Statement statement = null;

        try
        {
            c = Main.createConnection();

            statement = c.createStatement();

            String sql = "select * from memberofgroup where member_id = "+Main.user_id+ " and group_id = "+id;

            ResultSet rs = statement.executeQuery(sql);

            if(!rs.next())
            {
                sql = "insert into memberofgroup(member_id, group_id) values(" + Main.user_id+ ","+id+");";

                statement.executeUpdate(sql);

            }

            else
            {
                sql = "delete from memberofgroup where member_id = "+Main.user_id+ " and group_id = "+id;

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
    void initialize() {

        Connection c = null;

        Statement statement = null;

        try
        {
            c = Main.createConnection();

            statement = c.createStatement();

            String sql = "select * from group_table where group_id = "+id+";";

            ResultSet rs = statement.executeQuery(sql);

            while (rs.next())
            {
                name_field.setText(rs.getString("group_name"));
            }

            sql = "select count(*) from memberofgroup where group_id = "+id;

            rs = statement.executeQuery(sql);

            while (rs.next())
            {
                memeber_count.setText(rs.getString("count") + " members");
            }

            sql = "select count(*) from photos where group_id = "+id;

            rs = statement.executeQuery(sql);

            while (rs.next())
            {
                photo_count.setText(rs.getString("count") + " photos");
            }

            rs.close();

            statement.close();

            c.close();

        }catch (Exception e)
        {
            e.printStackTrace();
        }

    }

    public void browseAction(ActionEvent event)
    {
        FileChooser fileChooser = new FileChooser();

        fileChooser.setTitle("Open Resource File");
        fileChooser.getExtensionFilters().addAll(
                new FileChooser.ExtensionFilter("Image Files", "*.png", "*.jpg", "*.gif"));

        Stage stage = (Stage) window.getScene().getWindow();

        File selectedFile = fileChooser.showOpenDialog(stage);
        if (selectedFile != null)
        {
            System.out.println(selectedFile.getAbsolutePath());

            directory_field.setText(selectedFile.getAbsolutePath());
        }
    }

    public void showAction(ActionEvent event)
    {
    }
}
