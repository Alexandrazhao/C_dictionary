#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DELIM ":\t"
#define FILENAME  "filename.txt"
#define STANDARD_DEF "(No definition specified)"
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


Pair* newPair(char* key, char* def, int ID) { 
    printf("in newPair() before malloc; :%s, %s\n", key, def);
    //size_t size_to_allocate = A_MEGABYTE;
    Pair* p =  (Pair*)malloc(sizeof(Pair)); 
    p->myKey = (char*)malloc(sizeof(key));
    p->myDef = (char*)malloc(sizeof(def));
    
    printf("in newPair(), before, p->myKey: %s, key: %s \n", p->myKey, key);
    printf("in newPair(), before, p->myDef: %s, def: %s \n", p->myDef, def);
    
    strncat(p->myKey, key, strlen(key));
    strncat(p->myDef, def, strlen(def));
    p->myKey = key;
    //free(def);
    p->myDef = def;
    printf("in newPair(), after, p->myKey: %s, key: %s \n", p->myKey, key);
    printf("in newPair(), after, p->myDef: %s, def: %s \n", p->myDef, def);
    return p; 
    
} 


Dictionary* dict(){
    Dictionary* d = (Dictionary*)malloc(sizeof(Dictionary));
    d->first = NULL;
    d->second = NULL; 
    return d; 
}

int createID(char* key){
    /*
    //create a var to keep track if a key is already existed in the dictionary
    int in_dict = 0;
    //loop through the dictionary
    Dictionary* tmp = d;
    Dictionary* prev = NULL;
    while (tmp != NULL && in_dict==0){
        if(strcmp((tmp->first)->key, key) == 0){
            in_dict = 1;
            (tmp->first)->value = val;
        }
        prev = tmp;
        tmp = tmp->second;
    }
    */
    return 20;
}

/*
    Takes in an instance of the dictionary (Dictionary* d), the new word that is going to be added (char* d),
    the definition that is supposed to be associated with the word (char* def) and it stores
    that as a new Pair "object" in the dictionary. Returns 0 when successful, and -1 when an error has arised.
*/
int dict_add(Dictionary* d, char* key, char* def){
    printf("in dict_add(); :%s, %s\n", key, def);
    
    //makes sure the key is not null
    if(key == NULL){
        printf("ERROR: either the key or the definition is NULL\n");
        return -1;
    }
    
    //if the definition specified is NULL, sets it to STANDARD_DEF
    if(def == NULL){
        return dict_add(d,key,STANDARD_DEF);
    }
    
    //create a new pair with the key and def specified
    printf("in dict_add() #2; :%s, %s\n", key, def);
    Pair* pair = newPair(key, def, ID);
    printf("inside dict_add(), before adding\n");
    
    //handles the empty dictionary case
    if(d->first == NULL){
        printf("inside main(), case: first obj\n");
        d->first = pair;
        return 0;
        }
    Dictionary* new = d;
    Dictionary* prev = NULL;
    //handles any other case
    while(new != NULL){
        if (strcmp((new->first)->myKey, key) == 0){
            (new->first)->myDef = def;
        }
        prev = new;
        new = new->second;
    }
    if(d->first != NULL){
        Dictionary* new = dict();
        printf("inside main(), case: second obj\n");
        new->first =pair;
        new->second =NULL;
        prev->second = new;
        return 0;
    }
}

/*
   like regular dict_add(), but sets the definition to STANDARD_DEF
*/
int dict_add_def(Dictionary* d, char* key){
    dict_add(d,key,STANDARD_DEF);
    return 0;
}

/*
    Searches for a word with the key (char* key) in the dictionary (Dictionary* d). Returns
*/
int dict_search(Dictionary* d, char* key){
    printf("inside dict_search(), key:%s", key);
    if(d-> first == NULL){
        return -1;
    }
    printf("inside dict_get(), after if statement");
    Dictionary* tmp = d;
    while(tmp != NULL){
        if(strcmp((tmp->first)->myKey, key) == 0){
            return (tmp->first)->myDef;
        }
        tmp = tmp->second;
    }
    return -1;
}

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
        printf("STRTOK TEST: key= %s\n",key);
        char* def = strtok(NULL, DELIM);
        printf("%s", def);
    
        if(def == NULL){
            def = STANDARD_DEF;
        }
        
        //...and then add them into the dictionary.
        int tempReturn = dict_add(d, key, def);
        if( tempReturn < 0){
            printf("ERROR in load(), in dict_add()");
        }
        
        printf("inside load(), key: %s, def: %s\n", key, def);
        printf("inside load(), return of dict_get(): %d\n", tempReturn);
    }
    //close(fd);
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
    printf("%s", "Please enter the word you'd like to add: ");
    fgets(*key,100,stdin);
    //printf("%s","\n");
    
    if(*key==NULL){
      printf("ERROR: input cannot be null. Try again\n");
    }else {return;}
  }
}

void ask_for_def(char** def){
  while(1){
    printf("%s", "Please enter the definition you'd like to add to the word provided: ");
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



int user_add(Dictionary* d, char* key, char* def){
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
        char* userFilenameMal = (char*) malloc(100 * sizeof(char));

        show_options();
        fgets(userChoice,100,stdin);

        printf("User choice: %s", userChoice);
    
        if(userChoice==NULL){
          printf("ERROR: input cannot be null");
          break;
        } else if(0 == strcmp(userChoice, "1\n")){ //user wants to add a single word

            ask_for_key(& userKeyMal);
            strcpy(userKey, userKeyMal);
            
            ask_for_def(& userDefMal);
            strcpy(userDef, userDefMal);

            if(0 > user_add(d,userKeyMal, userDef)){
                printf("%s","ERROR: there was a problem with adding your word, please try again.\n");
            }

        }else if(0 == strcmp(userChoice, "2\n")){ //user wants to remove a word

            ask_for_key(& userKeyMal);
            strcpy(userKey, userKeyMal);

            if(0 > user_remove(d, userKeyMal)){
                printf("%s","ERROR: there was a problem with removing your word, please try again.\n");
            }

        } else if(0 == strcmp(userChoice, "3\n")){ //user wants to load words from file

            ask_for_filename(& userFileNameMal); 
            strcpy(userFilename, userFilenameMal);

            if(0 > user_load(d, userFileName)){
                printf("%s","ERROR: there was a problem with adding your file, please try again.\n");
            }

        } else if(0 == strcmp(userChoice, "4\n")){ //user wants to see all words

            user_display(d);

        } else if(0 == strcmp(userChoice, "5\n")){ //user wants to change the definition of the word

            ask_for_key(& userKeyMal);
            strcpy(userKey, userKeyMal);

            ask_for_def(& userDefMal);
            strcpy(userDef, userDefMal);

            if(0 > user_change_def(d, userKey,userDef)){
                printf("%s","ERROR: there was a problem with changing your definition, please try again.\n");
            }

        }else if(0 == strcmp(userChoice, "6\n")){ //user is looking for a particular word

            ask_for_key(& userKeyMal);
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
        free(userFilenameMal);
    }
    
    //----------------------------TESTS-----------------------------------
    
    //load the words from the file "test.txt" into the created dictionary
    //load(d, userFileName);
    //dict_free(d);
    //close(fd);
    return 0;
}
