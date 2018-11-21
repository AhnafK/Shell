all: shell.o
	gcc -o shell shell.c
shell.o: shell.c
	gcc -c shell.c
run:
	./shell
clear:
	rm shell *.o
