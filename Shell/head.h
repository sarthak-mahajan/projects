// void print_perm(mode_t);
// void ls(char*,char*);0;
// #ifndef _head_h
// #define _head_h 
void echo(char[100][100]);
void pwd(char*);
void cd(char*,char*);
void ls(char[100][100],char*);
void pinfo(char*);
void back(char[100][100],int);
void fore(char[100][100],int);
typedef struct proc_list{
   pid_t pid;
   char name[100];
} pl;
pl p_arr[100];
int jobno;
int flag;
int flag2;
int std__out;
int std__in;
// int fds[2];
char home_dir[100];
char boofer[1000];
int zz;
pid_t fore_pid;
pid_t shell_pid;
char last_com[100];

