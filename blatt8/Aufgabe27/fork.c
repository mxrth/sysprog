#include <stdio.h>

int main(void) {
  int cnt = 0;
  int fork_pid = getppid();
  printf("cnt = %d, fork_pid = %5d, my_pid = %5d\n", cnt, fork_pid, getpid());
  fork_pid = fork();
  cnt++;
  printf("cnt = %d, fork_pid = %5d, my_pid = %5d\n", cnt, fork_pid, getpid());
  fork_pid = fork();
  cnt++;
  printf("cnt = %d, fork_pid = %5d, my_pid = %5d\n", cnt, fork_pid, getpid());
}
