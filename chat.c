#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ifaddrs.h>

void server(){
  int serverSocket,client_connected,len;
  struct sockaddr_in client_addr,server_addr;
  struct hostent *ptrh;
  struct sockaddr_in sin;
  int n=0; 
  char message[100],received[100];

  serverSocket=socket(AF_INET, SOCK_STREAM, 0);

  memset((char*)&server_addr,0,sizeof(server_addr));

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(sin.sin_port);

  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if(bind(serverSocket,
  (struct sockaddr*)&server_addr,sizeof(server_addr)) == -1)
  printf("Bind Failure\n");
  else
  printf("Bind Success:<%u>\n", serverSocket);
  




  while(1)
  {   
       listen(serverSocket,5);
       len=sizeof(struct sockaddr_in);

      client_connected=accept(serverSocket,
      (struct sockaddr*)&client_addr,&len);
  if (-1 != client_connected)
    printf("Connection accepted:<%u>\n", client_connected);

      while(1)
      {
      n = read(client_connected, received, sizeof(received));
      if( (strcmp(received,"q") == 0 ) || (strcmp(received,"Q") == 0 ))
      {
         printf("Wrong place...Socket Closed of Client\n");
         close(client_connected);
         break;
      }
      else{
      printf("\nUser:-%s", received);}
      printf("\nServer:-");
    //  memset(message, '\0', 10);
      gets(message);             
      write(client_connected, message, sizeof(message));
      if( (strcmp(message,"q") == 0 ) || (strcmp(message,"Q") == 0 ))
      {
         printf("Wrong place...Socket Closed of Client\n");
         close(client_connected);
         break;
      }  
      }
  }

  close(serverSocket); printf("\nServer Socket Closed !!\n");
}

void help(){
	printf("connect <destination> <port no>:\t Establishes a new TCP connection to the specified <destination> at the specified < port no>.\n\n");
	printf("terminate <connection id>:\t\t Will terminate the connection listed under the specified number when LIST is used to display all connections.\n\n");
	printf("send <connection id> <message>:\t\t Send the message to the host on the connection that is designated by the number when command “list” is used.\n\n");
	printf("myip:\t\t Display's the IP address of the process.\n\n");
	printf("myport:\t\t Display's the port on which the process is listening for incoming connections.\n\n");
	printf("list:\t\t Display's a numbered list of all the connections your process is part of.\n\n");
	printf("exit:\t\t Close all connections and terminate the process.\n\n");
	
}

// void myip(){
// 	int n;
//     struct ifreq ifr;
//     char array[] = "en1";
 
//     n = socket(AF_INET, SOCK_STREAM, 0);
//     //Type of address to retrieve - IPv4 IP address
//     ifr.ifr_addr.sa_family = AF_INET;
//     //Copy the interface name in the ifreq structure
//     strncpy(ifr.ifr_name , array , IFNAMSIZ - 1);
//     ioctl(n, SIOCGIFADDR, &ifr);
//     close(n);
//     //display result
//     printf("IP Address is %s\n" , inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr) );
// }

void myport(){

    struct sockaddr_in sin;
    printf("port number %d\n", htons(sin.sin_port));

}

void client(int p1){
    int clientSocket; /* Socket Decriptor for Client */
    struct sockaddr_in server_addr;
    struct hostent *ptrh;

    char message[100];
    char received[100];
    int n = 0;

    clientSocket=socket(AF_INET, SOCK_STREAM, 0);

    memset((char*)&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(p1);

    /*  bind(clientSocket, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)); */

    ptrh=gethostbyname("10.85.109.255");
    memcpy(&server_addr.sin_addr,ptrh->h_addr,ptrh->h_length);

    if( -1 == (connect(clientSocket, (struct sockaddr*)&server_addr, sizeof(server_addr)))) 
    { printf("\nServer Not Ready !!\n"); exit(1); }

while(1)
{
    printf("\nUser:-");
   // memset(message, '\0', 10);

    gets(message);

    n = write(clientSocket, message, strlen(message)+1);
if( (strcmp(message,"q") == 0 ) || (strcmp(message,"Q") == 0 ))
    {
       printf("Wrong place...Socket Closed\n");
       close(clientSocket);
       break;
    }

    //printf("Write:<%u>\n", n);

    read(clientSocket, received, sizeof(received));
    if( (strcmp(received,"q") == 0 ) || (strcmp(received,"Q") == 0 ))
    {
       printf("Wrong place...Socket Closed\n");
       close(clientSocket);
       break;
    }
    else
    printf("Server:- %s\n", received);



}

}




int main( int argc, char *argv[] )  {
  int n = 0;

  if(argc != 2){
   printf("Please enter the listening port number\n");
   exit(0);
  }
  else if(argc > 2){
  	printf("Please enter only listening port number\n");
  }
  else{
    server();
   printf("Type 'help' for more information\n");
   // printf(argv[1] );
   
   struct ifreq ifr;
    char array[] = "en1";
 
    n = socket(AF_INET, SOCK_STREAM, 0);
    //Type of address to retrieve - IPv4 IP address
    ifr.ifr_addr.sa_family = AF_INET;
    //Copy the interface name in the ifreq structure
    strncpy(ifr.ifr_name , array , IFNAMSIZ - 1);
    ioctl(n, SIOCGIFADDR, &ifr);
   while(1){
   	char command[100];
   	scanf("%[^\n]s",command);

   	if(strcmp(command, "exit") == 0){
   		exit(0);
   	}
   	else if(strcmp(command, "help") == 0){
   		help();
   	}
   	else if(strcmp(command, "myip") == 0){
      printf("IP Address is %s\n" , inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr) );
   		//myip();
   	}
   	else if(strcmp(command, "myport") == 0){
   		myport();
   	}
   	else if(strcmp(command, "connect") == 0){
      char s[50];
      strcpy(s,command);
      char* p1,p2;
      p1 = strtok(s," ");
      p1 = strtok(NULL, " ");
      p2 = strtok(NULL, " ");
      client(p1);
     
   			
   	}
   	// else if(strcmp(command, "list") == 0){
   	// 	list();
   	// }
   	// else if(strcmp(command, "terminate") == 0){
   	// 	terminater();
   	// }
   	// else if(strcmp(command, "send") == 0){
   	// 	sending();
   	// }
   	
   }
  }
  
  return 0;
}

