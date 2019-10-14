#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include <error.h>
// #include <libexplain/execvp.h>
#include "head.h"
pid_t p_id;
int k2;
char s_back2[100][100];

//p_id
void handl(int sig){
	
	int i;
	int booleanvar = 0;
	int status;
	int rec_pid = waitpid(-1,&status,WNOHANG);
     for ( i = 0; i < jobno; ++i)
     {
     	if (rec_pid==p_arr[i].pid)
     	{       
     		booleanvar = 1;
     		if(WIFEXITED(status))
			fprintf(stderr,"%s with pid %d exited normally \n",p_arr[i].name,p_arr[i].pid);
			else if(WIFSIGNALED(status))
			fprintf(stderr,"%s with pid %d exited abnormally \n",p_arr[i].name,p_arr[i].pid);	
        	break;	
		}
     }
     for (int j = i; booleanvar &&  j < jobno-1; ++j)
     {
     	p_arr[j].pid=p_arr[j+1].pid;
     	strcpy(p_arr[j].name,p_arr[j+1].name);
     }
     if(booleanvar)
     	jobno--;
	return;
	
}
void back(char s_back[100][100],int k)
{
	k2=k;
	char ** arr2=(char**)malloc(sizeof(char*)*100);
	for (int n = 0; n < 100; ++n)
	{
		arr2[n]=(char*)malloc(sizeof(char)*100);        
	}
	for (int n = 0; n < k; ++n)
	{
		strcpy(arr2[n],s_back[n]);
		strcpy(s_back2[n],s_back[n]);
	}   

	arr2[k-1]=NULL;
	strcpy(s_back2[k],"/0");
	signal(SIGCHLD,handl);				
	p_id=fork();
	if(p_id==0)
	{
		setpgid(0,0);
		if(execvp(arr2[0],arr2)==-1)
			perror("execvp not working2");
		
		exit(0);
	}
	else if(p_id<0){
		perror("not forked");
	}
	else{
			// printf("%ld\n", p_id);
		   p_arr[jobno].pid=p_id;
           strcpy(p_arr[jobno].name,arr2[0]);
			jobno++;
	}

}
