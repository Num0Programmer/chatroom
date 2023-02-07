import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.IOException;
import java.net.Socket;


interface Server_Info 
{
	String server_addr = "time.nist.gov";
	int port = 13;
}

public class Client implements Server_Info 
{

	public static void main(String[] args) throws IOException 
	{
			String msg = "";
			Socket client_socket = new Socket(server_addr, port);
			InputStreamReader input = new InputStreamReader(client_socket.getInputStream());
			BufferedReader buffer_reader = new BufferedReader(input);
			
			
			// while the msg doesn't contain an * keep reading
			while( msg != null)
				{
					// message from server
					msg = buffer_reader.readLine();
					
					// check if the message is null
					if(msg != null) 
					{
						// print server message
						System.out.println("Server: " + msg);
					}

				}
			
			// closing time
			client_socket.close();
			buffer_reader.close();
			input.close();
			
	}
}