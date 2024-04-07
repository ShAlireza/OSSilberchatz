#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[]) {

  int input = atoi(argv[1]);

  if (input < 0) {
    printf("Input should be non-negative!\n");
    exit(1);
  }

  int fd = shm_open(".temp", O_CREAT | O_RDWR, 0666);
  ftruncate(fd, sizeof(int) * 1000);
  int *shmem = (int *)mmap(0, sizeof(int) * 1000, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  pid_t pid = fork();

  if (pid < 0) {
    printf("Failed to create a child!\n");
    exit(1);
  }

  if (pid == 0) {
    // child
    int n = input;
    shmem[0] = n;
    int i = 1;
    do {
      if (n % 2) {
        n = 3 * n  + 1;
      } else {
        n = n / 2;
      }
      shmem[i++] = n;
    } while (n != 1);
    shmem[i] = -1;

  } else if (pid > 0) {
    // parent
    wait(NULL);
    int i = 0;
    while (shmem[i] != -1) {
      printf("%d\n", shmem[i++]);
    }
  }

  return 0;
}
