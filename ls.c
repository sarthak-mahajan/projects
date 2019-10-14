#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <ctype.h>
#include <dirent.h>
#include <getopt.h>
#include <grp.h>
// #include <stdboo2l.h>
#include <time.h>
#include <string.h>
#include <strings.h>
#include <sysexits.h>
#include <time.h>
#include <langinfo.h>
#include "head.h"
char s_tok2[3][100];
void tok(char* s_tok){
	int i=0;
	char* token = strtok(s_tok, " "); 
	while (token != NULL) { 
		token = strtok(NULL, " ");
		if(i==0)
			strcpy(s_tok2[0],token);
		if(i==1)
			strcpy(s_tok2[1],token);

		if(i==2)
			strcpy(s_tok2[2],token);

		i++;
	} 

}
void print_perm(mode_t perm1){
	if(S_ISDIR(perm1))
		printf("%c",'d');
	else
		printf("%c",'-');
	if(perm1  & S_IRUSR)
		printf("%c",'r');
	else
		printf("%c",'-');
	if(perm1  & S_IWUSR)
		printf("%c",'w');
	else
		printf("%c",'-');
	if(perm1  & S_IXUSR)
		printf("%c",'x');
	else
		printf("%c",'-');
	if(perm1  & S_IRGRP)
		printf("%c",'r');
	else
		printf("%c",'-');
	if(perm1  & S_IWGRP)
		printf("%c",'w');
	else
		printf("%c",'-');
	if(perm1  & S_IXGRP)
		printf("%c",'x');
	else
		printf("%c",'-');
	if(perm1  & S_IROTH)
		printf("%c",'r');
	else
		printf("%c",'-');
	if(perm1  & S_IWOTH)
		printf("%c",'w');
	else
		printf("%c",'-');
	if(perm1  & S_IXOTH)
		printf("%c",'x');
	else
		printf("%c",'-');

	printf(" ");
}


void ls(char s_ls[100][100],char home_dir4[100]){
   // printf("%s\n",s_ls[0]);
	
	// int l=0;
	 // while(strcmp(s_ls[l],"\0")!=0)
          // {
          // 	printf("%s\n",s_ls[l]);
          // 	l++;
          // }
	int bool_l=0,bool_a=0,bool_garb=0;
	char s_ls2[100][100];
	char s_ls3[100][100];
	for (int i = 1; i < 100 ; ++i){
		if(bool_garb==1){
			printf("wrong flag\n");
			return;
		}
		if(s_ls[i][0]=='-'){
			int j=1;
			while(s_ls[i][j]!='\0'){
				if(s_ls[i][j]=='l'){
					bool_l=1;
				}
				else if(s_ls[i][j]=='a')
					bool_a=1;
				else{
					bool_garb=1;
				}

				j++;
			}

		}
		if(s_ls[i][0]=='~'){
			char temp[100];
			char temp2[100];
			for (int k = 1; k <strlen(s_ls[i]); ++k){
				temp[k-1]=s_ls[i][k];    	
			}
			strcpy(temp2,home_dir4);
			strcat(temp2,temp);
     // strcpy(s_ls[i-1],"");
			strcpy(s_ls2[i-1],temp2);
     // printf("%s\n",s_ls2[i-1]);
		}
		else{
			strcpy(s_ls2[i-1],s_ls[i]);
		}

	}
	int k=0;
	for (int i = 0; i <100; ++i){ 
		if(s_ls2[i][0]!='-'){
			strcpy(s_ls3[k],s_ls2[i]);
			k++;
		}
	}
	




	struct dirent **namelist;
	struct stat my_stat;	
	struct stat my_stat2;	
	int n;
      
      // printf("s_ls3[0]%s",s_ls3[0]);

	if(strcmp(s_ls3[0],"\0")!=0){
	int i=0;
	while(strcmp(s_ls3[i],"\0")!=0){
		n = scandir(s_ls3[i], &namelist, NULL, alphasort);
		if (n == -1) {
			perror("directory doesn't exist");
			i++;
			continue;
		}
            printf("\n%s:\n",s_ls3[i]);
		if(bool_a==0 && bool_l==0){
			while (n--){
				if(namelist!=NULL){
					char temp3[100];
					strcpy(temp3,namelist[n]->d_name);
					if(temp3[0]!='.'){
						printf("%s\n", namelist[n]->d_name);
					}
				// free(namelist[n]);
				}
			}
		}
		if(bool_a==0 && bool_l==1){
			while (n--){
				char temp6[100];
				strcpy(temp6,namelist[n]->d_name);
				if(temp6[0]!='.'){
					if(namelist!=NULL){
						char temp7[100];
						char temp8[100];
						strcpy(temp7,namelist[n]->d_name);
						strcpy(temp8,s_ls3[i]);
						strcat(temp8,"/");
						strcat(temp8,temp7);
						stat(temp8,&my_stat);
						
					// printf("total: %d\n",total);
						print_perm(my_stat.st_mode);
						// printf("%d ",my_stat.st_nlink);


						printf("%s ",getenv("USER"));
						printf("%10s ", getgrgid(my_stat.st_gid)->gr_name);


						printf("%d ",my_stat.st_size);
						time_t t = my_stat.st_mtime;
						struct tm t_1;
						localtime_r(&t, &t_1);
						char tim[80];
						strftime(tim, sizeof(tim), "%c", &t_1);
						tok(tim);
						printf("%s ",s_tok2[0]);
						printf("%s ",s_tok2[1]);
						printf("%s ",s_tok2[2]);
						printf("%s\n", namelist[n]->d_name);
                       // printf("st_block%d\n",my_stat.st_blocks);
						// printf("total:%d\n",total);
						// total+=my_stat.st_blocks;

					}
				}
				// free(namelist[n]);
			}



		}
		if(bool_l==1 && bool_a==1){
			while(n--){
				if(namelist!=NULL){
					char temp4[100];
					char temp5[100];
					strcpy(temp4,namelist[n]->d_name);
					strcpy(temp5,s_ls3[i]);
					strcat(temp5,"/");
					strcat(temp5,temp4);
					stat(temp5,&my_stat);
					// total+=my_stat.st_blocks;
					// if(n==n2-1)
					// printf("total: %d\n",total );
					print_perm(my_stat.st_mode);
					printf("%d ",my_stat.st_nlink);

					

					printf("%s ",getenv("USER"));
					printf("%10s ", getgrgid(my_stat.st_gid)->gr_name);


					printf("%d ",my_stat.st_size);
					time_t t2 = my_stat.st_mtime;
					struct tm t_2;
					localtime_r(&t2, &t_2);
					char tim2[80];
					strftime(tim2, sizeof(tim2), "%c", &t_2);
					tok(tim2);
					printf("%s ",s_tok2[0]);
					printf("%s ",s_tok2[1]);
					printf("%s ",s_tok2[2]);

					printf("%s", namelist[n]->d_name);


				// free(namelist[n2]);
					printf("\n");
				}
			} 
		}
		if(bool_l==0 && bool_a==1){
			while(n--){
				if(namelist!=NULL){
					printf("%s\n", namelist[n]->d_name);
				}				  
				// free(namelist[n2]);
			} 
		}
		i++;
	}  
}
else{
        
n = scandir(".", &namelist, NULL, alphasort);
		if (n == -1) {
			perror("directory doesn't exist");
		}
           printf("\n.:\n");
		if(bool_a==0 && bool_l==0){
			while (n--){
				if(namelist!=NULL){
					
					char temp3[100];
					strcpy(temp3,namelist[n]->d_name);
					if(temp3[0]!='.'){
						printf("%s\n", namelist[n]->d_name);
					}
				// free(namelist[n]);
				}
			}
		}
		if(bool_a==0 && bool_l==1){
			while (n--){
				char temp6[100];
				strcpy(temp6,namelist[n]->d_name);
				if(temp6[0]!='.'){
					if(namelist!=NULL){

						char temp7[100];
						char temp8[100];
						strcpy(temp7,namelist[n]->d_name);
						strcpy(temp8,".");
						strcat(temp8,"/");
						strcat(temp8,temp7);
						stat(temp8,&my_stat2);
						
					// printf("total: %d\n",total);
						print_perm(my_stat2.st_mode);
						// printf("%d ",my_stat.st_nlink);

						
						

						printf("%s ",getenv("USER"));
						printf("%10s ", getgrgid(my_stat2.st_gid)->gr_name);


						printf("%d ",my_stat2.st_size);
						time_t t = my_stat2.st_mtime;
						struct tm t_1;
						localtime_r(&t, &t_1);
						char tim[80];
						strftime(tim, sizeof(tim), "%c", &t_1);
						tok(tim);
						printf("%s ",s_tok2[0]);
						printf("%s ",s_tok2[1]);
						printf("%s ",s_tok2[2]);
						printf("%s\n", namelist[n]->d_name);
                       // printf("st_block%d\n",my_stat.st_blocks);
						// printf("total:%d\n",total);
						// total+=my_stat.st_blocks;

					}
				}
				// free(namelist[n]);
			}



		}
		if(bool_l==1 && bool_a==1){
			while(n--){
				if(namelist!=NULL){
					char temp4[100];
					char temp5[100];
					strcpy(temp4,namelist[n]->d_name);
					strcpy(temp5,".");
					strcat(temp5,"/");
					strcat(temp5,temp4);
					stat(temp5,&my_stat2);
					// total+=my_stat.st_blocks;
					// if(n==n2-1)
					// printf("total: %d\n",total );
					print_perm(my_stat2.st_mode);
					printf("%d ",my_stat2.st_nlink);

					
					

					printf("%s ",getenv("USER"));
					printf("%10s ", getgrgid(my_stat2.st_gid)->gr_name);


					printf("%d ",my_stat2.st_size);
					time_t t2 = my_stat2.st_mtime;
					struct tm t_2;
					localtime_r(&t2, &t_2);
					char tim2[80];
					strftime(tim2, sizeof(tim2), "%c", &t_2);
					tok(tim2);
					printf("%s ",s_tok2[0]);
					printf("%s ",s_tok2[1]);
					printf("%s ",s_tok2[2]);

					printf("%s", namelist[n]->d_name);


				// free(namelist[n2]);
					printf("\n");
				}
			} 
		}
		if(bool_l==0 && bool_a==1){
			while(n--){
				if(namelist!=NULL){
					printf("%s\n", namelist[n]->d_name);
				}				  
				// free(namelist[n2]);
			} 
		}

	}


}




























