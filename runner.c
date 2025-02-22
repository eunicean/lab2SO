#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
  pid_t pid = fork();

  if (pid == 0) {
    execl("./ipc", "ipc", "2", "a", NULL);
  } else {
    execl("./ipc", "ipc", "3", "b", NULL);
    
    usleep(1000);
    wait(NULL);
  }

  return 0;
}
