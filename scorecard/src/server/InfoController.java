package server;

import java.net.URL;
import java.util.ResourceBundle;

import common.Info;
import common.Score;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;

public class InfoController {

    ServerMain serverMain;

    @FXML
    private ResourceBundle resources;

    @FXML
    private URL location;

    @FXML
    private TextField team1;

    @FXML
    private TextField team2;

    @FXML
    private TextField goals1;

    @FXML
    private TextField goals2;

    @FXML
    private TextField poss1;

    @FXML
    private TextField yellow1;

    @FXML
    private TextField red1;

    @FXML
    private TextField poss2;

    @FXML
    private TextField yellow2;

    @FXML
    private TextField red2;

    @FXML
    private TextField shots1;

    @FXML
    private TextField shots2;

    @FXML
    private TextField time;

    @FXML
    private Button Home;

    @FXML
    private Button send;

    @FXML
    void sendAction(ActionEvent event) {

        String Time = time.getText();

        String Team1=team1.getText();

        String Team2=team2.getText();

        String Goals1=goals1.getText();

        String Goals2=goals2.getText();

        String Poss1=poss1.getText();

        String Yellow1=yellow1.getText();

        String Red1=red1.getText();

        String Poss2=poss2.getText();

        String Yellow2=yellow2.getText();

        String Red2=red2.getText();

        String Shots1=shots1.getText();

        String Shots2=shots2.getText();

        Score score = new Score(Team1,Team2,Goals1,Goals2,Time);
        Info info  = new Info(score,Poss1,Poss2,Shots1,Shots2,Yellow1,Yellow2,Red1,Red2);
        System.out.println("Server sending " + info);

        try {
            this.serverMain.server.nc.write(info);
        }catch (Exception e)
        {
            e.printStackTrace();
        }

    }



    public void setServerMain(ServerMain serverMain)
    {
        this.serverMain = serverMain;
    }
}
