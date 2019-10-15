main: main.o redesocial.o avl.o lista.o
	gcc -o main main.o redesocial.o avl.o lista.o

main.o: main.c redesocial.h
	gcc -c main.c

redesocial.o: redesocial.c redesocial.h lista.h avl.h
	gcc -c redesocial.c

avl.o: avl.c avl.h lista.h
	gcc -c avl.c

lista.o: lista.c lista.h
	gcc -c lista.c