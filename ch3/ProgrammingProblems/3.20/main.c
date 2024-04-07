#include <stdlib.h>
#include <stdio.h>

#define MIN_PID 300
#define MAX_PID 5000

unsigned char *bitmap = NULL;


int allocate_map() {
  bitmap = (unsigned char *)malloc(MAX_PID - MIN_PID + 1);

  if (bitmap == NULL) {
    return -1;
  }

  return 1;
}

int allocate_pid() {
  for (int i = 0; i < MAX_PID - MIN_PID + 1; i++) {
    if (!bitmap[i]) {
      bitmap[i] = 1;
      return i + MIN_PID;
    }
  }

  return -1;
}

void release_pid(int pid) {
  bitmap[pid - MIN_PID] = 0;
}

int main(int argc, char *argv[]) {
  allocate_map();

  int pid1 = allocate_pid();
  printf("pid1: %d\n", pid1);
  int pid2 = allocate_pid();
  printf("pid2: %d\n", pid2);
  int pid3 = allocate_pid();
  printf("pid3: %d\n", pid3);

  release_pid(pid1);
  release_pid(pid2);
  release_pid(pid3);
  int pid4 = allocate_pid();
  printf("pid4: %d\n", pid4);
}
