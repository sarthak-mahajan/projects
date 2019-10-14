#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include <error.h>
#include "head.h"
void fore(char s_fore[100][100],int k){

	char ** arr1=(char**)malloc(sizeof(char*)*100);
	for (int n = 0; n < 100; ++n){
		arr1[n]=(char*)malloc(sizeof(char)*100);        
	}
	for (int n = 0; n < k; ++n){
		strcpy(arr1[n],s_fore[n]);
	}     
	arr1[k]=NULL;
	pid_t p_id,w_id;
	int status;
	strcpy(last_com,arr1[0]);
	p_id=fork();
	fore_pid=p_id;
	if(p_id==0){
				// printf("fore=%d\n",getpid() );

		if(execvp(arr1[0],arr1)==-1){
			perror("execvp not working1");
			exit(0);
		}
		exit(0);
	}
	else if(p_id<0){
		perror("not forked");
	}
	else{
					// printf("hahah%ld\n",p_id);
		do{

						// w_id=waitpid(p_id,&status,WUNTRACED);tcsetpgrp(0, getpgid(p_arr[r1-49].pid));
			tcsetpgrp(0, getpgid(p_id));
			signal(SIGTTIN, SIG_IGN);
			signal(SIGTTOU, SIG_IGN);
			kill(p_id,SIGCONT);
			w_id=waitpid(p_id, &status, WUNTRACED);
			tcsetpgrp(0, getpgid(shell_pid));
			signal(SIGTTOU, SIG_DFL);
			signal(SIGTTIN, SIG_DFL);
			
		}while(!WIFEXITED(status) && !WIFSIGNALED(status) && !WIFSTOPPED(status) );
		if(WIFSTOPPED(status)){
			// printf("fore stop\n");
			// printf("'%d'\n",fore_pid);
			// printf("'%s'\n",last_com );
			jobno++;
			p_arr[jobno-1].pid=fore_pid;
			strcpy(p_arr[jobno-1].name,last_com);
		}	
	}
	free(arr1);


}