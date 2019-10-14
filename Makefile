all: shell
shell: shell.o ls.o cd.o pwd.o pinfo.o echo.o background.o foreground.o
	gcc shell.o ls.o cd.o pwd.o pinfo.o echo.o background.o foreground.o  -o shell
shell.o: shell.c
	gcc -c shell.c
ls.o: ls.c
	gcc -c ls.c
cd.o: cd.c
	gcc -c cd.c
pwd.o: pwd.c
	gcc -c pwd.c
pinfo.o: pinfo.c
	gcc -c pinfo.c
echo.o: echo.c
	gcc -c echo.c
background.o: background.c
	gcc -c background.c
foreground.o: foreground.c
	gcc -c foreground.c
clean:
	rm -rf *.o shell
   


