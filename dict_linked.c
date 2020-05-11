#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DELIM ":\t"
#define FILENAME  "test.txt"
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
    Pair* p =  (Pair*)malloc(1000*sizeof(Pair)+1); 
    p->myKey = (char*)malloc(1000*sizeof(key)+1);
    p->myDef = (char*)malloc(1000*sizeof(def)+1);
    
    printf("in newPair(), before, p->myKey: %s, key: %s \n", p->myKey, key);
    printf("in newPair(), before, p->myDef: %s, def: %s \n", p->myDef, def);
    
    strncat(p->myKey, key, strlen(key));
    strncat(p->myDef, def, strlen(def));
    //free(key);
    p->myKey = key;
    //free(def);
    //p->myDef = def;
    printf("in newPair(), after, p->myKey: %s, key: %s \n", p->myKey, key);
    printf("in newPair(), after, p->myDef: %s, def: %s \n", p->myDef, def);
    return p; 
    free(key);
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


void dict_free(Dictionary* d){
    Dictionary* h = d;
	Dictionary* prev = NULL;
	while (h->second != NULL){
		prev = h;
		h = h->second;
	}
	free((h->first)->myKey);
	free(h->first);
	free(h);
	if(prev != NULL){
		prev->second = NULL;
		dict_free(d);
	}else{
		Pair* to_free = d->first;
		d->first = NULL;
		d->second = NULL;
	}

}

/*
    Takes in an instance of the dictionary (Dictionary* d), the new word that is going to be added (char* d),
    the definition that is supposed to be associated with the word (char* def) and the ID (int ID) and it stores
    that as a new Pair "object" in the dictionary. Returns 0 when successful, and -1 when an error has arised.
*/
int dict_add(Dictionary* d, char* key, char* def, int ID){
    printf("in dict_add(); :%s, %s\n", key, def);
    
    //makes sure the key is not null
    if(key == NULL){
        printf("ERROR: either the key or the definition is NULL\n");
        return -1;
    }
    
    //if the ID is NULL, give a proper ID
    if(ID == NULL){
        return dict_add_id(d,key,def);
    }
    
    //if the definition specified is NULL, sets it to STANDARD_DEF
    if(def == NULL){
        return dict_add_id(d,key,STANDARD_DEF);
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
   like regular dict_add(), but creates a new ID for the word
*/
int dict_add_id(Dictionary* d, char* key, char* def){
    printf("in dict_add_id(); :%s, %s\n", key, def);
    dict_add(d,key,def,createID(key));
    return 0;
}

/*
   like regular dict_add(), but sets the definition to STANDARD_DEF
*/
int dict_add_def(Dictionary* d, char* key, int ID){
    dict_add(d,key,STANDARD_DEF,ID);
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
        int tempReturn = dict_add_id(d, key, def);
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


int main(int argc, char *argv[]){
    //create an "instance" of the dictionary
    Dictionary* d = dict();
    
    //load all the words from a previous instance of the program
    //load(d);
    
    //load the words from the file "test.txt" into the created dictionary
    char* fileName = "test.txt";
    load(d, fileName);
    dict_free(d);
    //close(fd);
    return 0;
}



