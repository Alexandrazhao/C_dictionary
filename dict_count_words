
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

// Struct for a dictionary with a pointer to a pair as first and pointer to a dictionary as next
typedef struct Dictionary{
	Pair* first;
	struct Dictionary* next;
}Dictionary;

// "Constructor" for a key-value pair - returns a pointer to a pair.
Pair* newPair(char* k, int val) { 
    Pair* p =  (Pair*)malloc(sizeof(Pair)); 
    p->myKey = (char*)malloc(sizeof(k));
    strncat(p->myKey, k, strlen(k));
    //free(k);
    p->myID = val; 
    return p; 
} 

// "Constructor" for dictionary - returns a pointer to a dictionary.
Dictionary* dict(){
	Dictionary* d = (Dictionary*)malloc(sizeof(Dictionary)); 
	d->first = NULL;
	d->next = NULL;
	return d;
}

// Method for checking if dictionary is empty. On true it returns 1 and on false 0.
int dict_isEmpty(Dictionary* d){
	if (d->first == NULL){
		return 1;	
	}else{
		return 0;	
	}
}

// Method returning the size of a dictionary.
int dict_size(Dictionary* d){
	int count = 0;
	if(d->first == NULL){
 		count = 0;
 	} 
	Dictionary* h = d;
	while (h != NULL){
		count++;
		h = h->next;
	}
	return count;
}

// Method returning the value of the given key if that key exists in the dictionary.
// If the key is not found then -1 is returned.
int dict_get(Dictionary* d, char* key){
 	if(d->first == NULL){
 		return -1;
 	} 	
 	Dictionary* h = d;
	while (h != NULL){
		if (strcmp((h->first)->myKey, key) == 0){
			return (h->first)->myID;
		}
		h = h->next;
	}
	return -1; 
}

// Method for adding new pairs into the dictionary
void dict_put(Dictionary* d, char* key, int val){
	if (val == -1){
		printf("-1 value reserved, please use another one\n");
		return;
	}
	if (key == NULL || val == 0){
		printf("You cannot use null keyes and values\n");
		return;
	}
	// create a pair out of key and value
	Pair* pair = newPair(key, val);
	// case when dictionary is empty
	if (d->first == NULL){
		d->first = pair;
		return;
	}
	// variable for keeping track if a key already exists in the dictionary
	int in_dict = 0;
	// loop throught the dictionary
	Dictionary* h = d;
	Dictionary* prev = NULL;
	while (h != NULL && in_dict==0){
		// if key exists in dictionary, change in_dict to 1 and update the value of the key with new value
		if (strcmp((h->first)->myKey, key) == 0){
			in_dict = 1;
			(h->first)->myID = val;
		}
		prev = h;
		h = h->next;
	}
	// if a key hasn't been found then we create a new "node" with 'first' as created pair
	if (in_dict == 0){
		Dictionary* new = dict();
		new->first = pair;
		new->next = NULL;
		prev->next = new;
	}
}

// This method removes a pair specified by the key from the dictionary
void dict_remove(Dictionary* d, char* key){
	// variable for keeping track if a key has been deleted when found
	int deleted = 0;
	// loop through dictionary
	Dictionary* h = d;
	Dictionary* prev = NULL;
	while (h != NULL && deleted == 0){
		// if key found, delete the pair
		if (strcmp((h->first)->myKey, key) == 0){
			Pair* rmv = h->first;
			// key is not the first item in the dictionary   
			if (prev != NULL){
				prev->next = h->next;
				free(rmv->myKey);
				free(rmv);
				free(h);
			}
			// key is the first item in dictionary
			else{
				// case when dictionary has more than 1 item
				if (h->next != NULL){
					h->first = (h->next)->first;
					h->next = (h->next)->next;
					free(rmv->myKey);
					free(rmv);
				}
				// case when dictionary has only one item we are trying to delete
				else{
					free(rmv->myKey);
					free(rmv);
					h->first = NULL;
				}
			}
			// change the variable to 1 -> key has been deleted
			deleted = 1;
		}
		// continue looping
		else{
			prev = h;
			h = h->next;
		}
	}
	// we looped thorugh whole dictionary and haven't found the key
	if (deleted == 0){printf("Key not in dictionary\n");}

}

// Mehtod for printing out the contents of a dictionary. 
// Format: {key1=val1, key2=val2 ...}
void dict_print(Dictionary* d){
	
	Dictionary* h = d;
	if(h->first==NULL){
		printf("{}\n");
		return;
	}
	printf("{");
	while (h != NULL){
		Pair* x = h->first;
		printf("%s=%d", x->myKey, x->myID);
		if (h->next != NULL){
			printf(", ");
		}		
		h = (h->next);

	}
	printf("}");
	printf("\n");
}

// Method for freeing all malloced memory from the dictionary.
// At the end makes the dictionary empty.
void dict_free(Dictionary* d){
	
	Dictionary* h = d;
	Dictionary* prev = NULL;
	while (h->next != NULL){
		prev = h;
		h = h->next;
	}
	free((h->first)->myKey);
	free(h->first);
	free(h);
	if(prev != NULL){
		prev->next = NULL;
		dict_free(d);
	}else{
		Pair* to_free = d->first;
		d->first = NULL;
		d->next = NULL;
	}
}

int main(int argc, char *argv[]) {

	Dictionary* d = dict();
	
	//FILE *fd = fopen("macbeth-processed.txt","r");
    FILE *fd = fopen("test.txt","r");
	if(fd == NULL){exit(EXIT_FAILURE);}
	char *line = NULL;
	ssize_t read;
	size_t len = 0;
	long long total_elasped = 0;
	
	struct timeval start, end;

	while ((read=getline(&line, &len, fd)) != -1){
		char* token = strtok(line, " \t");
		while(token != NULL){
			
			gettimeofday(&start, NULL);
			
			int val = dict_get(d, token);
			if (val == -1){
				dict_put(d, token, 1);
			}else{
				dict_put(d, token, val+1);
			}
			gettimeofday(&end, NULL);
			long long start_msec = start.tv_sec*1000LL + start.tv_usec/1000; // calculate milliseconds
			long long end_msec = end.tv_sec*1000LL + end.tv_usec/1000; // calculate milliseconds
			total_elasped += end_msec-start_msec;
			token = strtok(NULL, " ");
		}
	}
	fclose(fd);
	free(line);
	//dict_print(d);
	//printf("\n");
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
	dict_free(d);
	return 0;
}








