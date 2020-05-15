#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DELIM ":\t"
#define FILENAME  "filename.txt"
#define STANDARD_DEF "(No definition specified)"
#define SIZE 100
/*
public static char* DELIM = ":\t";
public static char* FILENAME = "test.txt"; //change it to the file that is gonna be used for storing our info bw instances of the process
public static char* STANDARD_DEF = "(No definition specified)";
*/

//struct for a pair for a key and a value
typedef struct Pair{
    char* myKey;
    char* myDef;
    int myID;
}Pair;

typedef struct Dictionary{
    Pair* first; //pointer to a pair
    struct Dictionary* second; //pointer to a dictionary
}Dictionary;

struct Pair* hashArray[SIZE];
struct Pair* p; 

Pair* newPair(char* key, char* def, int ID) { 
    Pair* p =  (Pair*)malloc(sizeof(Pair)); 
    p->myKey = (char*)malloc(sizeof(key));
    p->myDef = (char*)malloc(sizeof(def));
    
    strncat(p->myKey, key, strlen(key));
    strncat(p->myDef, def, strlen(def));
    p->myKey = key;
    
    p->myDef = def;
    p->myID = ID;
    return p; 
} 

Dictionary* dict_next(Pair* pair, Dictionary* pointer){
    Dictionary* new = (Dictionary*)malloc(sizeof(Dictionary));
    new->first = pair;
    new->second = pointer; 
    return new; 
}

Dictionary* dict(){
    return dict_next(NULL,NULL);
}

int createID(char* key){
    
    int key_len = strlen(key);
    return key_len % SIZE;
}
/*
    Takes in an instance of the dictionary (Dictionary* d), the new word that is going to be added (char* d),
    the definition that is supposed to be associated with the word (char* def) and it stores
    that as a new Pair "object" in the dictionary. Returns 0 when successful, and -1 when an error has arised.
*/
int dict_add(Dictionary** d, char* key, char* def){
    
    //makes sure the key is not null
    if(key == NULL){
        printf("ERROR: either the key or the definition is NULL\n");
        return -1;
    }
    
    //if the definition specified is NULL, sets it to STANDARD_DEF
    if(def == NULL){
        return dict_add(d,key,STANDARD_DEF);
    }

    int ID = createID(key);
    
    //create a new pair with the key and def specified
    Pair* pair = newPair(key, def, ID);
    
    //handles the empty dictionary case
    Dictionary* pointer = *d;
    Dictionary* prev = NULL;

    printf("I AM GOING CRAZY %d\n", pointer->first);
    if(pointer->first == NULL){
        printf("In dict_add(), when the dictionary is empty\n");
        Dictionary* new = dict_next(pair, d);
        *d = new;
        printf("|      d      |    |               |\n");
        printf("|  %s  |  %s  | -> |  %s   | NULL  |\n", new->first->myKey, "d", new->second);
        printf("%s\n",new->first);
        return 0;
        }
    //handles any other case
    printf("I AM IN HERE OIDFGDRBGJDFBG\n");
    
    while(pointer->first != NULL){
        printf("While loop %s\n", pointer->first-);
        prev = pointer;
        pointer = pointer->second;
    }
    
    if(pointer->first != NULL){
        Dictionary* new2 = dict_next(pair, pointer);
        prev->second = new2;
        return 0;
    }
    
}

void display_dict(Dictionary* d){
    //int in_dict = 0;
    Dictionary* pointer = d;
    Dictionary* prev = NULL;
    //handles any other case
     while(pointer->first != NULL){
        prev = pointer;
        pointer = pointer->second;
        printf("I am in display_dict, my Key is: %s\n", (pointer->first)->myKey);
    }
   
}

/*
   like regular dict_add(), but sets the definition to STANDARD_DEF
*/
int dict_add_def(Dictionary* d, char* key){
    dict_add(d,key,STANDARD_DEF);
    return 0;
}

int dict_search(Dictionary* new, char* key){
    //printf("inside dict_search(), key:%s", key);
    //get the hash
    //int ID = createID(key);
    //dict_add(new, key, STANDARD_DEF);
    int ID = createID(key); //create the ID of the input word
    //dict_add_def(new,key); //call the dict_add to generate the struct of key and ID;
    if(new->first == NULL){
        return -1;
    }
    printf("inside dict_search the ID I generated: %d \n", ID);
    printf("in dict_search(), I found the first item in my key is %s\n", (new->first)->myDef);
    //printf("inside dict_get(), after if statement");
    /*
    Dictionary* tmp = d;
    while(tmp != NULL){
        if((tmp->first)->myID == ID){
            return (tmp->first)->myKey;
        }
        tmp = tmp->second;
    }
    return -1;
    */

   
   return 2;
}

/*
    Searches for a word with the key (char* key) in the dictionary (Dictionary* d). Returns
*/

/*
    Takes in an instance of the dictionary (Dictionary* d), and the name of the file that is supposed to
    be accessed (char* filename) and stores all of the words present in the file in the dictionary, and sets
    all definitions equal to STANDARD_DEF. Returns 0 upon success and -1 when an error has arised. 
    Does not require a specific format.
    
    USAGE: processing large text files with no "dictionary format"
*/
int loadText(Dictionary* d, char* filename){
    return -1;
}

/* 
    Takes in an instance of the dictionary (Dictionary* d), and the name of the file that is supposed to
    be accessed (char* filename) and stores all of the words present in the file in the dictionary. Returns
    0 upon success and -1 when an error has arised. Requires a specific format.
    
    USAGE: should be used to process a large file containing words and definitions in the following format:
    key: definition\n
*/
int load(Dictionary* d, char* filename){
    
    //open the given file and set up access
    FILE *fd = fopen(filename, "r");
    if(fd == NULL){
        printf("FILE HANDLING ERROR IN load(): fd == NULL, or the file could not be opened\n");
        return -1;
    }
    char *line = NULL;
    ssize_t read;
    size_t len = 0;
    
    //loop over every line in the file...
    while((read = getline(&line, &len, fd))!= -1){
        
        //... tokenize it based on the DELIM dividers...
        char* key = strtok(line, DELIM);
        //printf("STRTOK TEST: key= %s\n",key);
        char* def = strtok(NULL, DELIM);
        //printf("%s", def);
    
        if(def == NULL){
            def = STANDARD_DEF;
        }
        
        //...and then add them into the dictionary.
        
        int tempReturn = dict_add(d, key, def);
        if( tempReturn < -1){
            printf("ERROR in load(), in dict_add()");
        }
        
        //printf("inside load(), key: %s, def: %s\n", key, def);
        //printf("inside load(), return of dict_get(): %d\n", tempReturn);
    }
    //fprintf(fd, dict_insert(d, "apple", "a fruit", 9));
    fclose(fd);
    free(line);
    return 0;
}
/*
    Saves the given dictionary (Dictionary* d) in a file so it's accessible throughout instances of the program
*/
int save(Dictionary* d){
    /*TO-DO: write a method that saves the dictionary in the following format:
    "key: definition: ID\n"
    */
    return 0;
}

/*
    like regular load, but load the Dictionary in a standard file FILENAME
    
    USAGE: should be used to load the dictionary from a different instance of the process.
*/
int load_std(Dictionary* d){
    return load(d, FILENAME);
}


//-----------------------------------------USER INTERFACE------------------------------------------

void show_options(){
  printf("%s","Please select an option by typing in a number corresponding with the option desired:\n");
  printf("%s","      (1) Add a new word\n      (2) Remove a word\n     (3) Add words from file\n");
  printf("%s","      (4) Display all words\n     (5) Change a definition of a word\n   (6) search for a word\n");
  printf("%s\n", "   (7) Exit and save.");
}



void ask_for_key(char** key){
  while(1){
    printf("%s", "Please enter the word you want to do the operation on: ");
    fgets(*key,100,stdin);
    //printf("%s","\n");
    
    if(*key==NULL){
      printf("ERROR: input cannot be null. Try again\n");
    }else {return;}
  }
}

void ask_for_def(char** def){
  while(1){
    printf("%s", "Please enter the definition corresponding with the word provided: ");
    fgets(*def,100,stdin);
    printf("%s","\n");
    
    if(*def==NULL){
      printf("ERROR: input cannot be null. Try again\n");
    }else {return;}
  }
}

void ask_for_filename(char** filename){
    while(1){
    printf("%s", "Please enter the file name you'd like to access: ");
    fgets(*filename,100,stdin);
    printf("%s","\n");
    
    if(*filename==NULL){
      printf("ERROR: input cannot be null. Try again\n");
    }else {return;}
  }
}

void remove_newline(char* line){
    int new_line =strlen(line)-1;
    if (line[new_line] == '\n'){
        line[new_line] = NULL;
    }
}


int user_add(Dictionary** d, char* key, char* def){
    return dict_add(d,key,def);
}

int user_remove(Dictionary* d, char* key){
    return -1;//dict_remove(d, key);
}

int user_load(Dictionary* d, char* filename){
    return load(d,filename);
}

int user_display(Dictionary* d){
    return -1;
}

int user_change_def(Dictionary* d, char* key, char* def){
    return -1;
}

char* user_search(Dictionary*d, char* key, char** def){
    return &def;
}

int main(int argc, char *argv[]){
    //----------------------------VARIABLES-----------------------------
    
    char userChoice[100];
    char* userKey[100];
    char* userDef[100];
    char* userFileName = "test.txt";
    int run = 1;

    //create an "instance" of the dictionary
    Dictionary* d = dict();
    
    //load all the words from a previous instance of the program
    load_std(d);

    //-----------------------Main Loop----------------------
    while(run){
        char* userKeyMal = (char*) malloc(100 * sizeof(char));
        char* userDefMal = (char*) malloc(100 * sizeof(char));
        char* userFileNameMal = (char*) malloc(100 * sizeof(char));

        show_options();
        fgets(userChoice,100,stdin);

        printf("User choice: %s", userChoice);
    
        if(userChoice==NULL){
          printf("ERROR: input cannot be null");
          break;
        } else if(0 == strcmp(userChoice, "1\n")){ //user wants to add a single word

            ask_for_key(& userKeyMal);
            remove_newline(userKeyMal);
            strcpy(userKey, userKeyMal);
            

            ask_for_def(& userDefMal);
            remove_newline(userDefMal);
            strcpy(userDef, userDefMal);

            if(0 > user_add(& d,userKeyMal, userDef)){
                printf("%s","ERROR: there was a problem with adding your word, please try again.\n");
            }

        }else if(0 == strcmp(userChoice, "2\n")){ //user wants to remove a word

            ask_for_key(& userKeyMal);
            remove_newline(userKeyMal);
            strcpy(userKey, userKeyMal);

            if(0 > user_remove(d, userKeyMal)){
                printf("%s","ERROR: there was a problem with removing your word, please try again.\n");
            }

        } else if(0 == strcmp(userChoice, "3\n")){ //user wants to load words from file

            ask_for_filename(& userFileNameMal); 
            remove_newline(userFileNameMal);
            strcpy(userFileName, userFileNameMal);

            if(0 > user_load(d, userFileName)){
                printf("%s","ERROR: there was a problem with adding your file, please try again.\n");
            }

        } else if(0 == strcmp(userChoice, "4\n")){ //user wants to see all words

            user_display(d);

        } else if(0 == strcmp(userChoice, "5\n")){ //user wants to change the definition of the word

            ask_for_key(& userKeyMal);
            remove_newline(userKeyMal);
            strcpy(userKey, userKeyMal);

            ask_for_def(& userDefMal);
            remove_newline(userDefMal);
            strcpy(userDef, userDefMal);

            if(0 > user_change_def(d, userKey,userDef)){
                printf("%s","ERROR: there was a problem with changing your definition, please try again.\n");
            }

        }else if(0 == strcmp(userChoice, "6\n")){ //user is looking for a particular word

            ask_for_key(& userKeyMal);
            remove_newline(userKeyMal);
            strcpy(userKey, userKeyMal);

            if(0 > user_search(d, userKey,& userDef)){
                printf("%s","ERROR: there was a problem with finding your word, please try again.\n");
            }

        }else if(0 == strcmp(userChoice, "7\n")){
            run = 0;
        }else{
            printf("ERROR: choice not recognized. Please try again");
        }
        free(userKeyMal);
        free(userDefMal);
        free(userFileNameMal);
    }
    
    //----------------------------TESTS-----------------------------------
    
    //load the words from the file "test.txt" into the created dictionary
    //load(d, userFileName);
    //dict_free(d);
    //close(fd);
    return 0;
}
