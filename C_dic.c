#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int add(char* word, char*def){} // adds a new word with a definition assigned to it; returns 1 on 
   //error, 0 on success

int add (char* word){} //adds a new word with null definition; returns 1 on error, 0 on success


char** search(char* word){} // searches for a word in the dictionary, returns an array of char*’s           
                                     //with the word, the definition and the ID in it. Returns the array 
          //filled with null’s if not found and 1’s upon error

char** search(int ID) // same as previous search, but searches using the ID

char* createID(char* word) {} // Creates a unique number based on the word given.

int load() {} //loads all the words from the file they are saved in by save() so they can be 
       //worked on. (probably uses system calls like write() etc)

int save() {} //updates the file with any changes to the dictionary so that the state can be 
       //saved in between instances of the process

Int remove(char* word){} // remove the word based on the actual word

int remove(char* ID){} // remove the word based on the ID



int remove(word){} //remove the word based on the actual word

If (search(word) == word):{           //search the word and delete it
remove(ID);
pop(word); // maybe using the pop() function here to remove the word
Return 0   //if success
}
Else If (word is not found OR the list is empty): 
return 1(error) // 



Int remove (int ID){} // remove the word regarding its id
If (search(word)==word):{ //search the word id and delete it
remove(word);
pop(ID); //using pop() function to remove the word
Return 0 //success
}
Else if (ID is not found OR list is empty):
Return 1 //wrong 


Int add (char[]* word, char[]* def, struct* dict){
    If (1){
        Dict.current = dict.current + 1;
        
        Dict.array[dict.current][0] = word;
        Dict.array[dict.current][1] = def;
        Dict.array[dict.current][2] = createID(&word);

        Return dict.current;
        Return 0;
    } else {
        printf(“Something went wrong”);
        Return 1;
    }
}


Struct Pair{
*char key;
Int value;
}Pair

Struct Dictionary{
Pair* first;
Struct Dictionary* second;
}Dictionary

//construct an empty dictionary
Dictionary* dict(){
Dictionary* d = (Dictionary*) malloc (sizeof(Dictionary));
*d.first = NULL;
*d.second = NULL; 
Return d;
}


Pair* newpair (char* key, int val){
    Pair* p = (Pair*)malloc(sizeof(Pair));
    *p.key = (char*)malloc(sizeof(key));
    *p.value = val;
    Return p;
}


Void add(Dictionary* d, char* key, int val){
Int _dict = 0;
Dictionary* prev = NULL;
//if the key is not found in the dict, we create a new pair
if(_dict == 0){
    Dictionary* new = NULL;
    *new.first = pair;
    *new.second = NULL;
    *prev.second = new;
}
}

int main(int argc, char *argv[]){
    Dictionary* d = dict();
    load();
    int val = get_dict();
    if (val == -1){
        
    }

}