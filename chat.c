#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>

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
   	
   }
  }

  return 0;
}

void help(){
	printf("HELP\n");
	
}