/*
 * --CS 4400 Assingment 1--
 *
 * Author: Aaron Pabst
 */

#include<stdio.h>
#include<stdlib.h>

/*
 * Returns a reformated str if the input matches the pattern.
 * Returns a string containing only a null terminator otherwise.
 */
char* aMode(char* str){
  char currChar = str[0];
  int i = 0;
  short isMatch = 1; // Start by assuming string is a match

  int charCounter = 0; // Used for counting how many times a char occurs
  int region = 0; // 0 for m, 1 for v, 2 for numerical

  // Loop through all the chars in the array
  while(currChar != 0){ // Keep going until we hit a null terminator
    if(region == 0){
      if(i == 0 && currChar != m){ // Bail if not valid
	isMatch = 0;
	break;
      }
      
    }
    else if(region == 1){

    }
    else{

    }

    i = i+1;
    currChar = str[i];
  }
}

char* bMode(char* str){

}

char* cMode(char* str){

}

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
      printf("%s\n", argv[1]);
      printf("%s\n", argv[2]);
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
