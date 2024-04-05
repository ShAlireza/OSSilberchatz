#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
  pid_t pid = fork();

  if (pid == 0) {
    // child
    exit(1);
  } else if (pid > 0) {
    // parent
    sleep(10);
  }

  return 0;
}
