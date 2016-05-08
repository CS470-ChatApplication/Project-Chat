import java.io.*;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Set;

import javax.xml.ws.handler.MessageContext.Scope;

import org.apache.commons.validator.routines.InetAddressValidator;

class TCPServer {
	
    static Selector selector ;
    static ServerSocketChannel welcomeSocket;
    static String str1=null;
    

	public static void createServer(String str) throws IOException {
    	str1=str;
    	
           
    		selector = Selector.open();
    		
    		welcomeSocket = ServerSocketChannel.open();
    		InetSocketAddress hostAddress = new InetSocketAddress(InetAddress.getLocalHost().getHostAddress(), Integer.parseInt(str));
        	welcomeSocket.bind(hostAddress);
        	
        	
        	
        	welcomeSocket.configureBlocking(false);
            int ops = welcomeSocket.validOps();
            SelectionKey selectKy = welcomeSocket.register(selector, ops, null);
    		
            while (true) {
            	
            	//System.out.println("Waiting for select...");
            	
            	int noOfKeys = selector.select();
            	
            	Set selectedKeys = selector.selectedKeys();
            	
            	Iterator iter = selectedKeys.iterator();
            	
            	while (iter.hasNext()) {
            		
            		
            		SelectionKey ky = (SelectionKey) iter.next();
            		
            		if (ky.isAcceptable()) {
            			System.out.println("------------Server Listening----------");
            			 SocketChannel connectionSocket = welcomeSocket.accept();
                         connectionSocket.configureBlocking(false);
                         SelectionKey clientkey = connectionSocket.register(selector, SelectionKey.OP_READ);
                         System.out.println("Server: connected from : "+connectionSocket.getRemoteAddress().toString() +" / "+connectionSocket.socket().getLocalPort() );
            		}
            		
            		else if (ky.isReadable()) {
            			SocketChannel client = (SocketChannel) ky.channel();
            			ByteBuffer buffer = ByteBuffer.allocate(256);
                        client.read(buffer);
                        String output = new String(buffer.array()).trim();
                        System.out.println("Server: Message from client: " + output); 
                	}
            		iter.remove();
            	}
            	
    	}
    
	}
	
}


class ServerThread extends Thread {
	
	private String portNO;

	public ServerThread(String portNO) {
		super();
		this.portNO = portNO;
		
	}

	@Override
	public void run() {         
			
		
		try {
			TCPServer.createServer(portNO);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
				
	}
	
	
}
	
public class Chat {
	

    private Socket socket = null;
    private InputStream inStream = null;
    private OutputStream outStream = null;
    ArrayList<SocketChannel> scolist=new ArrayList<SocketChannel>();
    ArrayList<Integer> numlist=new ArrayList<Integer>();
    Integer count=0;
    String str1=null;
    public Chat() {
    }  
   
    
    public static void main(String[] args) {
    	ArrayList<SocketChannel> scolist1=new ArrayList<SocketChannel>();
    	OutputStream outStreams = null;
        ArrayList<Integer> numlist1=new ArrayList<Integer>();
        ArrayList<Socket> socketList = new ArrayList<Socket>();
        Integer count1=0;
        ServerThread ST = null;
//        Chat chatServer = new Chat();
//        chatServer.createSocket(args[0]);

    	if (args.length == 0) {    //checking length of port number argument
			System.out.println(" Invalild Arguments: Provide argument.");
			System.exit(1);
		} 
    	
    	String str1 = args[0];
    	ST = new ServerThread(str1);
		ST.start();
		
		 while (true) {
			 try {
                 BufferedReader inputReader = new BufferedReader(new InputStreamReader(System.in));
           
                 String typedMessage = inputReader.readLine();
                 //System.out.println("message1:"+typedMessage);
                 if (typedMessage != null && typedMessage.length() > 0) {
               //System.out.println("1"); 
                 	//typedMessage = inputReader.readLine();
						String[] splited = typedMessage.split("\\s+");
					//int c = System.in.read();
				//System.out.println("message2:"+typedMessage);	
				
					switch (splited[0]) {
					case "help":
						System.out.println("myip:- display IP address");
						System.out.println("myport:- display port number");
						System.out.println("connect:- connect to another peer");
						System.out.println("send:- send messages to peers");
						System.out.println("terminate:- close the connection between peers");
						System.out.println("exit:- exit the program");

					break;
					case "myip":
					System.out.println("The IP address is "+InetAddress.getLocalHost().getHostAddress());	
					break;
					case "myport":
						System.out.println("The program runs on port number "+str1);
					break;
					case "connect":
						InetAddressValidator valid = new InetAddressValidator();
						if(valid.isValidInet4Address(splited[1])) {
							InetSocketAddress hostAddress = new InetSocketAddress(InetAddress.getByName(splited[1]), Integer.parseInt(splited[2]));//connection establishment
							SocketChannel client = SocketChannel.open(hostAddress); // Create a non-blocking socket channel
							System.out.println("Client: Connected To : " +client.getRemoteAddress().toString() +" / "+client.socket().getLocalPort()  );
							scolist1.add(client);
							socketList.add(client.socket());
							count1++;
			                numlist1.add(count1);
						}
						else {
							System.out.println("please enter a valid IP address");
						}
						break;
					case "send":
						SocketChannel s1=scolist1.get(Integer.parseInt(splited[1])-1);
						outStreams = s1.socket().getOutputStream();
						String string1=splited[2];
						for(int i=3;i<splited.length;i++)
							string1=string1+" "+splited[i];
						 outStreams.write(string1.getBytes("UTF-8"));
						break;
					case "terminate":
						int p=numlist1.indexOf(Integer.parseInt(splited[1]));
						SocketChannel s2=scolist1.get(p);

						outStreams=s2.socket().getOutputStream();
						String msg1="terminated "+s2.socket().getInetAddress().getHostAddress().toString();
						String msg2=s2.socket().getInetAddress().getHostAddress().toString();
						outStreams.write(msg1.getBytes("UTF-8"));

						//s2.getInputStream().close();
						//s2.close();
						System.out.println("connection with "+msg2+" closed");
						socketList.remove(p);
						scolist1.remove(p);
						numlist1.remove(p);
						break;
					case "list":
						System.out.println("Id:\tIP Address\tPort no.");
						for(int i=0;i<socketList.size();i++){
							System.out.println((i+1)+"  "+socketList.get(i).getInetAddress().getHostAddress()+"  "+socketList.get(i).getPort());
						}
						break;
					case "exit":
						System.exit(0);
						
					}
                 }
			 } catch (IOException i) {
                 i.printStackTrace();
             }
		 }
    }
}
