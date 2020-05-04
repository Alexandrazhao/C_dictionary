/*
  Implements a minimal shell.  The shell simply finds executables by
  searching the directories in the PATH environment variable.
  Specified executable are run in a child process.

  AUTHOR: Yuxuan (Alexandra) Zhao
*/

#include "bshell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>



int parsePath(char *dirs[]);
char *lookupPath(char *fname, char **dir,int num);
int parseCmd(char *cmdLine, Command *cmd);

/*
  Read PATH environment var and create an array of dirs specified by PATH.

  PRE: dirs allocated to hold MAX_ARGS pointers.
  POST: dirs contains null-terminated list of directories.
  RETURN: number of directories.

  NOTE: Caller must free dirs[0] when no longer needed.

*/
int parsePath(char *dirs[]) {
  int i, numDirs;
  char *pathEnv;
  char *thePath;
  char *nextcharptr; /* point to next char in thePath */

  for (i = 0; i < MAX_PATHS; i++) dirs[i] = NULL;
  pathEnv = (char *) getenv("PATH");

  if (pathEnv == NULL) return 0; /* No path var. That's ok.*/

  /* for safety copy from pathEnv into thePath */
  int str_len = strlen(pathEnv);
  thePath = (char *)malloc(sizeof(char)); //dynamically allocate memory 
  strcpy(thePath,pathEnv);

#ifdef DEBUG
  printf("Path: %s\n",thePath);
#endif

  /* Now parse thePath */
  nextcharptr = thePath;

  /* 
     Find all substrings delimited by DELIM.  Make a dir element
     point to each substring.
     TODO: approx a dozen lines.
  */
 
  numDirs = 0;
  char *dir = strtok(thePath,DELIM);
  for(;dir != NULL;){
    dirs[numDirs] = dir;
    dir = strtok(NULL, DELIM);
    numDirs = numDirs+1;
    }
  

  /* Print all dirs */
#ifdef DEBUG
  for (i = 0; i < numDirs; i++) {
    printf("%s\n",dirs[i]);
  }
#endif
  //free(thePath);
  return numDirs;
}


/*
  Search directories in dir to see if fname appears there.  This
  procedure is correct!

  PRE dir is valid array of directories
  PARAMS
   fname: file name
   dir: array of directories
   num: number of directories.  Must be >= 0.

  RETURNS full path to file name if found.  Otherwise, return NULL.

  NOTE: Caller must free returned pointer.
*/

char *lookupPath(char *fname, char **dir,int num) {
  char *fullName; // resultant name
  int maxlen; // max length copied or concatenated.
  int i;

  fullName = (char *) malloc(MAX_PATH_LEN);
  /* Check whether filename is an absolute path.*/
  if (fname[0] == '/') {
    strncpy(fullName,fname,MAX_PATH_LEN-1);
    if (access(fullName, F_OK) == 0) {
      return fullName;
    }
  }

  /* Look in directories of PATH.  Use access() to find file there. */
  else {
    for (i = 0; i < num; i++) {
      // create fullName
      maxlen = MAX_PATH_LEN - 1;
      strncpy(fullName,dir[i],maxlen);
      maxlen -= strlen(dir[i]);
      strncat(fullName,"/",maxlen);
      maxlen -= 1;
      strncat(fullName,fname,maxlen);
      // OK, file found; return its full name.
      if (access(fullName, F_OK) == 0) {
	return fullName;
      }
    }
  }
  fprintf(stderr,"%s: command not found\n",fname);
  free(fullName);
  return NULL;
}

/*
  Parse command line and fill the cmd structure.

  PRE 
   cmdLine contains valid string to parse.
   cmd points to valid struct.
  PST 
   cmd filled, null terminated.
  RETURNS arg count

  Note: caller must free cmd->argv[0..argc]

*/
int parseCmd(char *cmdLine, Command *cmd) {
  int argc = 0; // arg count
  char* token;
  int i = 0;

  token = strtok(cmdLine, SEP);
  while (token != NULL && argc < MAX_ARGS){    
    cmd->argv[argc] = strdup(token);
    token = strtok (NULL, SEP);
    argc++;
  }

  cmd->argv[argc] = NULL;  
  cmd->argc = argc;

#ifdef DEBUG
  printf("CMDS (%d): ", cmd->argc);
  for (i = 0; i < argc; i++)
    printf("CMDS: %s",cmd->argv[i]);
  printf("\n");
#endif
  
  return argc;
}

/*
  Runs simple shell.
*/
int main(int argc, char *argv[]) {

  char *dirs[MAX_PATHS]; // list of dirs in environment
  int numPaths;
  char cmdline[LINE_LEN];
  
  numPaths = parsePath(dirs);
  // TODO
  int background = 0; 
  int status;
  int child;
  int get_cmd;
  char last_arg;

  Command *cmd = (Command*)malloc(sizeof(Command));
  char *cmdLine = (char*)malloc(sizeof(char));
  char* cwd = (char*)malloc(100*sizeof(char));
  Jobs *jb = (Jobs*)malloc(10*sizeof(Jobs)); //malloc the job struct
  (*jb).joblist = (Job*)malloc(10*sizeof(Job));
  (*jb).num_jobs = 0;
  (*jb).num_jb_id = 0;
  signal(SIGINT, SIG_IGN); //using signal to disable Ctrl+C -> send sig

  while(1){
    getwd(cwd); //get current directory
    printf("%s %s",cwd, PROMPT); //print the current dir and the prompt sign
    fgets(cmdline, LINE_LEN, stdin);
    char* command_path = malloc(sizeof(char)*500); //malloc path from the lookupPath
    if(cmdline != NULL){
      get_cmd = parseCmd(cmdline, cmd);
      //parseCmd(cmdline, cmd);
        //exit the shell
        if(strcmp(cmd->argv[0],"exit") == 0){
          exit(0); //exit the program
        }
        else if(strcmp(cmd->argv[0], "cd") == 0){
          char s[100];
          printf("%s\n", getcwd(s, 100));
          if (cmd->argv[1] != NULL){ //if the directiry doesn't exist, create it
            if(mkdir(cmd->argv[1], S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1){//check if directory exist, -1; not exist, 0 -> create it
              //printf("existed");
              chdir(cmd->argv[1]);
              //printf("%s\n", getcwd(s, 100));
            }
            else{
              mkdir(cmd->argv[1], S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
            }
            //printf("%s\n", getcwd(s, 100)); //get current directory to see if it changed
          }
          else{
            chdir(".."); //go back to the original one
          }

        }
        else if(strcmp(cmd->argv[0], "jobs") == 0){ //use sleep 10 & as background process
          for(int i = 0; i < (*jb).num_jobs; i++){
            printf("[%d] Running  %s &\n", i, ((*jb).joblist[i]).p_name);
          }
        }

        else if(strcmp(cmd->argv[0], "kill") == 0){ //sleep 10 & to test it
          if (cmd-> argv[1] != NULL){ //if specify the job_id
            for(int i = 0; i < (*jb).num_jb_id; i++){
              if(atoi(cmd->argv[1]) == ((*jb).joblist[i]).job_id){ //compare!
                kill(((*jb).joblist[i]).job_pid, SIGTERM);
                (*jb).num_jobs = (*jb).num_jobs - 1; //add one job to the list
                (*jb).num_jb_id = (*jb).num_jb_id - 1; // add one in the id list
                //((*jb).joblist[i]).job_pid = 0;
            }
          }
        }
        else{
          printf("Please specify the job id");
        }
      }

        else{
          
          command_path = lookupPath(cmd->argv[0], dirs, numPaths); //get the full command entered
          printf("%s", command_path);
          background = 0;
          if(strcmp(cmd->argv[get_cmd-1], "&") == 0){ //to see if last argv is &
            background = 1; //set & true
            cmd->argv[get_cmd-1] = NULL; //don't wait for child process
            cmd->argc--; //decrease the args

            if(command_path != NULL && (*jb).num_jobs < 10){
              Job new_job;
              new_job.p_name = cmd -> argv[0];//get the name for job from the command line
              new_job.job_id = (*jb).num_jb_id; //get the job id for new job
              (*jb).joblist[(*jb).num_jobs] = new_job; // add new job to my job list
              (*jb).num_jobs = (*jb).num_jobs + 1; //add one job to the list
              (*jb).num_jb_id = (*jb).num_jb_id + 1; // add one in the id list
              printf("[%d] %d\n", (*jb).num_jobs, new_job.job_id);
            }
            else{
              printf("You have too many background process running! \n");
              background = 0;
            }
          }
        pid_t rc = fork();
        //int status;
        //int child;
        if(rc < 0){
          //fork failed
          fprintf(stderr,"fork failed \n");
          exit(1);
        }else if (rc == 0){ //child (new process)
          child  = (int)getpid();
          if(command_path != NULL){
            execv(command_path, cmd->argv);
          }
          if(background == 1){ //add jobs pid
            (*jb).joblist[(*jb).num_jobs - 1].job_pid = child;
          }
        }
        else{ //parent
          //int rc_wait = wait(NULL);
          if(background == 0){
            //pid_t rc_wait = waitpid(rc, &status, 0);
            pid_t rc_wait = waitpid(rc, &status, WNOHANG);
          }
          else{
            (*jb).joblist[(*jb).num_jobs -1].job_pid = rc;
          }
        }
      }
      /*
      if(command_path == NULL){
        printf("Your command input is NULL");
      }
      */
      
    for(int i = 0; i < get_cmd; i++){
      free(cmd->argv[i]);
    }

    }
  free(command_path);
  }
free(cmd);
free((*jb).joblist);
}

