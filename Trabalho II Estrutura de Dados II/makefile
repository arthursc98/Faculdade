cobertura_vacinal: main.o hashmap.o listaord.o avl.o cobertura.o
	gcc -o cobertura_vacinal main.o hashmap.o listaord.o avl.o cobertura.o -lm

main.o: main.c hashmap.h avl.h cobertura.h
	gcc -c main.c
	
hashmap.o: hashmap.c listaord.h hashmap.h
	gcc -c hashmap.c
	
listaord.o: listaord.c hashmap.h
	gcc -c listaord.c

cobertura.o: cobertura.c hashmap.h avl.h
	gcc -c cobertura.c

avl.o: avl.c avl.h
	gcc -c avl.c
