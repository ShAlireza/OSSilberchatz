#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>

#include "shell.h"
#include "utils.h"


int main(int argc, char *argv[]) {

  run();
  return 0;
}

void run() {

  char input[1024];
  int tokens_count;

  while (1) {
    printf("$ ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    if (!strcmp(input, "exit")) {
      exit(0);
    }


    char **tokens = split(input, &tokens_count);
    char *PATH = read_env(PATH_ENV, ".");
    char *binary = find_binary(PATH, input);

    if (binary != NULL) {
      printf("Found binary: %s\n", binary);

      pid_t pid = fork();

      if (pid < 0) {
        printf("Failed to fork!\n");
      } else if (pid == 0) {
        // Child
        execv(binary, tokens);
      } else {
        // Parent
        wait(NULL);
      }

    } else {
      printf("Executable not found!\n");
    }

  }

}
