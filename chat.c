#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <netdb.h>

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
   	else if(strcmp(command, "myip") == 0){
   		myip();
   	}
   	else if(strcmp(command, "myport") == 0){
   		myport();
   	}
   	else if(strcmp(command, "connect") == 0){
   		connect();	
   	}
   	else if(strcmp(command, "list") == 0){
   		list();
   	}
   	else if(strcmp(command, "terminate") == 0){
   		terminater();
   	}
   	else if(strcmp(command, "send") == 0){
   		send();
   	}
   	
   }
  }

  return 0;
}

void help(){
	printf("HELP\n");
	
}

void myip(){

}

void myport(){

}

void connect(){

}

void list(){

}

void terminate(){

}

void send(){
	
}