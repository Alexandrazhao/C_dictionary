
int hash_add(char* word, char*def){} // adds a new word with a definition assigned to it; returns 1 on 
   //error, 0 on success; if there is no dictionary it creates

int hash_add (char* word){} //adds a new word with null definition; returns 1 on error, 0 on success


char** hash_search(char* word){} // searches for a word in the dictionary, returns an array of char*’s           
                                     //with the word, the definition and the ID in it. Returns the array 
          //filled with null’s if not found and 1’s upon error

char** hash_search(int ID) // same as previous search, but searches using the ID

char* hash_createID(char* word) {} // Creates a unique number based on the word given.

int hash_load() {} //loads all the words from the file they are saved in by save() so they can be 
       //worked on. (probably uses system calls like write() etc)

int hash_save() {} //updates the file with any changes to the dictionary so that the state can be 
       //saved in between instances of the process

int hash_remove(char* word){} // remove the word based on the actual word

int hash_remove(char* ID){} // remove the word based on the ID

int hash_start() {} // starts the user side of the program, so that the user can interact with the program. Calls load()

int hash_end() {} // ends the user side of the program, calls save()
