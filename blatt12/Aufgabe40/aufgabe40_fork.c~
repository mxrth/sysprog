#include <stdio.h>
#include <unistd.h>

int main(void) {
  int i = 0;
  int cnt = 0;
  int fork_pid = getppid();
  printf("cnt = %d, fork_pid = %5d, my_pid = %5d\n", cnt, fork_pid, getpid());
  for(i = 0; i < 2; i++) {
    fork_pid = fork();
    cnt++;
    printf("cnt = %d, fork_pid = %5d, my_pid = %5d\n", cnt, fork_pid, getpid());
  }
}
