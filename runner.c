#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Error en fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Proceso hijo - Ejecutar ipc con "A"
        execl("./ipc", "ipc", "5", "A", NULL);
        perror("Error en execl");
    } else {
        // Proceso padre - Ejecutar ipc con "B"
        execl("./ipc", "ipc", "5", "B", NULL);
        perror("Error en execl");
    }

    return 0;
}
