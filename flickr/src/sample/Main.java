package sample;
import java.io.IOException;
import java.net.URL;
import java.sql.*;
import java.util.ResourceBundle;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class Main extends Application {

    public static int user_id;
    public static String userName;

    Stage stage;

    public static Connection createConnection()
    {
        Connection c = null;
        try
        {
            Class.forName("org.postgresql.Driver");

            c = DriverManager
                    .getConnection("jdbc:postgresql://localhost:5432/"+"new_database",
                            "postgres", "123");

            c.setAutoCommit(false);
            System.out.println("Opened database successfully");

            //return  c;

        }catch (Exception e)
        {
            e.printStackTrace();
        }

        return c;
    }

    @Override
    public void start(Stage primaryStage) throws Exception
    {
        stage = primaryStage;
        showLoginPage();
        //showSignUpPage();
        //showHomePage();
    }

    public void showLoginPage() throws Exception {
        // XML Loading using FXMLLoader
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("logIn.fxml"));
        Parent root = loader.load();

        // Loading the controller
        LogInController controller = loader.getController();
        controller.setMain(this);

        // Set the primary stage
        stage.setTitle("Login");
        stage.setScene(new Scene(root));
        stage.show();
    }

    public void showSignUpPage() throws Exception
    {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("signup.fxml"));
        Parent root = loader.load();

        // Loading the controller
        SignUpController controller = loader.getController();
        controller.setMain(this);

        // Set the primary stage
        stage.setTitle("sign up");
        stage.setScene(new Scene(root));
        stage.show();
    }

    public void showHomePage() throws IOException
    {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("homepage.fxml"));
        Parent root = loader.load();

        // Loading the controller
        homepageController controller = loader.getController();
        controller.setMain(this);

        // Set the primary stage
        stage.setTitle("home page for user");
        stage.setScene(new Scene(root));
        stage.show();
    }

    public void showSearchPage(int id) throws Exception
    {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("searchpage.fxml"));
        Parent root = loader.load();

        searchController controller = loader.getController();
        controller.setButton_id(id);
        System.out.println("show search page : id = "+id);
        controller.setMain(this);

        controller.initialize();

        // Set the primary stage
        stage.setTitle("search page for user");
        stage.setScene(new Scene(root));
        stage.show();
    }

    public void showProfilePage(int id) throws  Exception
    {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("profile.fxml"));
        Parent root = loader.load();

        // Loading the controller
        profileController controller = loader.getController();
        controller.setId(id);
        controller.setMain(this);

        controller.initialize();

        // Set the primary stage
        stage.setTitle("profile page for user");
        stage.setScene(new Scene(root));
        stage.show();
    }

    public void showCreateGroupPage() throws Exception
    {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("creategroup.fxml"));
        Parent root = loader.load();

        // Loading the controller
        createGroupController controller = loader.getController();
        controller.setMain(this);

        controller.initialize();

        // Set the primary stage
        stage.setTitle("create group for user");
        stage.setScene(new Scene(root));
        stage.show();
    }

    public void showSearchPhotoPage(int id) throws Exception
    {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("searchPhotoPage.fxml"));
        Parent root = loader.load();

        // Loading the controller
        SearchPhotoController controller = loader.getController();
        controller.setId(id);
        controller.setMain(this);

        controller.initialize();

        // Set the primary stage
        stage.setTitle("create group for user");
        stage.setScene(new Scene(root));
        stage.show();
    }

    public void showGroupSearch(int id) throws Exception
    {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("groupsearch.fxml"));
        Parent root = loader.load();

        SearchGroupController controller = loader.getController();
        controller.setButton_id(id);
        System.out.println("show search page : id = "+id);
        controller.setMain(this);

        controller.initialize();

        // Set the primary stage
        stage.setTitle("search page for user");
        stage.setScene(new Scene(root));
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }


    public void showGroup(int id) throws Exception
    {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("group.fxml"));
        Parent root = loader.load();

        // Loading the controller
        GroupController controller = loader.getController();
        controller.setId(id);
        controller.setMain(this);

        controller.initialize();

        // Set the primary stage
        stage.setTitle("profile page for user");
        stage.setScene(new Scene(root));
        stage.show();
    }
}
