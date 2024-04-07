PROGRAM=ipc
pipe: pipe.o
	gcc -o pipe pipe.o

shmem: shmem.o
	gcc -o shmem shmem.o

pipe.o: pipe.c
	gcc -c pipe.c

shmem.o: shmem.c
	gcc -c shmem.c

clean: 
	rm -f pipe.o shmem.o pipe shmem
