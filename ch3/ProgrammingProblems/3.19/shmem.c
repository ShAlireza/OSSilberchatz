#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/mman.h>


void *create_shared_memory(size_t size) {
  int protection = PROT_READ | PROT_WRITE;
  int visibility = MAP_SHARED | MAP_ANONYMOUS;

  return mmap(NULL, size, protection, visibility, -1, 0);
}


int main(int argc, char *argv[]) {

  void *shmem = create_shared_memory(sizeof(unsigned long));
  pid_t pid = fork();

  if (pid == 0) {
    // child
    unsigned long usec;
    struct timeval start;
    gettimeofday(&start, NULL);
    usec = start.tv_sec * 1000000 + start.tv_usec;
    memcpy(shmem, &usec, sizeof(unsigned long));
    execlp(argv[1], argv[1], NULL);
  } else if (pid > 0) {
    // parent
    unsigned long startus;
    wait(NULL);
    struct timeval end;
    gettimeofday(&end, NULL);
    memcpy(&startus, shmem, sizeof(unsigned long));

    unsigned long endus = end.tv_sec * 1000000 + end.tv_usec;

    printf("Total execution time: %ld", endus - startus);
  }

  return 0;
}
