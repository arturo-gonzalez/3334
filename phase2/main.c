//Arturo Gonzalez
//CSCI 3334
//Phase2
//3/30/2016

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "functions2.h"

void load(void);
void execute(void);
void debug(void);
void dump(void);
void help(void);
void assemble(char*);
void directory(void);
void splitLine(char*, char*, char*, char*);


main()
{



    char str[80];
    int lenght;
    str[0] = '\0';
    printf("Hello, welcome to the interpreter, enter your commmand\n");
    while(str != "exit")
    {
      printf("command> ");
      fgets(str, 80, stdin);
      lenght = strlen(str)-1;
      //remove last character
      if(str[lenght]=='\n')
        {
            str[lenght]='\0';
        }
      //printf("%s\n",str);
      //printf("%d\n",lenght);

      //convert to lowercase
      int i;
      for(i = 0; str[i]; i++)
        {
            str[i] = tolower(str[i]);
        }
      char command[50];
      char p1[50];
      char p2[50];

        //split the string
        splitLine(str, command,p1,p2);
        //testing
        //printf("in split: command = %s\n", command);
        //printf("in split: p1 = %s\n", p1);
        //printf("in split: p2 = %s\n", p2);
	int numparam = 0;
	if (p1[0] != '\0')numparam++;
	if(p2[0] != '\0')numparam++;
	  if(!strcmp(command,"load"))
	    {
		if(numparam != 1)
		{
			printf("load takes exaclty one operand\n");
		}
	      	else
			load();
	    }
	  else if(!strcmp(command,"execute"))
	    {
	        if(numparam != 0)
            {
                printf("execute takes no operands\n");
            }
            else
	 		execute();
	    }
	  else if(!strcmp(command,"debug"))
	    {
	        if(numparam != 0)
            {
                printf("debug takes no operands\n");
            }
            else
            debug();
	    }
	  else if(!strcmp(command,"dump"))
	    {
	        if(numparam !=2)
            {
                printf("dump takes exaclty two operands\n");
            }
            else
                dump();
	    }
	  else if(!strcmp(command,"help"))
	    {
	        if(numparam != 0)
            {
                printf("help takes no operands\n");
            }
            else
            help();
	    }
	  else if(!strcmp(command,"assemble"))
	    {
	        if(numparam !=1)
            {
                printf("assemble takes exaclty one operand\n");
            }
            else
                assemble(p1);
	    }
	  else if(!strcmp(command,"directory"))
	    {
	        if(numparam != 0)
            {
                printf("directory takes no operands\n");
            }
            else
	        directory();
	    }

	  else if(!strcmp(command,"exit"))
	    {
	        if(numparam != 0)
            {
                printf("exit takes no operands\n");
            }
            else
	        exit(0);
	    }
      else
	{
	  printf("%s is not a valid command. Type help for a list of commands\n", command);
	}

    }


  return 0;

}

//functions
void load(void)
{
  printf("load function was reached\n");
}
void execute(void)
{
  printf("execute function was reached\n");
}
void debug(void)
{
  printf("debug function was reached\n");
}
void dump(void)
{
  printf("dump function was reached\n");
}
void help(void)
{
  printf("****************************************\n");
  printf("load:     will call the load function to load the specified file\n");
  printf("execute:  will call the computer simulation program to execute the program that was previosly loaded in memory \n");
  printf("debug:    will allow you to execute in debug mode\n");
  printf("dump      will call the dump function, passing the values of start and end. Start and end will be hexadecimal values\n");
  printf("help:     will print out a list of available commands\n");
  printf("assemble: will assemble a SIC assembly language program into a load module and store it in a file\n");
  printf("directory:will list the files stored in the current directory\n");
  printf("exit:     will exit from the simulator\n");
}
void assemble(char *p1)
{
  pass1(p1);
}
void directory(void)
{
  system("ls");
}

//function to split line
void splitLine(char* line, char *command, char*p1, char *p2)
{

	command[0] = p1[0] = p2[0] = '\0';
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;
	int length = strlen(line)-1;

	while(line[i] == ' '|| line[i]=='\n' || line[i] =='\t')i++;
	for(; i<=length;i++,l++)
	{
		if(line[i] != ' '&& line[i] !='\t')
		{
			command[l] = line[i];
		}
		else
		{

		 	break;
		}

	}
	command[l] = '\0';
	while(line[i] == ' '|| line[i]=='\n' || line[i] =='\t')i++;
	for(; i<=length;i++,j++)
	{
		if(line[i] != ' '&& line[i] !='\t')
		{
			p1[j] = line[i];
		}
		else
		{
		 	break;
		}

	}
	p1[j] = '\0';
	while(line[i] == ' '|| line[i]=='\n' || line[i] =='\t')i++;

	for(; i<=length;i++,k++)
	{
		if(line[i] != ' '&& line[i] !='\t')
		{
			p2[k] = line[i];
		}
		else
		{
		 	break;
		}

	}
	p2[k] = '\0';
}
