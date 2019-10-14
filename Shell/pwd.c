#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "head.h"

void pwd(char home_dir2[100]){
	int boo=0;
	char str_pwd[100];
	char str_pwd2[100];
	char str_pwd3[100];
	for (int i = 0; i < strlen(home_dir2); ++i)
	{
        if(home_dir2[i]!=getcwd(str_pwd,100)[i])
        	boo=1;
	}

   if(boo==0){
    for (int i = strlen(home_dir2); i < strlen(getcwd(str_pwd,100)); ++i)
    {
    	str_pwd2[i-strlen(home_dir2)]=getcwd(str_pwd,100)[i];
    }
    strcpy(str_pwd3,"~/");
    strcat(str_pwd3,str_pwd2);
   	printf("%s\n",str_pwd3 );
   }
   else
   	printf("%s",getcwd(str_pwd,100));

}
