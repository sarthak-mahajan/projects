#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>
#include <fcntl.h> 
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include <error.h>
#include "head.h"
typedef int ll;
int sig_check=0;
int indec_cnt;
int indec_pos;
int outdec_cnt;
int outdec_pos;
int q=0,k,k2;
char s2[100][100];
char s3[100][100];
char s4[100][100];
char s5[100][100];   // redirec
char *buf;
size_t bufsize=1000;
char s[100],curr_dir[100];
void all_check(char arr[100]){
	k2=0;       
	char* token3 = strtok(arr, " "); 
	while (token3 != NULL) { 
		strcpy(s5[k2],token3);
		token3 = strtok(NULL, " ");
		k2++;
	} 
	strcpy(s5[k2],"\0"); 
	if (s5[k2-1][0]!='&')
	{
		if(strcmp(s5[0],"cd")==0){
			if(k2==1)
				cd("~", home_dir);
			else
				cd(s5[1], home_dir);

		}
		else if(strcmp(s5[0],"echo")==0){
			echo(s5);
		}
		else if(strcmp(s5[0],"pwd")==0){
			pwd(home_dir);
		}
		else if(strcmp(s5[0],"pinfo")==0){
			pinfo(s5[1]);
		}
		else if(strcmp(s5[0],"ls")==0){
			ls(s5,home_dir);
		}
		else if(strcmp(s5[0],"setenv")==0){
			if(strcmp(s5[1],"\0")==0)
				printf("too few arguments\n");
			else{
				if(strcmp(s5[2],"\0")==0){
					if(setenv(s5[1],"",1)==-1)
						perror("setenv error1");
				}
				else{
					if(strcmp(s5[3],"\0")!=0)
						printf("too many arguments\n");
					else if(setenv(s5[1],s5[2],1)==-1)
						perror("setenv error2");

				}

			}

		}
		else if(strcmp(s5[0],"unsetenv")==0){
			if(strcmp(s5[1],"\0")==0)
				printf("too few arguments\n");
			else{
				if(unsetenv(s5[1])==-1)
					perror("unsetenv error");
			}
		}
		else if(strcmp(s5[0],"quit")==0){

			exit(1);

		}

		else if(strcmp(s5[0],"jobs")==0){
			int l1,l2,l3,p1;
			char info_buf[1000],temp_buf[1000],path1[1000],status1[1000];
			char stat_name[1000];

			for (int jn = 0;jn < jobno; ++jn)
			{

				strcpy(path1,"/proc/");
				p1=p_arr[jn].pid;
				l2=0;
				while(p1!=0){
					temp_buf[l2]=48+p1%10;
					p1=p1/10;
					l2++;
				}
				for ( l3 = 0; l3 < l2/2 ; ++l3)
				{
					char temp_inf;
					temp_inf=temp_buf[l3];
					temp_buf[l3]=temp_buf[l2-l3-1];
					temp_buf[l2-l3-1]=temp_inf;

				}

				strcat(path1,temp_buf);
				strcat(path1,"/stat");

				int fd4=open(path1,O_RDONLY);
				if (fd4<0)
				{
					// perror("not runningewgweg");
					continue;
				}

				read(fd4,info_buf,1000);
				char* token5 = strtok(info_buf, " "); 
				l1=0;
				while (token5 != NULL && l1<=24) { 
					l1++;
					if (l1==3)
					{
						strcpy(status1,token5);
					}

					token5 = strtok(NULL," ");
				} 
				if(strcmp(status1,"R")==0)
					strcpy(stat_name,"Running");
				else if(strcmp(status1,"T")==0)
					strcpy(stat_name,"Stopped");
				else if(strcmp(status1,"S")==0)
					strcpy(stat_name,"Sleeping");
				else if(strcmp(status1,"Z")==0)
					strcpy(stat_name,"Zombie");

							// for (int ii = jn; ii < jobno-1; ++ii)
							// {
							// 	p_arr[ii].pid=p_arr[ii+1].pid;
							// 	strcpy(p_arr[ii].name,p_arr[ii+1].name);
							// }
							// jobno--;

				printf("%d %s %s %d\n",jn+1,stat_name,p_arr[jn].name,p_arr[jn].pid);
				strcpy(info_buf,"");
				strcpy(temp_buf,"");
				strcpy(status1,"");
				strcpy(path1,"");
				strcpy(stat_name,"");

			}

		}
		else if(strcmp(s5[0],"kjob")==0){
			int r1,r2;
			char tem[100];
			char tem2[100];
			for (int ii = 0; ii < strlen(s5[1]); ++ii)
			{
				tem[ii]=s5[1][ii];
			}  
			for (int ii = 0; ii < strlen(s5[2]); ++ii)
			{
				tem2[ii]=s5[2][ii];
			}  

			for ( int ii = 0; ii < strlen(tem)/2 ; ++ii)
			{
				char temp_inf;
				temp_inf=tem[ii];
				tem[ii]=tem[strlen(tem)-ii-1];
				tem[strlen(tem)-ii-1]=temp_inf;

			}
			for ( int ii = 0; ii < strlen(tem2)/2 ; ++ii)
			{
				char temp_inf;
				temp_inf=tem2[ii];
				tem2[ii]=tem2[strlen(tem2)-ii-1];
				tem2[strlen(tem2)-ii-1]=temp_inf;

			}
			int base=1;
			for (int ii = 0; ii <strlen(tem) ; ++ii)
			{ 

				r1=tem[ii]*base;
				base*=base;

			}
			base=1;
			for (int ii = 0; ii <strlen(tem2) ; ++ii)
			{ 

				r2=tem2[ii]*base;
				base*=base;

			}

			kill(p_arr[r1-49].pid,atoi(s5[2]));                           

		}
		else if(strcmp(s5[0],"overkill")==0){
			for (int ii = 0; ii < jobno; ++ii)
			{
				kill(p_arr[ii].pid,9);                           

			}


		}
		else if(strcmp(s5[0],"bg")==0){
			char tem[100];
			int r1;
			for (int ii = 0; ii < strlen(s5[1]); ++ii)
			{
				tem[ii]=s5[1][ii];
			}  
			for ( int ii = 0; ii < strlen(tem)/2 ; ++ii)
			{
				char temp_inf;
				temp_inf=tem[ii];
				tem[ii]=tem[strlen(tem)-ii-1];
				tem[strlen(tem)-ii-1]=temp_inf;

			}
			int base=1;
			for (int ii = 0; ii <strlen(tem) ; ++ii)
			{ 

				r1=tem[ii]*base;
				base*=base;

			}
// printf("%d\n",p_arr[r1-49].pid );

// kill(p_arr[r1-49].pid,SIGSTOP);
			kill(p_arr[r1-49].pid,SIGCONT);


		}
		else if(strcmp(s5[0],"fg")==0){
			char tem[100];
			int r1,state;
			for (int ii = 0; ii < strlen(s5[1]); ++ii)
			{
				tem[ii]=s5[1][ii];
			}  
			for ( int ii = 0; ii < strlen(tem)/2 ; ++ii)
			{
				char temp_inf;
				temp_inf=tem[ii];
				tem[ii]=tem[strlen(tem)-ii-1];
				tem[strlen(tem)-ii-1]=temp_inf;

			}
			int base=1;
			for (int ii = 0; ii <strlen(tem) ; ++ii)
			{ 

				r1=tem[ii]*base;
				base*=base;

			}
			pid_t pi=p_arr[r1-49].pid;
			char l_com[100];
			strcpy(l_com,p_arr[r1-49].name);
			// for (int ii = r1-49; ii < jobno-1; ++ii)
			// {
			// 	p_arr[ii].pid=p_arr[ii+1].pid;
			// 	strcpy(p_arr[ii].name,p_arr[ii+1].name);
			// }
			// jobno--;

			tcsetpgrp(0, getpgid(pi));
			signal(SIGTTIN, SIG_IGN);
			signal(SIGTTOU, SIG_IGN);
			kill(pi,SIGCONT);
			waitpid(pi, &state, WUNTRACED);
			tcsetpgrp(0, getpgid(shell_pid));
			signal(SIGTTOU, SIG_DFL);
			signal(SIGTTIN, SIG_DFL);
			// if(WIFSTOPPED(state)){
			// 	  printf("fg stop\n");
			// 	  // printf("'%d'\n",pi );
			// 	  // printf("'%s'\n", l_com);
			// 		jobno++;
			// 		p_arr[jobno-1].pid=pi;
			// 		strcpy(p_arr[jobno-1].name,l_com);
			// }
			

		}

		else{

			fore(s5,k2);
		}
	}
	else
	{	
		back(s5,k2);
	}


}
void handl2(int sig){
	;
}
void handl3(int sig){
	
	;
}
void handl4(int sig){
	;
}

int redirec_check(char arrayy[100]){
	indec_cnt=0;outdec_cnt=0;
	for (int i1= 0; i1 < strlen(arrayy)-1; ++i1)
	{
		if(arrayy[i1]=='<' ){
			indec_cnt++;
			indec_pos=i1;
		}  
		if(arrayy[i1]=='>'){
			outdec_cnt++;
			outdec_pos=i1;
		}   

	}
	// printf("%c%c\n",arrayy[outdec_pos-1],arrayy[outdec_pos] );
	if(indec_cnt>1 ){
		printf("invalid command\n");
		return -1;
	}
	else if (outdec_cnt>1)
	{
		if(outdec_cnt==2 && arrayy[outdec_pos-1]==arrayy[outdec_pos]);
		else{
			printf("invalid command\n");
			return -1;
		}
	}
	else if(outdec_cnt==0 && indec_cnt==0){
		return 0;
	}
	return 1;
}
void redirec(char arrayy[100]){
	char s_red[3][100],temp[100],temp2[100];
	pid_t filed,filed2;
	int it,it2,i1;
	if(outdec_cnt==1 && indec_cnt==0){
		for ( i1 = 0; i1 < outdec_pos; ++i1)
		{
			s_red[0][i1]=arrayy[i1];
		}
		s_red[0][i1]='\0';
		for ( i1 = outdec_pos+1; i1 < strlen(arrayy); ++i1)
		{
			s_red[1][i1-outdec_pos-1]=arrayy[i1];
		}
		it=0;
		for (int ii = 0; ii <strlen(s_red[1]) ; ++ii)
		{
			if(s_red[1][ii]!=' '){
				temp[it]=s_red[1][ii];
				it++;
			}
		}
		temp[it]='\0';

		filed = open(temp, O_RDWR | O_CREAT|O_TRUNC,0777); 
		dup2(filed,1);
		close(filed);

            //cmd st
		all_check(s_red[0]);
           //cmd end
		dup2(std__out,1);

	}
	else if(outdec_cnt==2 && indec_cnt==0 && arrayy[outdec_pos-1]==arrayy[outdec_pos]){
		for (i1 = 0; i1 < outdec_pos-1; ++i1)
		{
			s_red[0][i1]=arrayy[i1];
		}
		s_red[0][i1]='\0';
		for ( i1 = outdec_pos+1; i1 < strlen(arrayy); ++i1)
		{
			s_red[1][i1-1-outdec_pos]=arrayy[i1];

		} 
		it=0;
		for (int ii = 0; ii <strlen(s_red[1]) ; ++ii)
		{
			if(s_red[1][ii]!=' '){
				temp[it]=s_red[1][ii];
				it++;
			}
		}
		temp[it]='\0';
		
		filed = open(temp, O_RDWR | O_CREAT|O_APPEND,0777); 
		dup2(filed,1);
		close(filed);
              //cmd st
		all_check(s_red[0]);
              //cmd end
		dup2(std__out,1);

	}

	else if(outdec_cnt==0 && indec_cnt==1){
		for (i1 = 0; i1 < indec_pos; ++i1)
		{
			s_red[0][i1]=arrayy[i1];
		}
		s_red[0][i1]='\0';
		for (i1 = indec_pos+1; i1 < strlen(arrayy); ++i1)
		{
			s_red[1][i1-1-indec_pos]=arrayy[i1];
		}
		it=0;
		for (int ii = 0; ii <strlen(s_red[1]) ; ++ii)
		{
			if(s_red[1][ii]!=' '){
				temp[it]=s_red[1][ii];
				it++;
			}
		}
		temp[it]='\0';
		
		filed = open(temp, O_RDONLY,0777); 
		dup2(filed,0);
      //cmd st
		all_check(s_red[0]);
        //cmd end
		close(filed);	
		dup2(std__in,0);
	}	
	else if(outdec_cnt!=0 && indec_cnt==1 && indec_pos<outdec_pos){
		for ( i1 = 0; i1 < indec_pos; ++i1)
		{
			s_red[0][i1]=arrayy[i1];
		}
		s_red[0][i1]='\0';
		if(outdec_cnt==1){
			for (i1 = indec_pos+1; i1 < outdec_pos; ++i1)
			{
				s_red[1][i1-1-indec_pos]=arrayy[i1];

			}
			s_red[1][i1-1-indec_pos-1]='\0';

			for ( i1 = outdec_pos+1; i1 < strlen(arrayy); ++i1)
			{
				s_red[2][i1-1-outdec_pos]=arrayy[i1];
			}
			s_red[2][i1-outdec_pos-1]='\0';
			it=0;
			for (int ii = 0; ii <strlen(s_red[1]) ; ++ii)
			{
				if(s_red[1][ii]!=' '){
					temp[it]=s_red[1][ii];
					it++;
				}
			}
			temp[it]='\0';
			
			it=0;
			for (int ii = 0; ii <strlen(s_red[2]) ; ++ii)
			{
				if(s_red[2][ii]!=' '){
					temp2[it]=s_red[2][ii];
					it++;
				}
			}
			temp2[it]='\0';
			
			filed = open(temp, O_RDONLY,0777);
			if(filed<0)
				perror("error opening input file");
			filed2 = open(temp2, O_RDWR | O_CREAT|O_TRUNC,0777);
			if(filed2<0)
				perror("error opening output file");


			dup2(filed2,1); 
			dup2(filed,0);
         // cmd st
			all_check(s_red[0]);
         //cmd end
			close(filed);	
			dup2(std__in,0);
			close(filed2);
			dup2(std__out,1);
			

		}
		else if(outdec_cnt==2 && arrayy[outdec_pos-1]==arrayy[outdec_pos]){
			for ( i1 = indec_pos+1; i1 < outdec_pos-1; ++i1)
			{
				s_red[1][i1-1-indec_pos]=arrayy[i1];
			}
			s_red[1][i1-1-indec_pos]='\0';
			for ( i1 = outdec_pos+1; i1 < strlen(arrayy); ++i1)
			{
				s_red[2][i1-outdec_pos-1]=arrayy[i1];
				
			}
			s_red[2][i1-1-outdec_pos]='\0';
			it=0;
			for (int ii = 0; ii <strlen(s_red[1]) ; ++ii)
			{
				if(s_red[1][ii]!=' '){
					temp[it]=s_red[1][ii];
					it++;
				}
			}
			temp[it]='\0';
			
			it=0;
			for (int ii = 0; ii <strlen(s_red[2]) ; ++ii)
			{
				if(s_red[2][ii]!=' '){
					temp2[it]=s_red[2][ii];
					it++;
				}
			}
			temp2[it]='\0';
			
			filed = open(temp, O_RDONLY,0777);
			if(filed<0)
				perror("error opening input file");
			filed2 = open(temp2, O_RDWR | O_CREAT|O_APPEND,0777);
			if(filed2<0)
				perror("error opening output file");


			dup2(filed2,1); 
			dup2(filed,0);
         // cmd st
			all_check(s_red[0]);
         //cmd end
			close(filed);	
			dup2(std__in,0);
			close(filed2);
			dup2(std__out,1);

		}

	}
	else if(outdec_cnt!=0 && indec_cnt==1 && indec_pos>outdec_pos){
		if (outdec_cnt==1)
		{
			for ( i1 = 0; i1 < outdec_pos; ++i1)
			{
				s_red[0][i1]=arrayy[i1];
			}
			s_red[0][i1]='\0';
			for (i1 = outdec_pos+1; i1 < indec_pos; ++i1)
			{
				s_red[1][i1-1-outdec_pos]=arrayy[i1];

			}
			s_red[1][i1-1-outdec_pos-1]='\0';

			for ( i1 = indec_pos+1; i1 < strlen(arrayy); ++i1)
			{
				s_red[2][i1-1-indec_pos]=arrayy[i1];
			}
			s_red[2][i1-indec_pos-1]='\0';
			it=0;
			for (int ii = 0; ii <strlen(s_red[1]) ; ++ii)
			{
				if(s_red[1][ii]!=' '){
					temp[it]=s_red[1][ii];
					it++;
				}
			}
			temp[it]='\0';
			
			it=0;
			for (int ii = 0; ii <strlen(s_red[2]) ; ++ii)
			{
				if(s_red[2][ii]!=' '){
					temp2[it]=s_red[2][ii];
					it++;
				}
			}
			temp2[it]='\0';
			// printf("'%s'\n",s_red[0] );
			// printf("'%s'\n", temp);
			// printf("'%s'\n", temp2);
			filed = open(temp2, O_RDONLY,0777);
			if(filed<0)
				perror("error opening input file");
			filed2 = open(temp, O_RDWR | O_CREAT|O_TRUNC,0777);
			if(filed2<0)
				perror("error opening output file");

			dup2(filed2,1); 
			dup2(filed,0);
         // cmd st
			all_check(s_red[0]);
         //cmd end
			close(filed);	
			dup2(std__in,0);
			close(filed2);
			dup2(std__out,1);



		}
		else if (outdec_cnt==2 && arrayy[outdec_pos-1]==arrayy[outdec_pos])
		{
			for ( i1 = 0; i1 < outdec_pos-1; ++i1)
			{
				s_red[0][i1]=arrayy[i1];
			}
			s_red[0][i1]='\0';
			for (i1 = outdec_pos+1; i1 < indec_pos; ++i1)
			{
				s_red[1][i1-1-outdec_pos]=arrayy[i1];

			}
			s_red[1][i1-1-outdec_pos-1]='\0';

			for ( i1 = indec_pos+1; i1 < strlen(arrayy); ++i1)
			{
				s_red[2][i1-1-indec_pos]=arrayy[i1];
			}
			s_red[2][i1-indec_pos-1]='\0';
			it=0;
			for (int ii = 0; ii <strlen(s_red[1]) ; ++ii)
			{
				if(s_red[1][ii]!=' '){
					temp[it]=s_red[1][ii];
					it++;
				}
			}
			temp[it]='\0';
			
			it=0;
			for (int ii = 0; ii <strlen(s_red[2]) ; ++ii)
			{
				if(s_red[2][ii]!=' '){
					temp2[it]=s_red[2][ii];
					it++;
				}
			}
			temp2[it]='\0';
			// printf("'%s'\n",s_red[0]);
			// printf("'%s'\n", temp);
			// printf("'%s'\n", temp2);
			filed = open(temp2, O_RDONLY,0777);
			if(filed<0)
				perror("error opening input file");
			filed2 = open(temp, O_RDWR | O_CREAT |O_APPEND,0777);
			if(filed2<0)
				perror("error opening output file");
			
			dup2(filed2,1); 
			dup2(filed,0);
         // cmd st
			all_check(s_red[0]);
         //cmd end
			close(filed);	
			dup2(std__in,0);
			close(filed2);
			dup2(std__out,1);

		}


	}

}



void check(char s1[100])
{
	int i=0;	
	char* token = strtok(s1, ";"); 
	while (token != NULL) { 
		strcpy(s2[i],token);
		token = strtok(NULL, ";");
		i++;
	} 
	for (int j = 0; j < i; ++j)
	{
		// printf("'%s'\n",s2[j] );
		k=0;
		flag=0;
		flag2=0;
		char* token2 = strtok(s2[j], "|"); 
		while (token2 != NULL) { 
			strcpy(s3[k],token2);
			token2 = strtok(NULL, "|");
			k++;
		} 
		strcpy(s3[k],"\0");
		
		if(k==1){

			if(redirec_check(s3[0])==1){
				redirec(s3[0]);
				break;	
			}
			else if (redirec_check(s3[0])==-1)
			{
				return;
			}
			all_check(s3[0]);

		}

		else{
			int fds[2];
			int j2 = 0;
			for (j2 = 0; j2 < k-1; j2++)
			{       
				
				if(pipe(fds)==-1){
					perror("pipe");
					exit(1);
				}

				pid_t cpid=fork();
				if (cpid == -1)
				{
					perror("fork");
					exit(0);
				}
	// child 
				else if(cpid==0)
				{
					{
						dup2(fds[1],1);
						close(fds[1]);
					}
					dup2(zz,0);
					close(fds[0]);
					

                   // standard code used before which works(given command)
					if(redirec_check(s3[j2])==1){
						redirec(s3[j2]);
						exit(0);	
					}
					else if (redirec_check(s3[j2])==-1)
					{
						printf("invalid\n");
						exit(0);
					}
					all_check(s3[j2]);
					
              // end of standard code(command)
					exit(1);
				}
				else{
				
				wait(NULL);		
				close(fds[1]);
					wait(NULL);		
					close(fds[1]);
					zz	 = fds[0];
				}

			}
                 // handler for end of pipe

			if(pipe(fds)==-1){
				perror("pipe");
				exit(1);
			}

			int cpid=fork();
			if (cpid == -1)
			{
				perror("fork");
				exit(0);
			}
	// child 
			else if(cpid==0)
			{
				dup2(zz,0);
				close(fds[0]);


                   // standard code used before which works(given command)
				if(redirec_check(s3[j2])==1)
				{
					redirec(s3[j2]);
					exit(0);	
				}
				else if (redirec_check(s3[j2])==-1)
				{
					printf("Invalid \n");
					exit(0);
				}
				all_check(s3[j2]);
				
              // end of standard code(command)
				exit(1);
			}
			else{
				
				wait(NULL);		
				close(fds[1]);
					// zz = fds[0];
			}

		}

		strcpy(s3[k],"");

	}

}





int main()
{
	std__in = dup(0);
	std__out=dup(1);
	while(1 )
	{
		shell_pid=getpid();
		signal(SIGINT,handl2);
		signal(SIGTSTP,handl3);
		signal(SIGQUIT,handl4);
		if(q==0){
			strcpy(home_dir,getcwd(s,1000));
		}
			strcpy(curr_dir,getcwd(s,1000)); //home_dir --> home_dir - 1 --> 


			q++;
			buf=(char*)malloc(100*sizeof(char));
			struct utsname node_name;
			if(strcmp(curr_dir,home_dir)==0)
				strcpy(curr_dir,"~");
			else
				strcpy(curr_dir,getcwd(s,1000));
			if (uname(&node_name) != 0) 
			{
				perror("uname");
				exit(EXIT_FAILURE);
			}

			
             // printf("hell\n");
			printf("\x1b[33m");
			printf("<%s@%s:%s> ",getenv("USER"),node_name.nodename,curr_dir);
			printf("\x1b[0m");
			getline(&buf,&bufsize,stdin);
			// fflush(stdin);
			buf[strlen(buf)-1]='\0';
			// printf("'%s'\n",buf );
			if (strcmp(" ",buf)==0 || strcmp("\n",buf)==0)
			{
				continue;
             	// printf("\n");
			}
			// printf("'hello1' %s\n",buf );

			check(buf);
			// fflush(stdout);
			free(buf);

		}


	}
















