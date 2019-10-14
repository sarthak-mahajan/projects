#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "head.h"

void echo(char s_ech[100][100]){
	int i=1;
    while(strcmp(s_ech[i],"\0")!=0){
  	 printf("%s ",s_ech[i]);
  	 i++;
    }
    printf("\n");
}
