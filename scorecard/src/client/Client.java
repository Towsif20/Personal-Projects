package client;

import common.NetworkUtil;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import common.Info;
import server.InfoController;
import common.Score;

public class Client extends Application {

    Stage primaryStage;
    NetworkUtil nc = null;
    String serverAddress = "127.0.0.1";
    int serverPort = 33333;
    Controller controller = null;
    InfoController infoController = null;
    Info info;


    @Override
    public void start(Stage primaryStage) throws Exception{

        this.primaryStage = primaryStage;
        showHome();

        /**FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("sample.fxml"));
        Parent root = loader.load();

        // Loading the controller
        controller = loader.getController();

        // Set the primary stage
        primaryStage.setTitle("NetworkThread UI");
        primaryStage.setScene(new Scene(root));
        primaryStage.show();

        new NetworkThread(this);*/
    }

    public void showHome() throws Exception
    {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("home.fxml"));
        Parent root = loader.load();
        homeController homeController = loader.getController();

        homeController.setClient(this);

        Scene scene = new Scene(root);
        primaryStage.setScene(scene);
        primaryStage.setTitle("Home page");
        primaryStage.show();
    }

    public void showScore(League league) throws Exception
    {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("score.fxml"));
        Parent root = loader.load();

        // Loading the controller
        controller = loader.getController();

        // Set the primary stage
        controller.setClient(this);
        primaryStage.setTitle(league.getName());
        primaryStage.setScene(new Scene(root));
        primaryStage.show();

        new NetworkThread(this);
    }



    public void updateInfo(Score score, String possession1, String possession2, String shots1, String shots2, String yellow1, String yellow2, String red1, String red2)
    {
        controller.getTeam1_score().setText(score.getTeam1());
        controller.getTeam2_score().setText(score.getTeam2());
        controller.getScore1_score().setText(score.getScore1());
        controller.getScore2_score().setText(score.getScore2());
        controller.getTime().setText(score.getTime());
        controller.getTeam1().setText(score.getTeam1());
        controller.getTeam2().setText(score.getTeam2());
        controller.getGoals1().setText(score.getScore1());
        controller.getGoals2().setText(score.getScore2());
        controller.getPoss1().setText(possession1);
        controller.getPoss2().setText(possession2);
        controller.getShots1().setText(shots1);
        controller.getShots2().setText(shots2);
        controller.getYellow1().setText(yellow1);
        controller.getYellow2().setText(yellow2);
        controller.getRed1().setText(red1);
        controller.getRed2().setText(red2);
    }

    public static void main(String[] args) {
        launch(args);
    }
}


class NetworkThread implements Runnable {
    Client client;
    Thread t;

    public NetworkThread(Client client) {
        this.client = client;
        t = new Thread(this);
        t.start();
    }

    public void run()
    {
        try
        {
            client.nc = new NetworkUtil(client.serverAddress, client.serverPort);
            new ReadThreadUI(client);
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}