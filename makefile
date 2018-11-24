all: shell.o
	gcc -o shell shell.c -lreadline
shell.o: shell.c
	gcc -c shell.c
run:
	./shell
clear:
	rm shell *.o
