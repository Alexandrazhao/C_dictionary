

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#define DELIM ":\t"
#define FILENAME  "filename.txt"
#define STANDARD_DEF "(No definition specified)"
#define SIZE 100


// Struct for a pair holding a key and a value
typedef struct Pair{
	char* myKey;
	int myID;
}Pair;

// Struct for a dictionary with a pointer to a pair as first and pointer to a dictionary as second
typedef struct Dictionary{
	Pair* first;
	struct Dictionary* second;
}Dictionary;

// "Constructor" for a key-value pair - returns a pointer to a pair.
Pair* newPair(char* key, int ID) { 
    Pair* p =  (Pair*)malloc(sizeof(Pair)); 
    p->myKey = (char*)malloc(sizeof(key));
    strncat(p->myKey, key, strlen(key));
    p->myID = ID; 
    return p; 
} 

// "Constructor" for dictionary - returns a pointer to a dictionary.
Dictionary* dict(){
	Dictionary* d = (Dictionary*)malloc(sizeof(Dictionary)); 
	d->first = NULL;
	d->second = NULL;
	return d;
}


// Method returning the size of a dictionary.
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

// Method returning the value of the given key if that key exists in the dictionary.
// If the key is not found then -1 is returned.
int dict_get(Dictionary* d, char* key){
 	if(d->first == NULL){
 		return -1;
 	} 	
 	Dictionary* tmp = d;
	while (tmp != NULL){
		if (strcmp((tmp->first)->myKey, key) == 0){
			return (tmp->first)->myID;
		}
		tmp = tmp->second;
	}
	return -1; 
}

// Method for adding new pairs into the dictionary
void dict_add(Dictionary* d, char* key, int ID){
	if (ID == -1){
		printf("-1 value reserved, please use another one\n");
		return;
	}
	if (key == NULL || ID == 0){
		printf("You cannot use null keyes and values\n");
		return;
	}
	// create a pair out of key and value
	Pair* pair = newPair(key, ID);
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
			(tmp->first)->myID = ID;
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


// Method for freeing all malloced memory from the dictionary.
// At the end makes the dictionary empty.
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
    long long total_elasped = 0;
	
	struct timeval start, end;
    //loop over every line in the file...
    while((read = getline(&line, &len, fd))!= -1){
        
        //... tokenize it based on the DELIM dividers...
        char* key = strtok(line, DELIM);
        while(key != NULL){
			
			gettimeofday(&start, NULL);
			
			int val = dict_get(d, key);
			if (val == -1){
				dict_add(d, key, 1);
			}else{
				dict_add(d, key, val+1);
			}
			gettimeofday(&end, NULL);
			long long start_msec = start.tv_sec*1000LL + start.tv_usec/1000; // calculate milliseconds
			long long end_msec = end.tv_sec*1000LL + end.tv_usec/1000; // calculate milliseconds
			total_elasped += end_msec-start_msec;
			key = strtok(NULL, " ");
		}
        
    }
    //fprintf(fd, dict_insert(d, "apple", "a fruit", 9));
    fclose(fd);
    free(line);
    printf("Time elasped of put in milliseconds: %lld\n", total_elasped);
	printf("Average time of put per argument in milliseconds %lld\n", (total_elasped)/dict_size(d));
	gettimeofday(&start, NULL);
	printf("dict_get(apple): %d\n", dict_get(d, "apple"));
	printf("dict_get(yes): %d\n", dict_get(d, "yes"));
	gettimeofday(&end, NULL);		
	long long start_msec = start.tv_sec*1000LL + start.tv_usec/1000; // calculate milliseconds
	long long end_msec = end.tv_sec*1000LL + end.tv_usec/1000; // calculate milliseconds
	total_elasped = end_msec-start_msec;
	printf("Time elasped of get in milliseconds: %lld\n", total_elasped);
	printf("Average time of get per argument in milliseconds %lld\n", (total_elasped)/6);
	printf("Size of c dictionary (Linked List): %d\n", dict_size(d));
    return 0;
}

int main(int argc, char *argv[]) {

	Dictionary* d = dict();
    char* fileName = "test.txt";
	load(d, fileName);
	
	dict_free(d);
	return 0;
}













