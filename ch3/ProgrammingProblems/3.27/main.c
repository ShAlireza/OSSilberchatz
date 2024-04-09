#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/types.h>


int main(int argc, char *argv[]) {

  int parent_writer[2];
  char *src = argv[1];
  char *dst = argv[2];

  pipe(parent_writer);

  pid_t pid = fork();

  if (pid == 0) {
    // child
    close(parent_writer[1]);
    char buffer[4 * 1024];
    size_t bytes;

    int file = open(dst, O_WRONLY | O_CREAT, 0666);
    while ((bytes = read(parent_writer[0], buffer, sizeof(buffer))) > 0) {
      write(file, buffer, bytes);
    }
    close(parent_writer[0]);
    close(file);

  } else if (pid > 0) {
    // parent
    close(parent_writer[0]);


    char buffer[4 * 1024];
    FILE *file = NULL;
    size_t bytes;
    file = fopen(src, "r");
    if (file != NULL) {
      while ((bytes = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        write(parent_writer[1], buffer, bytes);
        printf("Chunk: %s", buffer);
      }

    }

    close(parent_writer[1]);
    wait(NULL);
  }

  return 0;
}
