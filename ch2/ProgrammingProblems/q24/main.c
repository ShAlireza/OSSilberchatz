#include <stdio.h>
#include <stdlib.h>

char * read_file(char *filename) {
  char *buffer;
  long length;
  FILE *file = fopen(filename, "r");
  
  if (file != NULL) { 
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    rewind(file);

    buffer = malloc(length);

    if (buffer) {
      fread(buffer, 1, length, file);
    }
    fclose(file);
  }

  return buffer;
}

int write_to(char *filename, char *content) {
  FILE *file = fopen(filename, "w");

  if (file != NULL) {
    fprintf(file, "%s", content);
    return 0;
  }

  return 1;
}


int main(int argc, char* argv[]) {

  char *filename = argv[1];

  printf("Second argument: %s", argv[1]);

  char *file_content = read_file(filename);

  write_to("test.txt", file_content);

  
  return 0;
}
