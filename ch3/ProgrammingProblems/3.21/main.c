#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[]) {

  int input = atoi(argv[1]);

  if (input < 0) {
    printf("Input should be non-negative!\n");
    exit(1);
  }

  pid_t pid = fork();

  if (pid < 0) {
    printf("Failed to create a child!\n");
    exit(1);
  }

  if (pid == 0) {
    // child
    int n = input;
    printf("%d\n", n);
    do {
      if (n % 2) {
        n = 3 * n  + 1;
      } else {
        n = n / 2;
      }
      printf("%d\n", n);
    } while (n != 1);

  } else if (pid > 0) {
    // parent
    wait(NULL);
  }

  return 0;
}
