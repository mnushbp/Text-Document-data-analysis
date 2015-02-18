/*************************

# Family Name: Patabendi
# Given Name: Manusha
# Section: z
# Student Number:
# CSE Login: 

***************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

#define ONE 1
#define ZERO 0


typedef  struct {

     char  word[101] ;
     int   freq ;

} WordArray ;

// store names of files 
typedef struct 
{
        WordArray words[3] ; 
        char  fName[101];
        int  frank; 
        
} fileArray; 

//compare string freequancies in qSort()----------------------------------- 
int cmpwords (const void * a, const void * b)
{
	return (((int)(((WordArray*)b)->freq)) - (int)(((WordArray*)a)->freq));
}

//compare file freequancies in qSort()----------------------------------- 
int cmpFiles(const void * a, const void * b)
{				
	return (((int)(((fileArray*)b)->frank)) - (int)(((fileArray*)a)->frank));
}


int main(int argc, char** argv)
{

	int index ;  // current number of elements in the array 
	int i,j,x; 

	fileArray farray[101];	

	pid_t *idist = (pid_t*) malloc(sizeof(pid_t));
   	int fd[2];
   	
   	int status,id; //used for fork
	
   	if(pipe(fd) < ZERO)
    	{
       		printf("Error. Pipe failed. \n");
        	exit(ONE);
		}
    	else
		{

		for(x=1 ; x <argc ; x++)
		{
	
			 int pid;
           		 pid = fork();
           		  
           		 if(pid >= 0)
            		 {
            		 
                		if(pid == 0)//---- child process 
                		{	
					index = 0;  
					WordArray warray[10000] ; // assume max number of different words are 10000
					char temp[101];

					strcpy(farray[x].fName,argv[x]); 
   			
					FILE *fp;								
   					fp = fopen(argv[x], "r");

					int new_word;
					
					while (EOF != fscanf(fp, "%s", &temp))	
					{
						new_word = 1 ;

						for(j=0; j<=index ;j++)
						{
							if(strcmp(temp,warray[j].word)==0)
							{
								new_word = 0;
								warray[j].freq++ ;
								break; 
							}
						}
						if(new_word == 1){
					
							strcpy(warray[index].word,temp); 
							warray[index].freq=1 ;
							index++; 
						}	
    					}

					//Sorting the array----------------------------------------
					qsort(warray, index, sizeof(WordArray),cmpwords);

					//copy sorted array-----------------------
					for(i=0; i<3; i++)
					{
						strcpy(farray[x].words[i].word,warray[i].word);

					}
					farray[x].frank= index; 

					//close file connection-----------------
    					fclose(fp);
    
    					// close and write to the pipe--------------
    					close(fd[0]);
                                        write(fd[1], &farray[x], sizeof(fileArray));
                                   
                                        exit(ONE);
				}
				else 
                		{
                    			idist[x] = pid; 
                		}
			}
			else {
				printf("Fork initialization failed!\n");
                    		exit(ZERO);
			}
		}
		
		// wait until parent process is complete 	
		for(i = 0; i < argc; i++)
		{
	        	id = wait(&status);
	        	close(fd[1]);
	        	read(fd[0], &farray[i], sizeof(farray));
		}

		//Sorting files------------ 
		qsort(farray, argc, sizeof(farray[0]), cmpFiles);


		// Printing results---------------------- 		
		for (i=0 ; i <argc-1 ; i++)
		{
			printf("%s \t %d \t",farray[i].fName,farray[i].frank) ;	
			for (j=0 ; j <3 ; j++)
			{
				printf("%s \t", farray[i].words[j].word);
			}
			printf("\n") ;
		}	
	}
	return 0;
}