#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#define MAX_STRING_LENGTH 255
#define MAX_TOKS 100
#define DELIMITERS " \t"
#define MAXCOM 1000  
#define MAXLIST 1000 
void parseSpace(char* str, char** parsed) 
{ 
    int i; 
  
    for (i = 0; i < MAXLIST; i++) { 
        parsed[i] = strsep(&str, " "); 
  
        if (parsed[i] == NULL) 
            break; 
        if (strlen(parsed[i]) == 0) 
            i--; 
    } 
} 
int check(char* str, char** strpiped) 
{ 
    int i; 
    for (i = 0; i < 2; i++) { 
        strpiped[i] = strsep(&str, "|"); 
        if (strpiped[i] == NULL) 
            break; 
    } 
  
    if (strpiped[1] == NULL) 
        return 0; // returns zero if no pipe is found. 
    else { 
        return 1; 
    } 
} 
int processString(char* str, char** parsed, char** parsedpipe) 
{ 
  
    char* strpiped[2]; 
    int piped = 0; 
  
    piped = parsePipe(str, strpiped); 
  
    if (piped) { 
        parseSpace(strpiped[0], parsed); 
        parseSpace(strpiped[1], parsedpipe); 
  
    } else { 
  
        parseSpace(str, parsed); 
    } 
  

} int parsePipe(char* str, char** strpiped) 
{ 
    int i; 
    for (i = 0; i < 2; i++) { 
        strpiped[i] = strsep(&str, "|"); 
        if (strpiped[i] == NULL) 
            break; 
    } 
  
    if (strpiped[1] == NULL) 
        return 0; // returns zero if no pipe is found. 
    else { 
        return 1; 
    } 
} 
void  parse(char *line, char **argv)
{
     while (*line != '\0') {       
          while (*line == ' ' || *line == '\t' || *line == '\n')
               *line++ = '\0';     
          *argv++ = line;         
          while (*line != '\0' && *line != ' ' && 
                 *line != '\t' && *line != '\n') 
               line++;            
     }
     *argv = '\0'; 
            
}

void  execute(char **argv)
{
     pid_t  pid;
     int    status;

     if ((pid = fork()) < 0) {               
          printf("* ERROR: forking child process failed\n");
          exit(1);
     }
     else if (pid == 0) {                
          if (execvp(*argv, argv) < 0) {     
               exit(1);
          }
     }
     else {                                 
          while (wait(&status) != pid);
     }
}
int interactive(){
	char  line[1024];            
        char  *argv[64]; 
char in[200]; 
	pid_t pid1;
        pid_t  pid2;
        char inputString[MAXCOM], *parsedArgs[MAXLIST]; 
        char* parsedArgsPiped[MAXLIST]; 
        int execFlag = 0; 
int status;

	printf("    ***BilShell created by Ms Efronova***\n");
	printf("    ***Welcome to interactive mode of BilShell***\n");
	
   	while (1) {                
       printf("    ***Please enter a command***\n");
        printf("    ***Enter exit if you are done (with life)***\n");
          fgets(line, 1024, stdin); 
	  line[strcspn(line, "\n")] = 0;
          printf("\n");
	execFlag = processString(line, parsedArgs, parsedArgsPiped); 
	if (!parsedArgs[0]) {  continue;}
        if (strcmp(parsedArgs[0], "exit") == 0)  
            	         exit(0);
        if (execFlag == 1) 
 printf("    111\n");
            execute(parsedArgs); 
  
        if (execFlag == 2)  {  
                    int pipe1[2];
	            int pipe2[2];
	            int status1 , status2;
                     status2 = pipe(pipe2);
		    status1 = pipe(pipe1);
		    
		   if(status1 == -1){
			printf("Piping failed");
                  	 return 1;}
		   if(status2 == -1){
			printf("Piping failed");
                   	return 1;}
 			pid1 = fork();

                  if (pid1 < 0) {               
                     printf("* ERROR: forking child process failed\n");
                     exit(1);
                  }
                 else if (pid1 == 0) {   
                      
	        close(pipe1[0]);   
		close(pipe2[0]);
		close(pipe2[1]);
		dup2(pipe1[1],1);
                close(pipe1[1]);
         
                      if (execvp(*argv, argv) < 0) {     
                          exit(1);
                      }
                  }
               pid2 = fork();
                if (pid2 < 0) {               
                     printf("* ERROR: forking child process failed\n");
                     exit(1);
                  }
                 else if (pid2 == 0) {   
                close(pipe1[0]);   
		close(pipe1[0]);
		close(pipe1[1]);
		dup2(pipe2[0],0) ;  
                close(pipe2[1]);          
                      if (execvp(*argv, argv) < 0) {     
                          exit(1);
                      }
                  }
                 close (pipe1[1]);
		close(pipe2[0]);
int n = atoi(argv[1]);
	int countChars = 0;
	int readCount = 0;
        int writeCount = 0;
int readS, write1;
 while(1){
readS = read(pipe1[0], in, n );
write(pipe2[1], in, n);
if(readS>0){
	countChars = countChars + readS;
	readCount++;
	writeCount++;}
else{
break;}
}
close(pipe1[0]);
close(pipe2[1]);
wait(NULL);
wait(NULL);
printf("\n");
printf("character count is %d\n", countChars);
printf("read call count is %d\n", readCount);
printf("write call count is %d\n", writeCount);
}
                  }
     	}		


int main(int argc, char *argv[]){
	// call interactive mode
	if(argc == 1){printf("Shell terminated due to incorrect invocation"); return 0;}
        else if ( argc == 2) {
		interactive();
	}
	//else batch mode
	else if (argc == 3){
          
        char  *argv[64]; 
char in[200]; 
	pid_t pid1;
        pid_t  pid2;
        char inputString[MAXCOM], *parsedArgs[MAXLIST]; 
        char* parsedArgsPiped[MAXLIST]; 
        int execFlag = 0; 
int status;
  	char  line[1024];   
  	FILE *file;
 	 file = fopen (argv[2], "r"); 
  	if(file != NULL){
 	printf("Ms Efronova's BilShell is  entered  \n ");  
		while(fgets (line, 1024, file) != NULL){
		line[strcspn(line, "\n")] = 0;
	  	execFlag = processString(line, parsedArgs, parsedArgsPiped); 
	if (!parsedArgs[0]) {  continue;}
        if (strcmp(parsedArgs[0], "exit") == 0)  
            	         exit(0);
        if (execFlag == 1) 
 printf("    111\n");
            execute(parsedArgs); 
  
        if (execFlag == 2)  {  
                    int pipe1[2];
	            int pipe2[2];
	            int status1 , status2;
                     status2 = pipe(pipe2);
		    status1 = pipe(pipe1);
		    
		   if(status1 == -1){
			printf("Piping failed");
                  	 return 1;}
		   if(status2 == -1){
			printf("Piping failed");
                   	return 1;}
 			pid1 = fork();

                  if (pid1 < 0) {               
                     printf("* ERROR: forking child process failed\n");
                     exit(1);
                  }
                 else if (pid1 == 0) {   
                      
	        close(pipe1[0]);   
		close(pipe2[0]);
		close(pipe2[1]);
		dup2(pipe1[1],1);
                close(pipe1[1]);
         
                      if (execvp(*argv, argv) < 0) {     
                          exit(1);
                      }
                  }
               pid2 = fork();
                if (pid2 < 0) {               
                     printf("* ERROR: forking child process failed\n");
                     exit(1);
                  }
                 else if (pid2 == 0) {   
                close(pipe1[0]);   
		close(pipe1[0]);
		close(pipe1[1]);
		dup2(pipe2[0],0) ;  
                close(pipe2[1]);          
                      if (execvp(*argv, argv) < 0) {     
                          exit(1);
                      }
                  }
                 close (pipe1[1]);
		close(pipe2[0]);
int n = atoi(argv[1]);
	int countChars = 0;
	int readCount = 0;
        int writeCount = 0;
int readS, write1;
 while(1){
readS = read(pipe1[0], in, n );
write(pipe2[1], in, n);
if(readS>0){
	countChars = countChars + readS;
	readCount++;
	writeCount++;}
else{
break;}
}
close(pipe1[0]);
close(pipe2[1]);
wait(NULL);
wait(NULL);
printf("\n");
printf("character count is %d\n", countChars);
printf("read call count is %d\n", readCount);
printf("write call count is %d\n", writeCount);
}
                  }
     	}
	else {
		printf("Could not locate file"); 
 	}
}
printf("Ms Efronova's BilShell is done \n");
return 1;
}
