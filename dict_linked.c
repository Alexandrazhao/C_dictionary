#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//struct for a pair for a key and a value
typedef struct Pair{
    char* key;
    int value;
}Pair;

typedef struct Dictionary{
    Pair* first; //pointer to a pair
    struct Dictionary* second; //pointer to a dictionary
}Dictionary;


Pair* newPair(char* k, int val) { 
    Pair* p =  (Pair*)malloc(sizeof(Pair)); 
    p->key = (char*)malloc(sizeof(k));
    strncat(p->key, k, strlen(k));
    free(k);
    p->value = val; 
    return p; 
} 


Dictionary* dict(){
    Dictionary* d = (Dictionary*)malloc(sizeof(Dictionary));
    d->first = NULL;
    d->second = NULL; 
    return d; 
}

int dict_get(Dictionary* d, char* key){
    printf("%s Firday", key);
    if(d-> first == NULL){
        return -1;
    }
    Dictionary* tmp = d;
    while(tmp != NULL){
        if(strcmp((tmp->first)->key, key) == 0){
            return (tmp->first)->value;
        }
        tmp = tmp->second;
    }
    return -1;
}


int main(int argc, char *argv[]){
    Dictionary* d = dict();
    FILE *fd = fopen("test.txt", "r");
    if(fd == NULL){exit(EXIT_FAILURE);}
    char *line = NULL;
    ssize_t read;
    size_t len = 0;
    while((read = getline(&line, &len, fd))!= -1){
        char* token = strtok(line, "\t");
        //printf("%s", token);
        printf("%d", dict_get(d, token));
    
    }
    //close(fd);
    return 0;
}



