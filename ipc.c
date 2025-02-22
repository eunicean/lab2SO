#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#define SHM_SIZE 1024  

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Uso: ./ipc <n> <x>\n");
        return 1;
    }

    int n = atoi(argv[1]);
    char x = argv[2][0];

    const char* shm_name = "/sahred_memory";
    int shm_fd = shm_open(shm_name, O_CREAT | O_EXCL | O_RDWR, 0666);

    if (shm_fd < 0) {
        if (errno == EEXIST) {
            printf("%c: Memoria compartida ya existe.\n", x);
            shm_fd = shm_open(shm_name, O_RDWR, 0666);
            if (shm_fd < 0) return 1;
        } else {
            printf("%c: Error en memoria compartida.\n", x);
            return 1;
        }
    } else {
        printf("%c: Memoria compartida creada. FD: %d\n", x, shm_fd);
    }

    if (ftruncate(shm_fd, SHM_SIZE) < 0) {
        printf("%c: Error configurando tamaño de memoria.\n", x);
        return 1;
    }

    char* ptr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) return 1;

    printf("%c: Memoria mapeada en %p\n", x, (void*)ptr);

    
    int pipefd[2];
    if (pipe(pipefd) < 0) return 1;

    pid_t pid = fork();
    if (pid < 0) return 1;

    if (pid == 0) {  
        close(pipefd[1]);  
        char buffer;
        int index = 0;
        while (read(pipefd[0], &buffer, 1) > 0) {
            ptr[index++] = buffer;
        }
        close(pipefd[0]);  
        exit(0);
    } else {  
        close(pipefd[0]);
        printf("%c: Soy el padre PID: %d\n", x, getpid());

        for (int i = 0; i < SHM_SIZE; i++) {
            if (i % n == 0) write(pipefd[1], &x, 1);
        }

        close(pipefd[1]);
        wait(NULL);

        printf("%c: Memoria compartida -> %s\n", x, ptr);

        munmap(ptr, SHM_SIZE);
        close(shm_fd);
        shm_unlink(shm_name);
    }

    return 0;
}
