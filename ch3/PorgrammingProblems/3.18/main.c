#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
  pid_t pid = fork();

  if (pid == 0) {
    // child
    sleep(10);
  } else if (pid > 0) {
    // parent
    exit(0);
  }

  return 0;
}
