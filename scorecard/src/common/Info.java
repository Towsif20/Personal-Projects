package common;

import java.io.Serializable;

public class Info implements Serializable {
    Score score;
    String possession1;
    String possession2;
    String shots1;
    String shots2;
    String yellow1;
    String yellow2;
    String red1;
    String red2;

    public Info(Score score, String possession1, String possession2, String shots1, String shots2, String yellow1, String yellow2, String red1, String red2) {
        this.score = score;
        this.possession1 = possession1;
        this.possession2 = possession2;
        this.shots1 = shots1;
        this.shots2 = shots2;
        this.yellow1 = yellow1;
        this.yellow2 = yellow2;
        this.red1 = red1;
        this.red2 = red2;
    }

    public Score getScore() {
        return score;
    }

    public void setScore(Score score) {
        this.score = score;
    }

    public String getPossession1() {
        return possession1;
    }

    public void setPossession1(String possession1) {
        this.possession1 = possession1;
    }

    public String getPossession2() {
        return possession2;
    }

    public void setPossession2(String possession2) {
        this.possession2 = possession2;
    }

    public String getShots1() {
        return shots1;
    }

    public void setShots1(String shots1) {
        this.shots1 = shots1;
    }

    public String getShots2() {
        return shots2;
    }

    public void setShots2(String shots2) {
        this.shots2 = shots2;
    }

    public String getYellow1() {
        return yellow1;
    }

    public void setYellow1(String yellow1) {
        this.yellow1 = yellow1;
    }

    public String getYellow2() {
        return yellow2;
    }

    public void setYellow2(String yellow2) {
        this.yellow2 = yellow2;
    }

    public String getRed1() {
        return red1;
    }

    public void setRed1(String red1) {
        this.red1 = red1;
    }

    public String getRed2() {
        return red2;
    }

    public void setRed2(String red2) {
        this.red2 = red2;
    }
}
