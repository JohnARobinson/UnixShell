#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "built_in.h"
#include "commands.h"

/*John Robinson shell project
 *
 *I ran out of time on the last test getting the parallel commands to acually run in parallel.
 *
 *
 */


int input(char *s, int length);

char pathlist[32][32] = {{"/bin"}};
int path_arg_count = 1;

char redirectfilename[32];
int isredirect;

int main(int argc, char *argv[])
{
	// mode 0 is nothing, mode 1 is batchfile, mode 2 is interactive
	
	int mode = 0;
	int strcheck;
	int strcheckexit;
	char strcopy[32];
	char filename[32];
	if(argv[1] != NULL)
	{
		mode = 1;
	}
	else
	{
		mode = 2;
	}

			
	FILE *fptr;
	int linenumber = 1;
	char filereader[32];
	char *line = NULL;
	size_t length = 0;
	ssize_t read;
	int resultfile = 10;	
	char *p = NULL;	
	char error_message[30] = "An error has occurred\n";


	int filestatus = 0;
	if(access(argv[1], F_OK) != -1)
	{	
		filestatus = 1;
	}
	else
	{
		filestatus = 0;
	}
	

	if(mode == 1)
	{	
		//printf("%d", filestatus);
		if(argc > 2)
		{
			write(STDERR_FILENO, error_message, strlen(error_message));
			exit(1);
		}
		if(filestatus == 0)
		{
			write(STDERR_FILENO, error_message, strlen(error_message));
			exit(1);

		}

		fptr = fopen(argv[1],"r");
		int blank = 0;
		while((read = getline(&line,&length, fptr)) != -1)
		{
			blank = 0;
			if(strlen(line) == 1) 
			{
				blank = 1;
				continue;
			}


			resultfile = built_in(line);
			
			if(resultfile == 0)
			{
				fclose(fptr);
				exit(0);
			}
			if(resultfile == 1)
			{

				//char error_message[30] = "An error has occurred\n";
    				write(STDERR_FILENO, error_message, strlen(error_message)); 
			}
			if(resultfile >= 2)
                        {
				// this is was printing the line number and echo but was failing tests due to conflicting output
			


                        }


					
		}
		fclose(fptr);
		exit(0);
	}


	char *buffer;
        size_t bufsize = 64;
        size_t characters;
        int running = 1;
        buffer = (char *)malloc(bufsize * sizeof(char));


	if(mode == 2)
	{	
		do
		{	
			if(buffer == NULL)
			{
				perror("unable to allocate buffer");
				exit(1);
			}
		

			printf("wish> ");
			characters = getline(&buffer,&bufsize,stdin);
			
			strcpy(strcopy,buffer);
			int result = 10;
			result = built_in(strcopy);
			

			if(result == 0)
			{	
				exit(0);
			}
			if(result == 1)
			{
				char error_message[30] = "An error has occurred\n";
                                write(STDERR_FILENO, error_message, strlen(error_message));

			}
			else
			{
				
				printf("line%d",linenumber);
				printf(": ");
				printf("%s",buffer);
				linenumber = linenumber + 1;

			}

		}while(running == 1);

	}
	return 0;

}
