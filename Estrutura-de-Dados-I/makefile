main: main.o set.o
	gcc -o main main.o set.o
	
main.o: main.c set.h
	gcc -c main.c
	
set.o: set.c set.h
	gcc -c set.c