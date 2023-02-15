import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.*;
import java.io.IOException;
import java.net.Socket;
import java.util.Scanner;


interface Server_Info 
{
	String server_addr = "127.0.0.1";
	int port = 25176;
}

public class Client implements Server_Info 
{

	public static void main(String[] args) throws IOException 
	{
		Socket client_socket = null;
		InputStreamReader input = null;
		OutputStreamWriter output = null;
		BufferedReader buffer_reader = null;
		BufferedWriter buffer_writer = null;
		boolean steps_received = false;

		try
		{
			client_socket = new Socket(server_addr, port);
			input = new InputStreamReader(client_socket.getInputStream());
			output = new OutputStreamWriter(client_socket.getOutputStream());
			buffer_reader = new BufferedReader(input);
			BufferedOutputStream outStream = new BufferedOutputStream(client_socket.getOutputStream());
                        String rec_str;
                        int rec_as_num = 0;

			Scanner scanner = new Scanner(System.in);

			while (true) 
			{
				String msgToSend = scanner.nextLine();


				outStream.write(msgToSend.getBytes());
				outStream.flush();
					
					// convert rec to an integer
					rec_str = buffer_reader.readLine();
					for (int i = 0; i < rec_str.length(); i += 1)
					{
						System.out.println("this: " + rec_str);
						rec_as_num = (int)rec_str.charAt(i);
					}

				steps_received = true;
                                
				System.out.print("Server: ");
                                System.out.println(rec_as_num);

				
			}

		} catch(IOException e){
			e.printStackTrace();
		} finally {
			try {
				if (client_socket != null)
				client_socket.close();
				System.out.println("connecton ended");

				if (input != null)
				input.close();

				if (output != null)
				output.close();


				if (buffer_reader != null)
				buffer_reader.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
			
	}
}
