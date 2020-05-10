#include <stdio.h>
#include <string.h>
#include <stdlib.h>

public final char* DELIM = ":\t";
public final char* FILENAME = "test.txt"; //change it to the file that is gonna be used for storing our info bw instances of the process
public final char* STANDARD_DEF = "(No definition specified)";

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
    Pair* p =  (Pair*)malloc(sizeof(Pair)); 
    p->myKey = (char*)malloc(100* sizeof(k));
    p->myDef = (char*)malloc(100* sizeof(d));
    
    printf("in newPair(), before, p->myKey: %s, key: %s \n", p->myKey, key);
    printf("in newPair(), before, p->myDef: %s, def: %s \n", p->myDef, def);
    
    strncat(p->myKey, key, strlen(key));
    strncat(p->myDef, def, strlen(def));
    
    printf("in newPair(), after, p->myKey: %s, key: %s \n", p->myKey, key);
    printf("in newPair(), after, p->myDef: %s, def: %s \n", p->myDef, def);
    
    //free(d);
    free(key);
    p->myDef = def; 
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
    Takes in an instance of the dictionary (Dictionary* d), the new word that is going to be added (char* d)
    and the definition that is supposed to be associated with the word (char* def) and it stores that as a new Pair
    "object" in the dictionary. Returns 0 when successful, and -1 when an error has arised.
*/
int dict_add(Dictionary* d, char* key, char* def){
    
    //makes sure the key is not null
    if(key == NULL){
        printf("ERROR: either the key or the definition is NULL\n");
        return -1;
    }
    
    //if the definition specified is NULL, sets it to STANDARD_DEF
    if(def == null){
        return dict_add(d,key,STANDARD_DEF);
    }
    
    //create the ID associated with the key
    int tempID = createID(key);
    
    //create a new pair with the key and def specified
    Pair* pair = newPair(key, def, tempID);
    printf("inside dict_add(), before adding");
    
    //handles the empty dictionary case
    if(d->first == NULL){
        printf("inside main(), case: first obj");
        d->first = pair;
        return 0;
    } else //handles any other case{ 
        
        printf("inside main(), case: second obj");
        Dictionary* new = dict();
        Dictionary* prev = NULL;
        new->first =pair;
        new->second =NULL;
        prev->second = new;
        return 0;
    }
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
    be accessed (char* filename) and stores all of the words present in the file in the dictionary. Returns
    0 upon success and -1 when an error has arised.
    
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
        printf("STRTOK TEST: key= %d\n",key);
        char* def = strtok(NULL, DELIM);
        
        if(def == NULL){
            def = STANDARD_DEF;
        }
        
        //...and then add them into the dictionary.
        int tempReturn = dict_add(d, key, def);
        if( tempReturn == -1){
            printf("ERROR in load(), in dict_add()");
        }
        
        printf("inside load(), key: %s, def: %s\n", key, def);
        printf("inside load(), return of dict_get(): %d\n", tempReturn);
    }
    return 0;
}

/*
    Takes in an instance of the dictionary (Dictionary* d),and stores all of the words present 
    in the dictionary specified. Returns 0 upon success and -1 when an error has arised.
    
    USAGE: should be used to load the dictionary from a different instance of the process.
*/
int load(Dictionary* d){
    return load(d, FILENAME);
}


int main(int argc, char *argv[]){
    //create an "instance" of the dictionary
    Dictionary* d = dict();
    
    //load the words from the file "test.txt" into the created dictionary
    char* fileName = "test.txt";
    load(d, fileName);
    //close(fd);
    return 0;
}




