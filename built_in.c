#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include<sys/wait.h>


#include "commands.h"

extern char pathlist[32][32];
extern int path_arg_count;


int built_in(char command[])
{	
	char savecommand[32];
	//trimming leading whitespace
	int commandcountwhitespace = 0;
	int allwhitespace = 0;
	while(command[commandcountwhitespace] == '\n' || command[commandcountwhitespace] == ' ' || command[commandcountwhitespace] == '\t')
	{
		commandcountwhitespace++;
		if(commandcountwhitespace == strlen(command))
		{
			allwhitespace = 1;
			break;
		}
	}

	if(commandcountwhitespace != 0)
	{

		int f = 0;	
		if(allwhitespace == 1)
		{
			//command[f] = '\0';
			return 2;
			
			
		}


		while(command[f + commandcountwhitespace] != '\0')
		{
			command[f] = command[f + commandcountwhitespace];
			f++;
		}
		command[f] = '\0';

	}
	//trim trailing whitespace
	int trailindex=0;
	int k=0;

	while(command[k] != '\0')
	{
		if(command[k] != ' ' && command[k] != '\t' && command[k] != '\n')
		{
			trailindex = k;
		}	
		k++;
	
	}
	command[trailindex + 1] = '\0';


			

	command[strcspn(command, "\r\n")] = 0;

	strcpy(savecommand, command);
	//printf("%s", command);
//exit cmd
	char exitcommand[] = "exit\n";
	int exitcheck;
	exitcheck = strcmp(exitcommand, command);
	//printf("%d",exitcheck);
	if(exitcheck == 0)
	{
		//exit(0);
		return 0;
	}
	if(command[0] == 'e')
	{	
		if(command[1] == 'x')
		{	if(command[2] == 'i')
			{	if(command[3] == 't')
				{	if(strlen(command) == 4)
					{	//printf("%ld", strlen(command));
						return 0;
					}
					if(strlen(command) > 4)
                                        {       //printf("%ld", strlen(command));
                                                return 1;
                                        }


				}
			}
		}
	}



//cd cmd

	if(command[0] == 'c')
	{
                if(command[1] == 'd')
		{
			//printf("%ld", strlen(command));
			
			if(strlen(command) == 3)
			{
				// no args
				//printf("An error has occurred\n");
				return 1;
			}
			if(strlen(command) > 3)
			{
			
				char *cdsep = " ";
				char *cdpathpre = strtok(command, cdsep);
				//printf("%s",cdpathpre);
				char *cdpath = strtok(NULL, "");
				//printf("%s",cdpath);
				
		
				cdpath[strcspn(cdpath, "\r\n")] = 0;
				
				int argnumcheck = 0;
				for(int i =0; i < strlen(cdpath); i++)
				{
					if(cdpath[i] == ' ')
					{
						return 1;
					}				
				}
	
				
				


				chdir(cdpath);
			
			
			
			
			
				return 10;
			}	
		}
	}


//path command
//
	//char path[32][32] = {{"/bin"}};
	int hasapath = 1;
	command[strcspn(command, "\r\n")] = 0;

	if(command[0] == 'p')
	{	if(command[1] == 'a')
		{	if(command[2] =='t')
			{	if(command[3] == 'h')
				{	
				//printf("%ld",strlen(command));
					if(strlen(command) == 4)	
					{
						//path set to nothing

						for(int j = 0; j < 32; j++)
						{
							for(int v = 0; v < 32; v++)
							{
								pathlist[j][v] = '\0';
								

							}


						}	
						path_arg_count = 0;
						//printf("%d", path_arg_count);

						hasapath = 0;
						return 8;
					}
					if(strlen(command) > 4)
					{
						// need to add more than one path arg function

						char *pathsep = " ";
						char *pathpre = strtok(command, pathsep);
						char *pathafterspace = strtok(NULL, "");

						pathafterspace[strcspn(pathafterspace, "\r\n")] = 0;
						
						//printf("%s",pathafterspace);

						int argcountpath = 0;
						for(int o = 0; o < strlen(pathafterspace); o++)
						{
							if(pathafterspace[o] == ' ')
							{
								argcountpath = argcountpath + 1;
								//printf("%d",argcountpath);
								//printf("%c",pathafterspace[o]);
								

							}
							
							//printf("%d",o);

						}

						//printf("%d",argcountpath);	
						if(argcountpath ==  0)
						{
							

							for(int j = 0; j < 32; j++)
                                                	{
                                                        	for(int v = 0; v < 32; v++)
                                                        	{	
                                                                	pathlist[j][v] = '\0';

                                                        	}
                                                	}	


							path_arg_count = 1;
							//printf("%d", path_arg_count);

							strncpy(pathlist[0],pathafterspace,32);
	
						}
						
						if(argcountpath > 0)
						{	
							for(int j = 0; j < 32; j++)
                                                        {
                                                                for(int v = 0; v < 32; v++)
                                                                {
                                                                        pathlist[j][v] = '\0';

                                                                }
                                                        }
							

							
							
							
							path_arg_count = argcountpath+1;
							

							char * token = strtok(pathafterspace, " ");
							strncpy(pathlist[0],token,32);
							//printf( "%s", token);
							for(int p = 1; p < argcountpath+1; p++)
							{
								token = strtok(NULL, " ");
								
								strncpy(pathlist[p],token,32);

                                                        	
							}
						}
					
						

						hasapath = 1;
						return 9;
					
					}
				}

			}
	
		}


	}
	int parallel_count = 0;

	
	if(strlen(command) == 1)
	{
		if(command[0] == '&')
		{
			return 2;
		}
	}
	for(int z = 0; z < strlen(command); z++)
	{
		
		if(command[z] == '&')
		{
			parallel_count++;

		}
	}
	int notbuilt;
	const char ps[2]= "&";
	char *token;
	char token1[32];
	char token2[32];
	char token3[32];
	int v = 0;
//not a built in command
	if(parallel_count == 0)
	{
		notbuilt = commands(command);
		
	
		if(notbuilt == 1)
		{
			return 1;

		}
		if(notbuilt == 2)
        	{
                	return 2;
        	}
		if(notbuilt == 0);		
		{
			return 10;
		}
	}
	else
	{
		


		token = strtok(command, ps);
		strcpy(token1, token);
		

		
		while(token != NULL)
		{
										
			
			if(v == 1)
			{
				strcpy(token2, token);
				//printf("%s\n",token2);

			}
			if(v == 2 && parallel_count > 1)
                        {
                                strcpy(token3, token);
				

                        }
			token = strtok(NULL, ps);
			v++;
		}
		int doallpara = 0;
		int oi = 0;
		while(doallpara == 0)
		{
			if(oi == 0)
			{
				notbuilt = commands(token1);

			}
			if(oi == 1)
                        {
                                notbuilt = commands(token2);

			}
			if(oi == 2 && parallel_count > 1)
			{
				//checks for endline &
				if(savecommand[strlen(savecommand)-1] == '&')			
				{	
					break;
				}
				notbuilt = commands(token3);
				break;
			}
			if(oi == 2 && parallel_count == 1)
                        {
                                break;
                        }
			
			oi++;
		}
						
		if(notbuilt == 1)
		{
			return 1;
		}
		return 2;
		
	}
}
