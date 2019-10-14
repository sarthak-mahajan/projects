in shell.c:
  in main():
   command prompt is made and input is taken and sent to check function, also the directory from which the shell is run is considered as home directory. it calls only check() function.
  in all_check(chat[100]):
        we tokenise with space and perform required function using if-else ladder.
  in redirec_check(char[100]):
        checks if input for redirection is valid or not, sets values like position of input-output redirection arrow
  in redirec(char[100]):
        performs redirection on input array using if-else ladder based on values obtained from redirec_check()
  in check(char*):
  		the input taken is tokenised by ";" and "|". if-else ladder to check if piping needed or not and the if(k==1) part does for no pipes, and its 'else' parts is used if piping is involved.This function calls other functions like all_check(),redirec(),redirec_check().
in cd.c:
	cd(char*,char*):
		its inputs are the 1st space separated argument after 'cd' as taken input by the shell and the home directory, its does the same work as the cd in shell, and it also works for addresses with ~ included in them
in echo.c:
	echo(char**):
		does the same work as echo in the shell ,except that its flag-less, its input is the tokenised input taken by the shell
in pwd.c:
	pwd(char*):
		prints current working directory,its input is the home directory of the shell
in pinfo.c:
	pinfo(char*):
 		its input is the space separated string that comes after 'pinfo' , if there is one at all, it gives the process id,process status,memory and executable path of the current process or of the process mentioned(by its process id)
in ls.c:
	ls(char**,char*):
	 	its inputs are the input taken by the shell which is tokenised and the home directory,it implements the ls[al] for multiple arguments.
	tok(char*):
		it tokenises given input string
	print_perm(mode_t):
		its input is the .st_mode of the stat created using a given directory and it uses a series of if-else statements to print permissions for given directory. 
in background.c:
        back(char[100][100],int):
              handles background processes
in foreground.c
       fore(char[100][100],int):
             handles foreground processes except in-built commnds        
in Makefile:
	compiling all the codes together using  'make all; , 'make clean' deletes all the binary files created.



