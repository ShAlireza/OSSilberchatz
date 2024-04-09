PROGRAM=copy
all: main.o
	gcc -o $(PROGRAM) main.o

main.o: main.c
	gcc -c main.c

clean: 
	rm -f $(PROGRAM) main.o
