package sample;

import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ResourceBundle;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.text.Text;

public class SearchPhotoController {

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
    private ResourceBundle resources;

    @FXML
    private URL location;

    @FXML
    private ImageView tagged_photo;

    @FXML
    private Text owner_label;

    @FXML
    private Button back_button;

    @FXML
    void initialize()
    {
        Connection c = null;

        Statement statement = null;

        try
        {
            c = Main.createConnection();

            statement = c.createStatement();

            String sql = "select * from photos, user_table where photo_id = "+id+ " and user_id = owner_id";

            ResultSet rs = statement.executeQuery(sql);

            while (rs.next())
            {
                owner_label.setText(rs.getString("user_name"));

                String s = rs.getString("photo_directory");
                File file;
                file = new File(s);
                tagged_photo.setImage(new Image(file.toURI().toString()));
            }

        }catch ( Exception e)
        {
            e.printStackTrace();
        }
    }

    @FXML
    public void goBack(ActionEvent event)
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
