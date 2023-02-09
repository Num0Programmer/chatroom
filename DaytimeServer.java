import java.io.InputStreamReader;
import java.io.DataOutputStream;
import java.io.BufferedReader;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

import java.util.logging.Level;
import java.util.logging.Logger;

interface ServerInfo
{
    String serverAddr = "time.nist.gov";
    int serverPort = 13;
}

public class DaytimeServer implements ServerInfo
{

    private static ServerSocket serverSocket;
    private static int port;
    //Socket clientSocket = null;

    public DaytimeServer(int port) 
    {
        try {
            DaytimeServer.port = port;
            DaytimeServer.serverSocket = new ServerSocket(port);
        } catch (IOException ex) {
            Logger.getLogger(DaytimeServer.class.getName()).log(Level.SEVERE, null, ex);
            System.err.println("Error starting server on port " + port);
            System.exit(1);
        }

        DaytimeServer.port = port;
    }

    public static String getDateMsg() throws IOException
    {
        String msgToClient = "";
        String msgFromServer = "";
        Socket msgSocket = new Socket(serverAddr, serverPort);
        InputStreamReader msgInput = 
                             new InputStreamReader(msgSocket.getInputStream());
        BufferedReader bufferReader = new BufferedReader(msgInput);

        // capture date message to string
        while(msgFromServer != null)
        {
            msgFromServer = bufferReader.readLine();

            if(msgFromServer != null)
            {
                // capture date message before buffer reader returns null
                msgToClient = new String(msgFromServer);
            }
        }

        // close stream and socket to other server
        msgSocket.close();
        bufferReader.close();
        msgInput.close();

        return msgToClient;
    }

    public void runServerLoop(String msgToClient) throws IOException 
    {
        System.out.println("Daytime server started");

        // run server loop
        while (true) 
        {
            System.out.println("Waiting for connections on port #" + port);

            Client clientSocket = new Client(serverSocket.accept(), msgToClient);

            System.out.println("Client connected ...");

            Thread clientThread = new Thread(clientSocket);

            clientThread.start();
        }
    }

    public static void main(String args[]) throws Exception
    {
        // first, get date message from other server
        String msgToClient = getDateMsg();

        // create instance of server
        DaytimeServer daytimeServer = new DaytimeServer(13);

        // fire up server loop
        daytimeServer.runServerLoop(msgToClient);
    }

    // nested client class for instantiation of a client object;
    // client will implement runnable
    public class Client implements Runnable
    {
        Socket clientSocket = null;
        String relayMsg = null;

        public Client(Socket givenSocket, String msgToRelay)
        {
            this.clientSocket = givenSocket;

            // to avoid weirdness from string aliasing
            this.relayMsg = new String(msgToRelay);
        }

        // the client handler process under run() for when thread runs
        public void run()
        {
            // initialize variables
            DataOutputStream outputStream = null;
            char[] charMsgToClient = this.relayMsg.toCharArray();
            int index;

            // initialize the output stream to client
            try {
                outputStream = 
                          new DataOutputStream(clientSocket.getOutputStream());
            } catch (IOException e) {
                System.err.println("Error opening network streams");
                return;
            }

            // iterate through msg char array
            for(index = 0; index < charMsgToClient.length; index++)
            {
                //System.out.print(charMsgToClient[index]);

                try {
                    outputStream.writeByte(charMsgToClient[index]);
                } catch (IOException e) {
                    System.err.println("Error writing character to client");
                    return;
                }
            }
            
            // close client socket and stream
            try {
                clientSocket.close();
                outputStream.close();
            } catch (IOException e) {
                System.err.println("Error closing socket and stream to client");
            }
        }
    }
}
