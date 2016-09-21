CFLAGS = -g -Wall 
CC = gcc
objects = myshell.o parse.o compute.o

myshell: $(objects)
	$(CC) -o myshell $(objects)

parse.o:   parse.c parse.h structures.h
compute.o: compute.c compute.h structures.h
myshell.o: myshell.c parse.h compute.h

.PHONY : clean
clean: 
	rm myshell $(objects)