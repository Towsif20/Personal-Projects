package sample;


import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.layout.VBox;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.scene.control.*;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;


public class Searchpage
{
    public static void display(String key)
    {
        Connection c = null;

        Statement statement = null;

        ArrayList<String> results = new ArrayList<>();

        try
        {
            c = Main.createConnection();

            statement = c.createStatement();

            String sql = "select user_name from user_table where user_name like '%"+key+"%';";

            ResultSet rs = statement.executeQuery(sql);

            while (rs.next())
            {
                results.add(rs.getString("user_name"));
            }

            rs.close();

            statement.close();

            c.close();

        }catch (Exception e)
        {
            e.printStackTrace();
        }

        ScrollPane scrollPane = new ScrollPane();
    }
}
