#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum;
void *runner(void *param);

int main(int argc, char *argv[]) {

  pthread_t tid;
  pthread_attr_t attr;

  pthread_attr_init(&attr);

  pthread_create(&tid, &attr, runner, argv[1]);
  pthread_join(tid, NULL);

  printf("Sum: %d\n", sum);

  return 0;
}


void *runner(void *param) {
  int i, upper = atoi(param);
  sum = 0;

  for (int i = 1; i <= upper; i++) {
    sum += i;
  }

  pthread_exit(0);
}
