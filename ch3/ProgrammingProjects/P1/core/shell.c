#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>


void run();
char **split(char *str, int *ret_size);

int main(int argc, char *argv[]) {

  run();
  return 0;
}


char **split(char *str, int *ret_size) {
  char * temp = str;
  int tokens_count = 1;

  while (*temp != '\0') {
    if (*temp == ' ') {
      tokens_count++;
      // while (*temp == ' ')
        // temp++;
    }
    temp++;
  }

  *ret_size = tokens_count;

  char **tokens = (char **)malloc(sizeof(char *) * tokens_count);
  char *token = strtok(str, " ");

  tokens[0] = token;
  int i = 1;
  while (token != NULL) {
    token = strtok(NULL, " ");
    tokens[i++] = token;
  }

  return tokens;
}


void run() {

  char input[1024];
  int tokens_count;

  while (1) {
    printf("$ ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    printf("Input was: %s\n", input);

    if (!strcmp(input, "exit")) {
      exit(0);
    }


    char **tokens = split(input, &tokens_count);
    
    printf("Printing tokens (total = %d): \n", tokens_count);
    for (int i = 0; i < tokens_count; i++) {
      printf("%s\n", tokens[i]);
    }

  }

}
