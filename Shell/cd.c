#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "head.h"

void cd(char str_cd[100],char home_dir3[100]){
  
int boo1=0,boo2=0;
	char str_cd2[100];
	char str_cd3[100];
	char str_cd4[100];
	if(str_cd[0]=='~')
		boo2=1;
	for (int i = 0; i < strlen(home_dir3); ++i)
	{
        if(home_dir3[i]!=str_cd[i]){
        	boo1=1;
        	break;
        }
	}

   if(boo1==0){
    for (int i = strlen(home_dir3); i < strlen(str_cd); ++i)
    {
    	str_cd2[i-strlen(home_dir3)]=str_cd[i];
    }
    strcpy(str_cd3,"~/");
    strcat(str_cd3,str_cd2);
   }
   else{
      strcpy(str_cd3,str_cd);
      // return str_cd;   
    }  

   if(boo2==0){
   	// printf("%s\n",str_cd);
   	chdir(str_cd);
   	// printf("%s\n", getcwd(s,100));
   	// printf("%s\n",str_cd);
   }
   else{
          for (int i = 1; i < strlen(str_cd); ++i)
          {
          	 str_cd4[i-1]=str_cd[i];
          }
           strcat(home_dir3,str_cd4);
           strcpy(str_cd4,home_dir3);
           chdir(str_cd4);
            // return ;
   }
   // return 1; 

}
 