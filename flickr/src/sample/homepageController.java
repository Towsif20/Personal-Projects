package sample;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.AnchorPane;
import javafx.stage.DirectoryChooser;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

import java.io.File;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

public class homepageController
{
    public Button next_button;
    public Button post_button;
    public Button create_group_button;
    public Button show_groups_button;
    public Button create_album_button;
    public Button show_album_button;
    public Button photoSearchButton;
    public Button groupSearchButton;
    ArrayList<String> dir = new ArrayList<>();
    ArrayList<String> names = new ArrayList<>();
    ArrayList<Integer> ids = new ArrayList<>();

    public Label comment_count;
    public Label fave_count;
    public Button logOut_button;
    public Button image_home_button;
    Main main;

    int photo_id;

    public void setMain(Main main)
    {
        this.main = main;
    }
    @FXML
    private AnchorPane timeline_tab;

    @FXML
    private ImageView image_id;

    @FXML
    private Button fave_button;

    @FXML
    private Button comment_button;

    @FXML
    private AnchorPane profile_tab;

    @FXML
    private AnchorPane search_tab;

    @FXML
    private TextField searchField;

    @FXML
    private Button searchButton;

    @FXML
    private AnchorPane noti_tab;

    @FXML
    private TextField directory_field;

    @FXML
    private Button browse_button;

    @FXML
    private Label user_label;

    @FXML
    private TextField caption_field;

    @FXML
    private TextField tag_field;

    @FXML
    private TextField comment_field;

    @FXML
    private Button show_com_button;

    @FXML
    private Label owner_field;

    @FXML
    private TextArea notification_text;


    public void updateNotification()
    {
        Connection c = null;
        Statement statement = null;

        ArrayList<String> names = new ArrayList<>();
        ArrayList<String> descriptions = new ArrayList<>();

        try
        {
            c = Main.createConnection();

            statement = c.createStatement();

            String sql = "select user_id, user_name,datentime,description from notification, user_table " +
                    "where notification_id in (select notification_id from receive where rec_id="+Main.user_id+") " +
                    "and user_id = creator_id " +
                    "order by datentime desc;";

            ResultSet rs = statement.executeQuery(sql);



            while (rs.next())
            {
                if(rs.getInt("user_id") == Main.user_id)
                    continue;

                names.add(rs.getString("user_name"));
                descriptions.add(rs.getString("description"));
            }

            rs.close();

            statement.close();

            c.close();
        }catch (Exception e)
        {
            e.printStackTrace();
        }

        String s ="";

        System.out.println("names " +names.size());
        System.out.println("description " +descriptions.size());

        if(names.size()==0)
            return;

        for(int i=0;i<names.size();i++)
        {
            s = s + names.get(i) + " " + descriptions.get(i) + "\n";
        }

        notification_text.setText(s);
    }

    @FXML
    public void faveAction(ActionEvent event)
    {
        Connection c = null;
        Statement statement = null;

        boolean faved = false;
        try
        {
            c = Main.createConnection();

            statement = c.createStatement();

            String sql = "select * from fave where photo_id = "+photo_id+" and userwhofaves = "+Main.user_id;

            ResultSet rs = statement.executeQuery(sql);

            if(rs.next())
            {
                faved = true;
            }

            if(faved)
            {
                sql = "delete from fave where photo_id = "+photo_id+" and userwhofaves = "+Main.user_id;
                int t = Integer.valueOf(fave_count.getText());
                t--;
                fave_count.setText(Integer.toString(t));

                statement.executeUpdate(sql);
            }

            else
            {
                sql = "insert into fave(userwhofaves, photo_id) " +
                        "values("+Main.user_id+", "+photo_id+");";

                int t = Integer.valueOf(fave_count.getText());
                t++;
                fave_count.setText(Integer.toString(t));

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

        updateNotification();

        //initialize();
    }



    @FXML
    public void initialize()
    {
        updateNotification();

        Connection c = null;
        Statement stmnt = null;

        String s = null;

        String name = null;

        dir = new ArrayList<>();
        names = new ArrayList<>();
        ids = new ArrayList<>();

        try
        {
            c = Main.createConnection();

            stmnt = c.createStatement();

            ResultSet rs = stmnt.executeQuery("select * from photos, user_table where owner_id = user_id and " +
                    "owner_id in (select followed_id from follow where follower_id = "+Main.user_id+") " +
                    "and photo_directory <> ''" +
                    " order by timeofpost");


            while (rs.next())
            {
                //System.out.println(rs.getInt("photo_id"));

                dir.add(rs.getString("photo_directory"));
                
                names.add(rs.getString("user_name"));

                ids.add(rs.getInt("photo_id"));
                //System.out.println(s);

            }

            photo_id = 0;

            if(ids.size() > 0)
            {
                photo_id = ids.get(ids.size()-1);
                s = dir.get(dir.size()-1);
                name = names.get(names.size()-1);

                rs = stmnt.executeQuery("select count(*) from fave where photo_id = "+photo_id);

                while (rs.next())
                {
                    //System.out.println(rs.getInt("photo_id"));
                    fave_count.setText(rs.getString("count"));

                }

                rs = stmnt.executeQuery("select count(*) from comment_table where photo_id = "+photo_id);

                while (rs.next())
                {
                    //System.out.println(rs.getInt("photo_id"));
                    comment_count.setText(rs.getString("count"));

                }

            }


            rs.close();

            stmnt.close();

            //c.commit();

            c.close();
        }catch (Exception e)
        {
            e.printStackTrace();
        }

        File file;

        if(s != null)
        {
            file = new File(s);
            image_id.setImage(new Image(file.toURI().toString()));
            owner_field.setText(name);
            System.out.println(Main.userName);
            System.out.println(Main.user_id);
        }

        else
        {
            owner_field.setText("no photos for you\nsearch people to follow");
        }

        user_label.setText(Main.userName);

        System.out.println(Main.userName);
        System.out.println(Main.user_id);
    }

    @FXML
    public void browseAction(ActionEvent event)
    {
        FileChooser fileChooser = new FileChooser();

        fileChooser.setTitle("Open Resource File");
        fileChooser.getExtensionFilters().addAll(
                new FileChooser.ExtensionFilter("Image Files", "*.png", "*.jpg", "*.gif"));

        Stage stage = (Stage) profile_tab.getScene().getWindow();

        File selectedFile = fileChooser.showOpenDialog(stage);
        if (selectedFile != null)
        {
            System.out.println(selectedFile.getAbsolutePath());

            directory_field.setText(selectedFile.getAbsolutePath());
        }
    }

    @FXML
    public void postAction(ActionEvent event)
    {
        String cap = caption_field.getText();
        String tag = tag_field.getText();
        String dir = directory_field.getText();

        Connection c = null;
        Statement stmnt = null;

        try
        {
            c = Main.createConnection();

            stmnt = c.createStatement();

            String sql = "insert into photos(owner_id, caption, timeofpost, location, photo_directory) " +
                    "values("+Main.user_id+",'"+cap+"',current_timestamp(0),'dhaka','"+dir+"')";

            stmnt.executeUpdate(sql);

            sql = "select photo_id from photos where photo_id = (select max(photo_id) from photos)";

            ResultSet rs = stmnt.executeQuery(sql);

            int pid = 0;

            while (rs.next())
            {
                pid = rs.getInt("photo_id");
            }

            sql = "insert into post(owner_id, photo_id) values("+Main.user_id+", "+pid+")";

            stmnt.executeUpdate(sql);

            rs.close();

            stmnt.close();

            c.commit();

            c.close();

        }catch (Exception e)
        {
            e.printStackTrace();
        }

        try
        {
            c = Main.createConnection();

            stmnt = c.createStatement();

            String sql = "select photo_id from photos where owner_id = "+Main.user_id+" and photo_id = " +
                    "(select max(photo_id) from photos)";

            ResultSet rs = stmnt.executeQuery(sql);

            int id = 0;

            while (rs.next())
            {
                id = rs.getInt("photo_id");
            }

            sql = "insert into tag_table(photo_id, keyword) " +
                    "values("+id+", '"+tag+"')";

            stmnt.executeUpdate(sql);

            rs.close();

            stmnt.close();

            c.commit();

            c.close();

        }catch (Exception e)
        {
            e.printStackTrace();
        }
    }
    @FXML
    void searchAction(ActionEvent event)
    {
        Connection c = null;

        Statement statement = null;

        c= Main.createConnection();

        String s = searchField.getText();

        int i = 0;
        try
        {
            statement = c.createStatement();
            String sql = "select * from user_table where user_name like '%"+s+"%';";
            ResultSet rs = statement.executeQuery(sql);

            while (rs.next())
            {
                System.out.println(rs.getString("user_name"));

                s = rs.getString("user_name");

                i = rs.getInt("user_id");
            }

            rs.close();

            statement.close();

            c.close();

        } catch (SQLException e)
        {
            e.printStackTrace();
        }

        System.out.println("name "+s+" id "+i);
        try
        {
            main.showSearchPage(i);
        } catch (Exception e)
        {
            e.printStackTrace();
        }

    }

    public void commentAction(ActionEvent event)
    {
        Connection c = null;
        Statement statement = null;
        String comment = comment_field.getText();

        try

        {
            c = Main.createConnection();

            statement = c.createStatement();

            String sql = "insert into comment_table(commentator_id, photo_id, comments) " +
                    "values("+Main.user_id+", "+photo_id+", '"+comment+"');";

            statement.executeUpdate(sql);

            statement.close();

            c.commit();

            c.close();

        }catch (Exception e)
        {
            e.printStackTrace();
        }

        initialize();
    }

    public void showComAction(ActionEvent event)
    {
        Connection c = null;

        Statement statement = null;

        String s = "";

        try
        {
            c = Main.createConnection();

            statement = c.createStatement();

            String sql = "select user_name, comments from comment_table , user_table where user_id = commentator_id and photo_id = "+photo_id+";";

            ResultSet rs = statement.executeQuery(sql);

            while (rs.next())
            {
                s = s + " "+rs.getString("user_name") + ": " + rs.getString("comments") + "\n";
            }

        }catch (Exception e)
        {
            e.printStackTrace();
        }
        updateNotification();
        //alert.setHeaderText("Incorrect input");
        CommentBox.display("comments", s);

    }

    public void logOutAction(ActionEvent event)
    {
        try
        {
            main.showLoginPage();
        } catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    public void shownextPhoto(ActionEvent event)
    {
        if(ids.size()==1)
            return;

        else
        {
            dir.remove(dir.size()-1);
            ids.remove(ids.size()-1);
            names.remove(names.size()-1);

            String s = "";
            String name = "";

            photo_id = ids.get(ids.size()-1);
            s = dir.get(dir.size()-1);
            name = names.get(names.size()-1);

            Connection c = Main.createConnection();

            Statement stmnt = null;
            try
            {
                stmnt = c.createStatement();
                ResultSet rs = stmnt.executeQuery("select count(*) from fave where photo_id = "+photo_id);

                while (rs.next())
                {
                    //System.out.println(rs.getInt("photo_id"));
                    fave_count.setText(rs.getString("count"));

                }

                rs = stmnt.executeQuery("select count(*) from comment_table where photo_id = "+photo_id);

                while (rs.next())
                {
                    //System.out.println(rs.getInt("photo_id"));
                    comment_count.setText(rs.getString("count"));

                }
            } catch (SQLException e)
            {
                e.printStackTrace();
            }

            File file;
            file = new File(s);
            image_id.setImage(new Image(file.toURI().toString()));
            owner_field.setText(name);
            System.out.println(Main.userName);
            System.out.println(Main.user_id);

        }
    }

    public void createGroupAction(ActionEvent event)
    {
        try
        {
            main.showCreateGroupPage();
        } catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    public void showGroupAction(ActionEvent event)
    {

    }

    public void createAlbumAction(ActionEvent event)
    {
    }

    public void showAlbumAction(ActionEvent event)
    {
    }

    public void photoSearchAction(ActionEvent event)
    {
        Connection c = null;

        Statement statement = null;

        c= Main.createConnection();

        String s = searchField.getText();

        int i = 0;
        try
        {
            statement = c.createStatement();
            String sql = "select * from tag_table where keyword like '%"+s+"%';";
            ResultSet rs = statement.executeQuery(sql);

            while (rs.next())
            {
                i = rs.getInt("photo_id");
            }

            rs.close();

            statement.close();

            c.close();

        } catch (SQLException e)
        {
            e.printStackTrace();
        }

        System.out.println("name "+s+" id "+i);
        try
        {
            main.showSearchPhotoPage(i);
        } catch (Exception e)
        {
            e.printStackTrace();
        }

    }

    public void groupSearchAction(ActionEvent event)
    {
        Connection c = null;

        Statement statement = null;

        c= Main.createConnection();

        String s = searchField.getText();

        int i = 0;
        try
        {
            statement = c.createStatement();
            String sql = "select * from group_table where group_name like '%"+s+"%';";
            ResultSet rs = statement.executeQuery(sql);

            while (rs.next())
            {
                i = rs.getInt("group_id");
            }

            rs.close();

            statement.close();

            c.close();

        } catch (SQLException e)
        {
            e.printStackTrace();
        }

        System.out.println("name "+s+" id "+i);
        try
        {
            main.showGroupSearch(i);
        } catch (Exception e)
        {
            e.printStackTrace();
        }
    }
}