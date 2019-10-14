#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h> 
#include <string.h>
#include <sys/utsname.h>
#include "head.h"



void pinfo(char s_info[100]){
	char path1[100];
	char path2[100];
	char status[100];
	char mem[100];
	char temp_buf[100];
	char buf_info1[1000];
	char buf_info2[10000];
	strcpy(path1,"/proc/");
	strcpy(path2,"/proc/");
	if(strcmp(s_info,"")==0){
		// printf("%d ", getpid())
		int p=getpid();
		int p2=p;
		int i=0;
		while(p!=0){
			temp_buf[i]=48+p%10;
			p=p/10;
			i++;
		}
		// printf("%d\n",p);
		for (int j = 0; j < i/2 ; ++j)
		{
			char temp_inf;
			temp_inf=temp_buf[j];
			temp_buf[j]=temp_buf[i-j-1];
			temp_buf[i-j-1]=temp_inf;

		}
		// printf("%s\n",temp_buf );
		strcat(path1,temp_buf);
		strcat(path2,temp_buf);
		strcat(path1,"/stat");
		strcat(path2,"/cmdline");
		printf("pid--%d\n",p2);
		// printf("path1--%s\n",path1);
		// printf("path2--%s\n",path2);
		// write(std__out,path1,strlen(path1));
		// printf("%s\n",path1);
		int fd1=open(path1,O_RDONLY);
		if (fd1<0)
		{
			perror("not running");
		}
		int fd2=open(path2,O_RDONLY);
		if (fd2<0)
		{
			perror("not running");
		}
		read(fd1,buf_info1,1000);
		read(fd2,buf_info2,1000);
		

		int i1=0;	
  // char new_buf[100];
		char* token = strtok(buf_info1, " "); 
		while (token != NULL && i1<=24) { 
			i1++;
        // strcpy(new_buf,token);
        // printf("%dnew=%s\n",i1,new_buf );
        // strcpy(new_buf,"");
			if (i1==3)
			{
				strcpy(status,token);
			}
			if (i1==23)
			{
				strcpy(mem,token);
			}
			token = strtok(NULL, " ");


		} 

		printf("Process Status--%s\n",status);
		printf("memory--: %s bytes\n",mem);   
		printf("Executible Path--: %s\n",buf_info2 );


	}
	else{
		strcat(path1,s_info);
		strcat(path2,s_info);
		printf("pid--%s\n",s_info);
		strcat(path1,"/stat");
		strcat(path2,"/cmdline");
        int fd1=open(path1,O_RDONLY);
		int fd2=open(path2,O_RDONLY);
		if (fd1<0)
		{
			perror("not running");
			return;
		}
		if (fd2<0)
		{
			perror("not running");
			return;
		}
		read(fd1,buf_info1,1000);
		read(fd2,buf_info2,1000);
		

		int i1=0;	
 		// char new_buf[100];
		char* token = strtok(buf_info1, " "); 
		while (token != NULL && i1<=24) { 
			i1++;
        // strcpy(new_buf,token);
        // printf("%dnew=%s\n",i1,new_buf );
        // strcpy(new_buf,"");
			if (i1==3)
			{
				strcpy(status,token);
			}
			if (i1==23)
			{
				strcpy(mem,token);
			}
			token = strtok(NULL, " ");

		} 

		printf("Process Status--%s\n",status);
		printf("memory--: %s bytes\n",mem);   
		printf("Executible Path--: %s\n",buf_info2 );



	}

}