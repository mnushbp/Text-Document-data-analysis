/*************************

# Family Name: Patabendi
# Given Name: Manusha
# Section: z
# Student Number:
# CSE Login: 

***************************/

#include <stdio.h>
#include <string.h>

typedef  struct {

     char  word[101] ;
     int   freq ;

} WordArray ;

//compare string freequancies in qSort()----------------------------------- 
int cmpwords (const void * a, const void * b){
  return (((int)(((WordArray*)b)->freq)) - (int)(((WordArray*)a)->freq));
}

int main(int argc, char** argv)
{
	int index ;  // current number of elements in the array 
	int i,j,x; 

	if (argc <=1){
		printf("Error. Please specify file names. \n");
		return -1;
	}
	else {

		for(x=1 ; x <argc ; x++){

			index = 0;  
			WordArray warray[10000] ; // assume max number of different words are 10000
			char temp[101];
   			
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


			// Printing results---------------------- 
			printf("%s \t %d \t",argv[x],index) ;			
			for (i=0 ; i <3 ; i++)
			{
				printf("%s \t", warray[i].word);
			}
			printf("\n") ;

			//close file connection-----------------
    			fclose(fp);
		}
	}
}
