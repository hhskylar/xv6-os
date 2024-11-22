#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "user/user.h"
#define MAX_NUM 100 

void slove_primes(int readp, int write_p) {
  char nums[MAX_NUM];
  read(readp, nums, MAX_NUM);
  int prime = 0;
  for (int i = 2; i < MAX_NUM; i++) {
    if (nums[i] == '0') {
      prime = i;
      break;
    }
  }
  if (prime == 0) {
    return;
  }
  printf("primes %d\n", prime);
  nums[prime] = '1';
  for (int i = prime; i < MAX_NUM; i++) {
    if (i % prime == 0) {
      nums[i] = '1';
    }
  }

  int pid = fork();
  if (pid < 0) {
    printf("fork error pid %d\n", pid);
    exit(0);
  }
  if (pid == 0) {
    slove_primes(readp, write_p);
  } else {
    write(write_p, nums, MAX_NUM);
  }
  wait(0);
  exit(0);
}

int main(int argc, char* argv[]) {
  int p[2];
  if (pipe(p) < 0) {
    write(1, "error", 5);
    exit(-1);
  }
  char nums[MAX_NUM];
  memset(nums, '0', MAX_NUM);
  int pid = fork();
  if (pid == 0) {
    slove_primes(p[0], p[1]);
  } else {
    nums[0] = '1';
    nums[1] = '1';
    write(p[1], nums, MAX_NUM);
    wait(0);
  }

  close(p[0]);
  close(p[1]);
  exit(0);
}
