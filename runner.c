#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
  pid_t pid = fork();

  if (pid == 0) {
    execl("./ipc", "ipc", "5", "a", NULL);
    perror("Error en execl");
  } else {
    execl("./ipc", "ipc", "5", "b", NULL);
    perror("Error en execl");
  }

  return 0;
}
