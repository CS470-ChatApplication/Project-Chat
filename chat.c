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
   	char command;
   	scanf("%s",command);
   	
   }
  }

  return 0;
}