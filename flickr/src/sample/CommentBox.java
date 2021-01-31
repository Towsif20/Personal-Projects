package sample;

import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.layout.VBox;
import javafx.stage.Modality;
import javafx.stage.Stage;

import javafx.scene.control.*;

public class CommentBox
{
    public static void display(String title, String message)
    {
        Stage window = new Stage();

        window.initModality(Modality.APPLICATION_MODAL);

        window.setTitle(title);

        window.setMinWidth(400);

        window.setMinHeight(500);

        Label label = new Label();

        label.setText(message);

        Button closeButton = new Button("close");

        closeButton.setOnAction(e->window.close());

        VBox layout = new VBox(50);

        layout.getChildren().addAll(label,closeButton);

        layout.setAlignment(Pos.CENTER);

        Scene scene = new Scene(layout);

        window.setScene(scene);
        window.showAndWait();
    }
}
