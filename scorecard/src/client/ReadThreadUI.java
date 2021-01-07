package client;

import common.Info;

public class ReadThreadUI implements Runnable {
    Client client;
    Thread t;

    public ReadThreadUI(Client client) {
        this.client = client;
        this.t = new Thread(this);
        t.start();
    }

    public void run() {
        try {
            while (true) {
                Object o = client.nc.read();
                if (o != null) {
                    if (o instanceof Info) {
                        Info obj = (Info) o;
                        client.updateInfo(obj.getScore(),obj.getPossession1(),obj.getPossession2(),obj.getShots1(),obj.getShots2(),obj.getYellow1(),obj.getYellow2(),obj.getRed1(),obj.getRed2());
                        //ReadThreadUI.info = obj;
                        //client.updateScore(obj.getScore().getTeam1(),obj.getScore().getTeam2(),obj.getScore().getScore1(),obj.getScore().getScore2());
                    }
                }
            }
        } catch (Exception e) {
            System.out.println(e);
        } finally {
            client.nc.closeConnection();
        }
    }
}



