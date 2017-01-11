/*
 * --CS 4400 Assingment 1--
 *
 * Author: Aaron Pabst
 */

#include<stdio.h>
#include<stdlib.h>

int main(int argc, char** argv){
  if(argc != 3 && argc != 4){
    printf("ERROR: Incorrect number of arguements!\n");
    printf("Number of args: %d\n", argc);
    return 1;
  }

  char* option;
  char* str;
  short tSelect = 0;

  if(argc == 3){ // If there's no -t flag
    option = argv[1];
    str = argv[2];
  }
  else{ // If there is a -t flag
    str = argv[4];
    if(argv[1] == "-t")
      option = argv[2];
    else if(argv[2] == "-t")
      option = argv[1];
    else{
      printf("ERROR: Invalid argument!\n");
      return 1;
    }
    tSelect = 1;
  }

  if(option == "-a"){

  }
  else if(option == "-b"){

  }
  else if(option == "-c"){

  }
} 
