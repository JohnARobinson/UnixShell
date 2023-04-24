#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

extern char pathlist[32][32];
extern int path_arg_count;


int commands(char command[])
{

int execreturn = 0;

if(command[0] == '&' || command[0] == '\0')
        {
                //printf("d");
                return 2;
        }


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



	if(command[0] == '&' || command[0] == '\0')
        {
                //printf("d");
                return 2;
        }









//commands with no args
	
	if(path_arg_count == 0)
        {
                return 1;
        }

	//check for echo
	
	
					
			

	
	
	int argcount = 0;
	int filestatus1 = 0;
	int filestatus = 0;
	command[strcspn(command, "\n")] = 0;
	int redirectyn = 0;
	int returnnofileretirect = 0;
	int redirectioninitalpos = 0;
	char redirectpath[32];

	int whitespacezero = 0;
	
	int redirectfile;
	
	for(int x = 0; x < strlen(command); x++)
	{
		if(command[x] == ' ' && redirectyn == 0 && command[x+1] != '>')
		{
			argcount = argcount + 1;

		}
		

		//checking for redirection
		if(command[x] == '>')
		{
			redirectyn = 1;
			if(redirectioninitalpos == 0)
			{
				redirectioninitalpos = x;
			}

			char *redirectsep = ">";
                	char *redirectpre = strtok(command, redirectsep);
                	char *redirectloc = strtok(NULL, "");

                	                	

                	if(redirectloc == NULL)
                	{
				
				return 1;
                	}
			else
			{
				
				for(int k = 0; k < strlen(redirectloc); k++)
        			{
                			if(redirectloc[k] == ' ')
                			{
                        			if(k != 0)
						{
							//printf("%s", redirectloc);
							return 1;
						}
						else
						{
							whitespacezero = 1;
						}
						

                			}


				}
				
				if(whitespacezero == 1)
				{
					char *initspace = " ";
		                	char *removeinitspace = strtok(redirectloc, initspace);
                			char *spaceremoved = strtok(NULL, "");
					
					
					

					int trailindex2=0;
        				int k2=0;

        				while(command[k2] != '\0')
        				{
                				if(command[k2] != ' ' && command[k2] != '\t' && command[k2] != '\n')
                				{
                        				trailindex2 = k2;
                				}
                				k2++;

        				}
        				command[trailindex2 + 1] = '\0';
        				command[strcspn(command, "\r\n")] = 0;





					//redirect with whitespace
					
					redirectfile = open(removeinitspace, O_CREAT | O_TRUNC | O_WRONLY);
                                	

				}
				else	//redirect without whitespace
				{	whitespacezero = 2;
					redirectfile = open(redirectloc, O_CREAT | O_TRUNC | O_WRONLY);
					
				}
			}
		}

	}
	//echo check
	if(command[0] == 'e')
	{    
		if(command[1] == 'c')
		{               
			if(command[2] == 'h')
			{	
				if(command[3] == 'o')
				{
					argcount = 1;
					//printf("%c", command[3]);
							
				}
			}
		}
	}


	if(command[0] == '&')
	{	
		//printf("d");
		return 2;
	}	

	// exec code with no args
			
	if(argcount == 0)
	{


		
		char *args[2];	
		char commandsearch[32];
                char slash = '/';
	
		



		for(int z = 0; z < path_arg_count; z++)
		{
		
			
			
			commandsearch[0] = '\0';

			strcpy(commandsearch, pathlist[z]);
			strncat(commandsearch, &slash, 1);
			strcat(commandsearch, command);
				
			//check if file exits
			if(access(commandsearch, F_OK ) != -1)
                	{
				 
                        	filestatus1 = 1;
				args[0] = commandsearch;
	                        args[1] = NULL;
				break;

			}
                	else
			{	
				if(path_arg_count == 1)
				{
					filestatus1 = 2;
					//printf("%d", filestatus1);

					return 1;
				}
				if(path_arg_count >= 1)
				{
					if(z == path_arg_count-1)
					{
						filestatus1 =2;
						return 1;
					}
					
				}
				
                	}
		
		}
	
		
		
				
			
		pid_t i = fork();
		if(i == 0)
		{	
			if(whitespacezero == 1 || whitespacezero == 2)
			{
				dup2(redirectfile, STDOUT_FILENO);
                        	close(redirectfile);
			}
			execreturn = execv(args[0],args);
		}			
		if(i != 0)
		{
			wait(NULL);
		}
		
		
		
	}
	//commands with args

	
	
	if(argcount > 0)
	{
		char commandsearch[32];
		char commandfirstarg[32];
		char commandsecondarg[32];

		char slash = '/';

		char *commandsep = " ";
                char *commandpre = strtok(command, commandsep);
                char *commandargs = strtok(NULL, "");

		
		if(argcount > 1)
		{
			char *commandargs1 = strtok(commandargs, commandsep);
			char *commandargs2 = strtok(NULL, "");
			
			strcpy(commandfirstarg, commandargs1);
			strcpy(commandsecondarg, commandargs2);
	
	
		}
		
	
		

		char *args2[4];
		

		
		for(int u = 0; u < path_arg_count; u++)
                {
			              		
			strcpy(commandsearch, pathlist[u]);
			strncat(commandsearch, &slash, 1);
			strcat(commandsearch, commandpre);
					
			


			if(access(commandsearch, F_OK ) != -1)
			{
				filestatus = 1;
				if(argcount == 1)
				{	commandargs[strcspn(commandargs, "\r\n")] = 0;

					args2[0] = commandpre;
					args2[1] = commandargs;
					args2[2] = NULL;
                                	args2[3] = NULL;
					break;
				}
				if(argcount == 2)
				{

					args2[0] = commandpre;
                                        args2[1] = commandfirstarg;
                                        args2[2] = commandsecondarg;
                                        args2[3] = NULL;
                                        break;
	
				}
	

			}
			else
			{
				
	       		        if(path_arg_count == 1)
                               	{	
                               	        filestatus = 2;
                               	        return 1;
                               	}
                                
				if(path_arg_count >= 1)
                                {
                                        if(u == path_arg_count-1)
                                        {
                                                filestatus1 =2;
                                                
                                                return 1;
                                        }
                                        
                                }

	                
			}
		}		
		

			pid_t i = fork();
		    	if(i == 0)
               		{

				if(whitespacezero == 1 || whitespacezero == 2)
                        	{
                                	dup2(redirectfile, STDOUT_FILENO);
                                	close(redirectfile);
                        	}

	
				execreturn = execv(commandsearch,args2);
				//exit(1);
				
				
			}
				
		
         		if(i != 0)
			{
                		wait(NULL);		
	        	}
		
			
		
					
			
	}




	

	if(errno == 2 && filestatus1 == 1)
        {
		return 2;        }

	if(errno == 2 && filestatus == 1)
        {

                return 2;
		
        }


	if(filestatus == 2 || filestatus1 == 2)
	{
		return 1;
		
	
	}
	if(returnnofileretirect == 1)
	{
		return 1;
	}


	else
	{
		return 0;
	}

		
	
	//printf("%d",errno);
	return 20;

}	
