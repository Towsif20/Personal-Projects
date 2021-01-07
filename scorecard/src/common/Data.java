package common;

import java.io.Serializable;

public class Data implements Serializable {

    private String value1;
    private String value2;

    public Data(String value1, String value2) {
        this.value1 = value1;
        this.value2 = value2;
    }

    public String getValue1() {
        return this.value1;
    }

    public String getValue2() {
        return this.value2;
    }

}