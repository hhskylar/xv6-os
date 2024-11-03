#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
  int p1[2];
  int p2[2];
  if (pipe(p1) < 0) {
    write(1, "error", 5);
    exit(-1);
  }
  if (pipe(p2) < 0) {
    write(1, "error", 5);
    exit(-1);
  }
  if (fork() == 0) {
    close(p1[1]);
    close(p2[0]);
    int pid = getpid();
    write(p2[1], "ping", 4);
    char buff[128];
    read(p1[0], buff, 4);
    printf("%d:received %s\n", pid, buff);

    close(p1[0]);
    close(p2[1]);
    exit(0);
  } else {  // parent
    close(p1[0]);
    close(p2[1]);
    int pid = getpid();
    char pong[128];
    read(p2[0], pong, 4);

    printf("%d:received %s\n", pid, pong);
    write(p1[1], "pong", 4);
    close(p1[1]);
    close(p2[0]);
    int status;
    wait(&status);
  }

  return 0;
}
