/*
 * --CS 4400 Assingment 1--
 *
 * Author: Aaron Pabst
 */

#include<stdio.h>
#include<stdlib.h>

/*
 * Determines whether a char is a digit or not.
 * 1 if true
 * 0 otherwise
 */
short isDig(char c){
  if(c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5'
     || c == '6' || c == '7' || c == '8' || c == '9')
    return 1;
  else
    return 0;
}

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

  char* returnVal = "";
  
  // Loop through all the chars in the array
  while(currChar != 0){ // Keep going until we hit a null terminator
    if(region == 0){
      if(currChar == 'm'){
	charCounter++;
      }
      else{
	if(charCounter % 2 == 0 || currChar != 'v'){ // Even number of m's, invalid
	  isMatch = 0;
	  break;
	}
	else{
	  charCounter = 1; // We know there's a V at this point
	  region++;
	}
      }
    }
    else if(region == 1){
      if(currChar == 'v'){
	charCounter++;
      }
      else{
	if(charCounter <= 1 || !isDig(currChar)){
	  isMatch = 0;
	  break;
	}
	else{
	  region++;
	  charCounter = 1;
	}
      }
    }
    else{
      if(isDig(currChar)){
	charCounter++;
      }
      else{
	isMatch = 0;
	break;
      }
    }

    i = i+1;
    currChar = str[i];
  }

  // Need one final check to make sure that we had the correct number of digits
  if((charCounter >= 1 && charCounter <= 3) && isMatch == 1){ // The string is a match
    return str;
  }
  else{ // The string is not a match
    return "";
  }
}

short isCap(char ch){
  return 0;
}

char* bMode(char* str){
  char currChar = str[0];
  int i = 0;
  short region = 0;
  short isMatch = 1;
  int charCounter = 0;
  char* x = malloc(6); // variable for stashing digit sequence
  short xNum = 1;
  int xInd = 2;

  while(currChar != 0){ // Spin through until we hit a null ptr
    if(region == 0){ // g sequence
      if(currChar == 'g'){
	charCounter++;
      }
      else{
	if(charCounter < 4 || !isDig(currChar)){
	  isMatch = 0;
	  break;
	}
	else{
	  region++;
	  *x = currChar; 
	  charCounter = 1;
	}
      }
    }
    else if (region == 1){ // decimal sequence/x sequence
      if(isDig(currChar)){
	charCounter++;
	*x = currChar;
	x++;
	xNum++;

	if(xNum > 5){ // We need this check to avoid segmentation faults
	  isMatch = 0;
	  break;
	}
      }
      else{
	if(charCounter > 3 || currChar != 'n'){ // Invalid
	  isMatch = 0;
	  break;
	}
	else{
	  region++;
	  charCounter = 1;
	}
      }
    }
    else if(region == 2){ // n sequence
      if(currChar == 'n'){
	charCounter++;
      }
      else{
	if(charCounter < 2 || charCounter > 5 || currChar != x[0]){
	  isMatch = 0;
	  break;
	}
	else{
	  charCounter = 1;
	  region++;
	}
      }
    }
    else if(region == 3){ // even positioned x sequnce
      // Same as even numbered indexes in x
      if(currChar == x[xInd]){
	xInd += 2; // Will I get a seg fault from this??
      }
      else{
	if(xInd > xNum || !isCap(currChar)){ // Invalid
	  isMatch == 0;
	  break;
	}
	else{
	  region++;
	}
      }
    }
    else if(region == 4){ // odd number of uppercase letters
      // Odd number of uppercase letters
      if(isCap(currChar)){
	charCounter++;
      }
      else{ // Auto fail
	isMatch = 0;
	break;
      }
    }

    i++;
    currChar = str[i];
  }
}

char* cMode(char* str){

}

int main(int argc, char** argv){
  if(argc != 3 && argc != 4){
    printf("ERROR: Incorrect number of arguements!\n");
    printf("Number of args: %d\n", argc);
    return 1;
  }

  char option;
  char* str;
  short tSelect = 0;

  if(argc == 3){ // If there's no -t flag
    option = argv[1][1];
    str = argv[2];
  }
  else{ // If there is a -t flag
    str = argv[4];
    if(argv[1][1] == 't')
      option = argv[2][1];
    else if(argv[2][1] == 't')
      option = argv[1][1];
    else{
      printf("ERROR: Invalid argument!\n");
      printf("%s\n", argv[1]);
      printf("%s\n", argv[2]);
      return 1;
    }
    tSelect = 1;
  }

  char* res;
  if(option == 'a'){
    char* res = aMode(str);
    printf("A mode\n");
  }
  else if(option == 'b'){

  }
  else if(option == 'c'){

  }

  if(res[0] == 0)
     printf("Invalid\n");
  else
    printf("%s\n", res);
} 
