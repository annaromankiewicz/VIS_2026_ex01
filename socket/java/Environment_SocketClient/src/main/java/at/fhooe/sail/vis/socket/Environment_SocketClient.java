import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.Scanner;
import at.fhooe.sail.vis.general.IEnvService;
import at.fhooe.sail.vis.general.IEnvData;

public class Environment_SocketClient implements IEnvService {

}
    public Environment_SocketClient(String _ip, int _port) throws IOException { // try and catch and not like this
        Socket activeSocket = new Socket(_ip, _port);
        InputStream in = activeSocket.getInputStream();
        OutputStream out = activeSocket.getOutputStream();

        byte[] byteBuffer = new byte[1024];
        Scanner scan = new Scanner(System.in);

        while (true) {
            System.out.println("Eingabe: ");
            String msg = scan.nextLine();
            if (msg.length() == 0) {
                System.out.println("No empty messages!");
                continue;
            } else {
                if (msg.equalsIgnoreCase("quit")) {
                    System.out.println("shutting down client...");
                    break;
                }

                out.write(msg.getBytes());
                out.flush();

                int rVal = in.read(byteBuffer);
                String reply = new String(byteBuffer, 0, rVal);
                System.out.println("message from server: " + reply);
            }


        } // while true
        out.close();
        in.close();
        activeSocket.close();
    }

    public static void main(String[] _argv) throws IOException {
//        System.out.println("Starting Primitive_SocketClient ...");
//
//        if (_argv.length != 2) {
//            System.out.println("Usage Primitive_SocketClient <IP> <PORT>");
//            return;
//        }
//
//        int port = Integer.parseInt(_argv[1]);
//        Primitive_SocketClient client = new Primitive_SocketClient(_argv[0], port);
//
//        System.out.println("Stopping Primitive_SocketClient ...");
//    }

        IEnvService service = new Environment_SocketClient();
        while (true) {
            String[] sensors = service.reqEnvDataTypes();
            for (String sensor : sensors) {
                EnvData dataO = service.reqEnvData(sensor);
                System.out.print(dataO)
                System.out.println();
            } // for sensors
            System.out.println();
            System.out.println();
            EnvData[] dataOs = service.reqAll();
            for (EnvData dataO : dataOs) {
                System.out.println(dataO);
            } // for data
            try {
                Thread.sleep(1000);
            } catch (Exception _e) {
                _e.printStackTrace();
            }
        } // while true


}
