#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "user.h"
#include "dict_linked.c"

void show_options(){
  printf("%s","Please select an option by typing in a number corresponding with the option desired:\n");
  printf("%s","      (1) Add a new word\n      (2) Remove a word\n     (3) Add words from file\n");
  printf("%s","      (4) Display all words\n     (5) Change a definition of a word\n");
}

void ask_for_key(char** key){
  while(0){
    printf("%s", "Please enter the word you'd like to add: ");
    fgets(&key,100,stdin);
    printf("%s","\n");
    
    if(&key==NULL){
      printf("ERROR: input cannot be null. Try again\n");
    }else {return;}
  }
}

void ask_for_def(char** def){
  while(0){
    printf("%s", "Please enter the definition you'd like to add to the word provided: ");
    fgets(&def,100,stdin);
    printf("%s","\n");
    
    if(&def==NULL){
      printf("ERROR: input cannot be null. Try again\n");
    }else {return;}
  }
}

int user_add(char* key, char* def){
  
  return -1;
}



int main(int argc, char *argv[])
{
  char* userChoice[100];
  char* userKey[100];
  char* userDef[100];
  
  //-----------------------Main Loop----------------------
  while(1){
    show_options();
    fgets(userChoice,100,stdin);
    
    if(userChoice==NULL){
      printf("ERROR: input cannot be null");
      break;
    } else if(0 == strcmp(userChoice, "1")) //user wants to add a single word
    {
      ask_for_key(userKey*);
      ask_for_def(userDef*);
      user_add(userKey, userDef);
    }
    
    
    
  }
  
  
}
