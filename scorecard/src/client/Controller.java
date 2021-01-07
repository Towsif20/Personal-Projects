package client;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.event.ActionEvent;

public class Controller {

    Client client;

    public void setClient(Client client) {
        this.client = client;
    }

    @FXML
    private TextField team1_score;

    @FXML
    private TextField score1_score;

    @FXML
    private TextField team2_score;
    @FXML
    private TextField score2_score;

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
    private Button Home;

    @FXML
    private TextField Time;
    @FXML
    private Button home;
    @FXML
    private Button info;

    public TextField getTeam1_score() {
        return team1_score;
    }

    public void setTeam1_score(TextField team1_score) {
        this.team1_score = team1_score;
    }

    public TextField getScore1_score() {
        return score1_score;
    }

    public void setScore1_score(TextField score1_score) {
        this.score1_score = score1_score;
    }

    public TextField getTeam2_score() {
        return team2_score;
    }

    public void setTeam2_score(TextField team2_score) {
        this.team2_score = team2_score;
    }

    public TextField getScore2_score() {
        return score2_score;
    }

    public void setScore2_score(TextField score2_score) {
        this.score2_score = score2_score;
    }

    public TextField getTeam1() {
        return team1;
    }

    public void setTeam1(TextField team1) {
        this.team1 = team1;
    }

    public TextField getTeam2() {
        return team2;
    }

    public void setTeam2(TextField team2) {
        this.team2 = team2;
    }

    public TextField getGoals1() {
        return goals1;
    }

    public void setGoals1(TextField goals1) {
        this.goals1 = goals1;
    }

    public TextField getGoals2() {
        return goals2;
    }

    public void setGoals2(TextField goals2) {
        this.goals2 = goals2;
    }

    public TextField getPoss1() {
        return poss1;
    }

    public void setPoss1(TextField poss1) {
        this.poss1 = poss1;
    }

    public TextField getYellow1() {
        return yellow1;
    }

    public void setYellow1(TextField yellow1) {
        this.yellow1 = yellow1;
    }

    public TextField getRed1() {
        return red1;
    }

    public void setRed1(TextField red1) {
        this.red1 = red1;
    }

    public TextField getPoss2() {
        return poss2;
    }

    public void setPoss2(TextField poss2) {
        this.poss2 = poss2;
    }

    public TextField getYellow2() {
        return yellow2;
    }

    public void setYellow2(TextField yellow2) {
        this.yellow2 = yellow2;
    }

    public TextField getRed2() {
        return red2;
    }

    public void setRed2(TextField red2) {
        this.red2 = red2;
    }

    public TextField getShots1() {
        return shots1;
    }

    public void setShots1(TextField shots1) {
        this.shots1 = shots1;
    }

    public TextField getShots2() {
        return shots2;
    }

    public void setShots2(TextField shots2) {
        this.shots2 = shots2;
    }

    public Button getHome() {
        return Home;
    }

    public void setHome(Button home) {
        Home = home;
    }

    public TextField getTime() {
        return Time;
    }

    public void setTime(TextField time) {
        Time = time;
    }

    @FXML
    public void goHome(ActionEvent event)
    {
        try {
            client.showHome();
        }catch (Exception e)
        {
            e.printStackTrace();
        }
    }

}


/**
package client;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.event.ActionEvent;

public class Controller {

    @FXML
    private Button home;

    @FXML
    private Label score1;

    @FXML
    private Label score2;

    @FXML
    private Label team1;

    @FXML
    private Label team2;

    @FXML
    private Label time;

    public Label getScore1() {
        return score1;
    }

    public void setScore1(Label score1) {
        this.score1 = score1;
    }

    public Label getScore2() {
        return score2;
    }

    public void setScore2(Label score2) {
        this.score2 = score2;
    }

    public Label getTeam1() {
        return team1;
    }

    public void setTeam1(Label team1) {
        this.team1 = team1;
    }

    public Label getTeam2() {
        return team2;
    }

    public void setTeam2(Label team2) {
        this.team2 = team2;
    }

    public Label getTime() {
        return time;
    }

    public void setTime(Label time) {
        this.time = time;
    }


    @FXML
    void goHome(ActionEvent event) {

    }

}
*/