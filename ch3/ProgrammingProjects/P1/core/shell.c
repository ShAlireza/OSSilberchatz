#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>

#include "shell.h"
#include "utils.h"


int main(int argc, char *argv[]) {

  run();

  return 0;
}


void run() {

  char input[INPUT_SIZE];
  int tokens_count;
  char *pwd = read_env("PWD", "");
  char prefix[1024];

  memcpy(prefix, pwd, strlen(pwd) + 1);
  replace_substring(prefix, "/home/alireza", "~");


  while (1) {
    
    setlocale(LC_ALL, "");
    // wchar_t ch = L'\u250C';
    // wprintf(L"%lc", ch);

    printf("%c\033[32m%s\033[0m\n", 218, prefix);
    printf("%c\033[33m(%s)\033[0m $ ", 192, get_current_time());

    fgets(input, sizeof(input), stdin);

    input[strcspn(input, "\n")] = 0;

    if (!strcmp(input, "exit")) {
      exit(0);
    } else if (!strcmp(input, "quit")) {
      exit(0);
    } else {
      char **tokens = split(input, &tokens_count);
      char *PATH = read_env(PATH_ENV, ".");
      char *binary = find_binary(PATH, tokens[0]);

      if (binary != NULL) {
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
        printf("'%s' executable not found!\n", tokens[0]);
      }

    }
  }

}
