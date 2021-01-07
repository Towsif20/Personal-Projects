package client;

import java.net.URL;
import java.util.ResourceBundle;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;

public class homeController {

    Client client;
    League pl = new League("Premier League");
    League laliga = new League("La Liga");
    League fifa = new League("International");

    public void setClient(Client client) {
        this.client = client;
    }

    @FXML
    private ResourceBundle resources;

    @FXML
    private URL location;

    @FXML
    private Button premierLeague;

    @FXML
    private Button laLiga;

    @FXML
    private Button international;

    @FXML
    void goInternational(ActionEvent event) {
        try {
            client.showScore(fifa);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @FXML
    void goLaLiga(ActionEvent event) {

        try {
            client.showScore(laliga);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @FXML
    void goPremierLeague(ActionEvent event) {

        try {
            client.showScore(pl);
        }catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    @FXML
    void initialize() {
        assert premierLeague != null : "fx:id=\"premierLeague\" was not injected: check your FXML file 'home.fxml'.";
        assert laLiga != null : "fx:id=\"laLiga\" was not injected: check your FXML file 'home.fxml'.";
        assert international != null : "fx:id=\"international\" was not injected: check your FXML file 'home.fxml'.";

    }
}
