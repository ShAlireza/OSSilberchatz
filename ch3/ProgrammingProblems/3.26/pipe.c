#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

char *reverse(char *s) {
  int len = strlen(s);
  char *result = malloc(len + 1);
  result[len] = '\0';

  for (int i = 0; i < len; i++) {
    result[i] = s[len - 1 - i];
  }

  return result;
}


int main(int argc, char *argv[]) {

  int parent_writer[2];
  int child_writer[2];
  pipe(parent_writer);
  pipe(child_writer);

  pid_t pid = fork();

  if (pid == 0) {
    // child
    close(parent_writer[1]);
    close(child_writer[0]);
    char buffer[512];

    read(parent_writer[0], buffer, sizeof(buffer));
    close(parent_writer[0]);
    char *message = reverse(buffer);
    write(child_writer[1], message, strlen(message));
    close(child_writer[1]);

  } else if (pid > 0) {
    // parent
    close(parent_writer[0]);
    close(child_writer[1]);

    char *message = "Hello World!";
    char buffer[512];
    write(parent_writer[1], message, strlen(message));
    close(parent_writer[1]);
    wait(NULL);
    read(child_writer[0], buffer, sizeof(buffer));
    close(child_writer[0]);

    printf("Processed Message: %s\n", buffer);
  }

  return 0;
}
