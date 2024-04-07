#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>


int main(int argc, char *argv[]) {

  int fd[2];
  pipe(fd);

  pid_t pid = fork();

  if (pid == 0) {
    // child
    close(fd[0]);
    unsigned long usec;
    struct timeval start;
    gettimeofday(&start, NULL);
    usec = start.tv_sec * 1000000 + start.tv_usec;
    write(fd[1], &usec, sizeof(unsigned long));
    execlp(argv[1], argv[1], NULL);
  } else if (pid > 0) {
    // parent
    close(fd[1]);
    unsigned long startus;
    read(fd[0], &startus, sizeof(unsigned long));
    wait(NULL);
    struct timeval end;
    gettimeofday(&end, NULL);
    unsigned long endus = end.tv_sec * 1000000 + end.tv_usec;

    printf("Total execution time: %ld", endus - startus);
  }

  return 0;
}
