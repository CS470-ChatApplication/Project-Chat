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
   
  int n=0; 
  char message[100],received[100];

  serverSocket=socket(AF_INET, SOCK_STREAM, 0);

  memset((char*)&server_addr,0,sizeof(server_addr));

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = ntohs(51791);

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

 // close(serverSocket); printf("\nServer Socket Closed !!\n");
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
    printf("port number %d\n", ntohs(sin.sin_port));

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

void listening_port(char *argv[]){
  int ret, fd;
    
    struct sockaddr_in sa_loc;

     fd = socket(AF_INET, SOCK_STREAM, 0);
     
  memset(&sa_loc, 0, sizeof(struct sockaddr_in));
    sa_loc.sin_family = AF_INET;
    sa_loc.sin_port = htons(argv[1]);
    sa_loc.sin_addr.s_addr = inet_addr("192.168.1.3");

    ret = bind(fd, (struct sockaddr *)&sa_loc, sizeof(struct sockaddr));
    listen(fd,0);
   
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
    
    listening_port(argv);


   while(1){
   	char command[100];
    
    // scanf("%s", &command);
    char cmd[100],arg1[100];
    int arg2;  
    fgets(command,sizeof(command),stdin);
    sscanf(command,"%s %s %d",&cmd,&arg1, &arg2);

   // fgets(command,sizeof(command),stdin);
    //sscanf(command, "%[\n]", command);


   	if(strcmp(cmd, "exit") == 0){
   		exit(0);
   	}
   	else if(strcmp(cmd, "help") == 0){
   		help();
   	}
   	else if(strcmp(cmd, "myip") == 0){
      printf("IP Address is %s\n" , inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr) );
   		//myip();
   	}
   	else if(strcmp(cmd, "myport") == 0){
   		myport();
   	}
    
   	else if(strcmp(cmd, "connect") == 0){
     //   int clientid;
     //  char msgsend[512], msgrecv[512];
     //  struct sockaddr_in client; 

     //  memset(msgrecv, '0', sizeof(msgrecv));
     //  clientid = socket(AF_INET, SOCK_STREAM, 0);

     //  client.sin_family = AF_INET;
     // client.sin_addr.s_addr = inet_addr(arg1);
     // client.sin_port = htons(arg2);

     // bind(clientid, (struct sockaddr*)&server, sizeof(server));
   		// if(connect(clientid, (struct sockaddr*)&client, sizeof(client)) <0){
     //    printf("Connection Failed!");
     //  }
     int clientSocket; /* Socket Decriptor for Client */
    struct sockaddr_in server_addr;
    struct hostent *ptrh;
    struct sockaddr_in sin;

    char message[100];
    char received[100];
    int n = 0;

    clientSocket=socket(AF_INET, SOCK_STREAM, 0);

    memset((char*)&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons("1234");

    /*  bind(clientSocket, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)); */


    ptrh=gethostbyname(arg1);
    memcpy(&server_addr.sin_addr,ptrh->h_addr,ptrh->h_length);

    if( -1 == (connect(clientSocket, (struct sockaddr*)&server_addr, sizeof(server_addr)))) 
    { 
      printf("\nServer Not Ready !!\n");
    }

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

