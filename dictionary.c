/*
Created by Karo Krajewska, Michał Cieślik, Yuxuan Zhao
May 18th 2020
Principles of Computing Systems - Keith O'hara
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#define DELIM ":\t\n"
#define FILENAME  "filename.txt"
#define STD_FILENAME "test.txt"
#define STANDARD_DEF "(No definition specified)"
#define MAX_DEF_LEN 100
#define MAX_KEY_LEN 20
#define BUFFER_SIZE_SAVE (100 + 20) * 10
#define SIZE 100

// Struct for a pair holding a key and a value
typedef struct Pair{
	char* myKey;
    char* myDef;
}Pair;

// Struct for a dictionary with a pointer to a pair as first and pointer to a dictionary as second
typedef struct Dictionary{
	Pair* first;
	struct Dictionary* second;
}Dictionary;

/*
Returns a pointer to a newly created pair - a "constructor"
*/
Pair* newPair(char* key, char* def) { 
    Pair* p =  (Pair*)malloc(sizeof(Pair)); 
    p->myKey = (char*)malloc(MAX_KEY_LEN*sizeof(char));
    p->myDef = (char*)malloc(MAX_DEF_LEN * sizeof(char));
    strncat(p->myKey, key, strlen(key));
    strncat(p->myDef, def, strlen(def));
    return p; 
} 

/*
Returns a pointer to a newly created dictionary - a "constructor"
*/
Dictionary* dict(){
	Dictionary* d = (Dictionary*)malloc(sizeof(Dictionary)); 
	d->first = NULL;
	d->second = NULL;
	return d;
}


/*
Returns the current size of the dictionary.
*/
int dict_size(Dictionary* d){
	int count = 0;
	if(d->first == NULL){
 		count = 0;
 	} 
	Dictionary* tmp = d;
	while (tmp != NULL){
		count++;
		tmp = tmp->second;
	}
	return count;
}

/*
Removes the word from the dictionary d based on the key provided.
*/
void dict_remove(Dictionary* d, char* key){
    int delete = 0; //a counter for how many words i delete
    Dictionary* temp = d;
    Dictionary* prev = NULL;
    while(temp != NULL && delete == 0){
        if(strcmp((temp->first)->myKey,key) == 0){
            Pair* remove = temp->first;
            if(prev != NULL){
                prev->second = temp->second;
                free(remove->myKey);
                free(remove);
                free(temp);
            }
        //if key is the first item in dictionary
            else{
                //if the dict has more than one item
                if(temp->second !=NULL){
                    temp->first = (temp->second)->first;
                    temp->second = (temp->second)->second;
                    free(remove->myKey);
                    free(remove);
                }
                else{//when dict has only one item
                    free(remove->myKey);
                    free(remove);
                    temp->first = NULL;
                }
            }
            delete = 1;
        }
        else{
            prev = temp;
            temp = temp->second;
        }
    }
}

/*
    Method for adding new pairs into the dictionary with the specified key and def
*/
void dict_add(Dictionary* d, char* key, char* def){
	if (key == NULL || def == 0){
		printf("You cannot use null keyes and values\n");
		return;
	}
    
	// create a pair out of key and value
	Pair* pair = newPair(key, def);
	// case when dictionary is empty
	if (d->first == NULL){
		d->first = pair;
		return;
	}
	// variable for keeping track if a key already exists in the dictionary
	int in_dict = 0;
	// loop throught the dictionary
	Dictionary* tmp = d;
	Dictionary* prev = NULL;
	while (tmp != NULL && in_dict==0){
		// if key exists in dictionary, change in_dict to 1 and update the value of the key with new value
		if (strcmp((tmp->first)->myKey, key) == 0){
			in_dict = 1;
            (tmp->first)->myDef = def;
		}
		prev = tmp;
		tmp = tmp->second;
	}
	// if a key hasn't been found then we create a new "node" with 'first' as created pair
	if (in_dict == 0){
		Dictionary* new = dict();
		new->first = pair;
		new->second = NULL;
		prev->second = new;
	}
    
}
/*
Displays all the words in the dictionary d in a specific format.
*/
void display_dict(Dictionary* d){
    Dictionary* h = d;
    printf("-----------------DICTIONARY--------------------\n\n");
    if(h->first== NULL){
        printf("The Dictionary is empty.\n");
        return;
    }
	while (h != NULL){
		Pair* x = h->first;
		printf("    -%s: '%s'\n", x->myKey, x->myDef);
		h = (h->second);
    }
}

/*
Method for freeing all malloced memory from the dictionary. 
*/
void dict_free(Dictionary* d){
	
	Dictionary* tmp = d;
	Dictionary* prev = NULL;
	while (tmp->second != NULL){
		prev = tmp;
		tmp = tmp->second;
	}
	free((tmp->first)->myKey);
	free(tmp->first);
	free(tmp);
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
Searches for the word specified in the dictionary d, and returns the definition if found. If the word
is not found in the dictionary, NULL is returned
*/
char* dict_search(Dictionary* d, char* key){
    Dictionary* h = d;
    if(h->first== NULL){
        return NULL;
    }
	while (h != NULL){
		Pair* x = h->first;
        if (0 == strcmp(x->myKey, key)){
            return x->myDef;
        } else if (h->second == NULL){
			return NULL;
		}		
		h = (h->second);
	}
	return NULL;
}
/* 
    Takes in an instance of the dictionary (Dictionary* d), and the name of the file that is supposed to
    be accessed (char* filename) and stores all of the words present in the file in the dictionary. Returns
    0 upon success and -1 when an error has arised. Requires a specific format.
    
    USAGE: should be used to process a large file containing words and definitions in the following format:
    key: definition\n
*/
int dict_load(Dictionary* d, char* filename){
    
    //open the given file and set up access
    FILE *fd = fopen(filename, "r");
    if(fd == NULL){
        printf("ERROR: No save file found.\n");
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
    
        if(def == NULL){
            def = STANDARD_DEF;
        }
        
        //...and then add them into the dictionary.
        dict_add(d, key, def);
    }
    fclose(fd);
    free(line);
    return 0;
}

/*
    Takes in an instance of the dictionary (Dictionary* d), and the name of the file that is supposed to
    be accessed (char* filename) and stores all of the words present in the file in the dictionary, and sets
    all definitions equal to STANDARD_DEF. Returns 0 upon success and -1 when an error has arised. 
    Does not require a specific format.
    
    USAGE: processing large text files with no "dictionary format"
*/
int dict_loadText(Dictionary* d, char* filename){
    
    //open the given file and set up access
    FILE *fd = fopen(filename, "r");
    if(fd == NULL){
        printf("FILE HANDLING ERROR IN load(): fd == NULL, or the file could not be opened\n");
        return -1;
    }
    char *line = NULL;
    ssize_t read;
    size_t len = 0;
    long long total_elasped = 0;
	
	struct timeval start, end;
    //loop over every line in the file...
    while((read = getline(&line, &len, fd))!= -1){
        
        //... tokenize it based on the DELIM dividers...
        char* key = strtok(line, DELIM);
        while(key != NULL){
			/*
			gettimeofday(&start, NULL);
			
			int val = dict_get(d, key);
			if (val == -1){
				dict_add(d, key, 1);
			}else{
				dict_add(d, key, val+1);
			}
            */
			gettimeofday(&end, NULL);
			long long start_msec = start.tv_sec*1000LL + start.tv_usec/1000; // calculate milliseconds
			long long end_msec = end.tv_sec*1000LL + end.tv_usec/1000; // calculate milliseconds
			total_elasped += end_msec-start_msec;
			key = strtok(NULL, " ");
		}
        
    }
    fclose(fd);
    free(line);
    printf("Time elasped of put in milliseconds: %lld\n", total_elasped);
	printf("Average time of put per argument in milliseconds %lld\n", (total_elasped)/dict_size(d));
	gettimeofday(&start, NULL);
	//printf("dict_get(apple): %d\n", dict_get(d, "apple"));
	//printf("dict_get(yes): %d\n", dict_get(d, "yes"));
	gettimeofday(&end, NULL);		
	long long start_msec = start.tv_sec*1000LL + start.tv_usec/1000; // calculate milliseconds
	long long end_msec = end.tv_sec*1000LL + end.tv_usec/1000; // calculate milliseconds
	total_elasped = end_msec-start_msec;
	printf("Time elasped of get in milliseconds: %lld\n", total_elasped);
	printf("Average time of get per argument in milliseconds %lld\n", (total_elasped)/6);
	printf("Size of c dictionary (Linked List): %d\n", dict_size(d));
    return 0;
}

/*
Changes the defintion of the word by removing the word and re-adding it with the desired def
*/
void dict_change_def(Dictionary* d, char* key, char* def){
    dict_remove(d,key);
    dict_add(d,key,def);
}

/*
Saves the current dictionary into a specified file, so that the user can access the contents of the
dictionary in between instances of the process
*/
void dict_save(Dictionary* d, char* filename){
    printf("Saving...\n");
    //open the given file and set up access
    FILE *fd = fopen(filename, "w");
    if(fd == NULL){
        printf("ERROR: No save file found.\n");
        return;
    }
    char line[BUFFER_SIZE_SAVE];
    ssize_t read;
    size_t len = 0;
    
    Dictionary* h = d;
    //if the dictionary is empty, throw an error:
    if(h->first== NULL){
        printf("ERROR: Dictionary empty, nothing to save.");
        return;
    }
    //saves the full dictionary in the file
    int i = 0;
	while (h != NULL){
        
		Pair* x = h->first;

        strcat(line,x->myKey);
        strcat(line,":");
        strcat(line,x->myDef);

		if (h->second != NULL){
			strcat(line,"\n");
		}		
		h = (h->second);
        i++;

        if(i > 8 || h == NULL){
            fputs(line, fd);
            i=0;
            strcpy(line, "");
        }
	}
    fclose(fd);
    return;
}
//-----------------------------------------USER INTERFACE------------------------------------------

void show_options(){
  printf("%s","\nPlease select an option by typing in a number corresponding with the option desired:\n");
  printf("%s","      (1) Add a new word\n      (2) Remove a word\n      (3) Add words from file\n");
  printf("%s","      (4) Display all words\n      (5) Change a definition of a word\n      (6) search for a word\n");
  printf("%s\n", "      (7) Exit and save.");
}



void ask_for_key(char** key){
  while(1){
    printf("%s", "Please enter the word you want to do the operation on: ");
    fgets(*key,100,stdin);
    
    if(*key==NULL){
      printf("ERROR: input cannot be null. Try again\n");
    }else if(strlen(*key) > MAX_KEY_LEN){
        printf("ERROR: the word is too long. Try again\n");
    }else {return;}
  }
}

void ask_for_def(char** def){
  while(1){
    printf("%s", "Please enter the definition corresponding with the word provided(max 100 characters): ");
    fgets(*def,100,stdin);
    
    if(*def==NULL){
      printf("ERROR: input cannot be null. Try again\n");
    } else if(strlen(*def) > MAX_DEF_LEN){
        printf("ERROR: the definition is too long. Try again\n");
    }
    else {return;}
  }
}

void ask_for_filename(char** filename){
    while(1){
    printf("%s", "Please enter the file name you'd like to access: ");
    fgets(*filename,100,stdin);
    
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


int user_add(Dictionary* d, char* key, char* def){
    dict_add(d,key,def);
    return 1;
}

void user_remove(Dictionary* d, char* key){
    dict_remove(d, key);
}

int user_loadText(Dictionary* d, char* filename){
    return dict_loadText(d,filename);
}

void user_display(Dictionary* d){
    display_dict(d);
}

int user_change_def(Dictionary* d, char* key, char* def){
    dict_change_def(d,key,def);
}

int user_search(Dictionary*d, char* key){
    char* def = dict_search(d,key);
    if (NULL == def){
        return -1;
    }else{
        printf("\n    -%s: '%s'\n",key,def);
        return 1;
    }
}

void user_load_std(Dictionary *d){
    dict_load(d,STD_FILENAME);
}

void user_save_std(Dictionary *d){
    dict_save(d,STD_FILENAME);
}

int main(int argc, char *argv[]){
    //----------------------------VARIABLES-----------------------------
    
    char userChoice[100];
    char* userKey[100];
    char* userDef[100];
    char* userFileName[100];
    int run = 1;

    //create an "instance" of the dictionary
    Dictionary* d = dict();
    
    //load all the words from a previous instance of the program
    user_load_std(d);

    //-----------------------Main Loop----------------------
    while(run){
        char* userKeyMal = (char*) malloc(100 * sizeof(char));
        char* userDefMal = (char*) malloc(100 * sizeof(char));
        char* userFileNameMal = (char*) malloc(100 * sizeof(char));

        show_options();
        fgets(userChoice,100,stdin);
    
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

            if(0 > user_add(d,userKeyMal, userDef)){
                printf("%s","ERROR: there was a problem with adding your word, please try again.\n");
            }

        }else if(0 == strcmp(userChoice, "2\n")){ //user wants to remove a word

            ask_for_key(& userKeyMal);
            remove_newline(userKeyMal);
            strcpy(userKey, userKeyMal);

            user_remove(d, userKeyMal);

        } else if(0 == strcmp(userChoice, "3\n")){ //user wants to load words from file

            ask_for_filename(& userFileNameMal); 
            remove_newline(userFileNameMal);
            strcpy(userFileName, userFileNameMal);
            printf("USER FILE NAME: '%s'\n", userFileName);

            if(0 > user_loadText(d, userFileName)){
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

            if(0 > user_search(d, userKey)){
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

    user_save_std(d);
    return 0;
}
