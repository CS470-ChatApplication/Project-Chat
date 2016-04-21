#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <netdb.h>

void help(){
	printf("connect <destination> <port no>:\t Establishes a new TCP connection to the specified <destination> at the specified < port no>.\n\n");
	printf("terminate <connection id>:\t\t Will terminate the connection listed under the specified number when LIST is used to display all connections.\n\n");
	printf("send <connection id> <message>:\t\t Send the message to the host on the connection that is designated by the number when command “list” is used.\n\n");
	printf("myip:\t\t Display's the IP address of the process.\n\n");
	printf("myport:\t\t Display's the port on which the process is listening for incoming connections.\n\n");
	printf("list:\t\t Display's a numbered list of all the connections your process is part of.\n\n");
	printf("exit:\t\t Close all connections and terminate the process.\n\n");
	
}


int main( int argc, char *argv[] )  {

  if(argc != 2){
   printf("Please enter the listening port number\n");
   exit(0);
  }
  else if(argc > 2){
  	printf("Please enter only listening port number\n");
  }
  else{
   printf("Type 'help' for more information\n");
   while(1){
   	char command[100];
   	scanf("%s",command);

   	if(strcmp(command, "exit") == 0){
   		exit(0);
   	}
   	else if(strcmp(command, "help") == 0){
   		help();
   	}
   	// else if(strcmp(command, "myip") == 0){
   	// 	myip();
   	// }
   	// else if(strcmp(command, "myport") == 0){
   	// 	myport();
   	// }
   	// else if(strcmp(command, "connect") == 0){
   	// 	connecting();	
   	// }
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

