#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//struct for a pair for a key and a value
typedef struct Pair{
    char* key;
    char* def;
    int ID;
}Pair;

typedef struct Dictionary{
    Pair* first; //pointer to a pair
    struct Dictionary* second; //pointer to a dictionary
}Dictionary;


Pair* newPair(char* k, char* d, int ID) { 
    Pair* p =  (Pair*)malloc(sizeof(Pair)); 
    p->key = (char*)malloc(100* sizeof(k));
    p->def = (char*)malloc(100* sizeof(d));
    
    printf("in newPair(), before, p->key: %s, k: %s \n", p->key, k);
    printf("in newPair(), before, p->def: %s, d: %s \n", p->def, d);
    
    strncat(p->key, k, strlen(k));
    strncat(p->def, d, strlen(d));
    
    printf("in newPair(), after, p->key: %s, k: %s \n", p->key, k);
    printf("in newPair(), after, p->def: %s, d: %s \n", p->def, d);
    
    //free(d);
    free(k);
    p->def = d; 
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

int dict_add(Dictionary* d, char* key, char* def){
    if(key == NULL || def == NULL){
        printf("ERROR: either the key or the definition is NULL\n");
        return -1;
    }
    
    //create a Pair buy key and the value
    int tempID = createID(key);
    Pair* pair = newPair(key, def, tempID);
    printf("inside dict_add(), before adding");
    //if the dict is empty
    if(d->first == NULL){
        printf("inside main(), case: first obj");
        d->first = pair;
        return 0;
    } else {
        printf("inside main(), case: second obj");
        Dictionary* new = dict();
        Dictionary* prev = NULL;
        new->first =pair;
        new->second =NULL;
        prev->second = new;
        return 0;
    }
}


int dict_get(Dictionary* d, char* key){
    printf("inside dict_get(), key:%s", key);
    if(d-> first == NULL){
        return -1;
    }
    printf("inside dict_get(), after if statement");
    Dictionary* tmp = d;
    while(tmp != NULL){
        if(strcmp((tmp->first)->key, key) == 0){
            return (tmp->first)->def;
        }
        tmp = tmp->second;
    }
    return -1;
}


int main(int argc, char *argv[]){
    Dictionary* d = dict();
    
    FILE *fd1 = fopen("test.txt", "r");
    if(fd1 == NULL){exit(EXIT_FAILURE);}
    char *line1 = NULL;
    ssize_t read1;
    size_t len1 = 0;
    while((read = getline(&line, &len, fd))!= -1){
        
        char* key = strtok(line, ":"); // token = "key: def"
        char* def = strtok(NULL, "\t");
        
        printf("inside main(), key: %s, def: %s\n", key, def);
        printf("inside main(), return of dict_get(): %d\n", dict_add(d, key, def));
        //printf("%s", dict_get_new(d, token));
    }
    //close(fd);
    return 0;
}




