PROGRAM=server
all: main.o
	gcc -o $(PROGRAM) main.o cjson.o -lcurl

main.o: main.c
	gcc -c main.c cjson.c

clean: 
	rm -f $(PROGRAM) main.o cjson.o
