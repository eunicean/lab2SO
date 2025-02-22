#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

#define SHM_NAME "/shared_memory_example"
#define SHM_SIZE 1024 // Tamaño en bytes

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <número> <carácter>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    char x = argv[2][0];

    int shm_fd;
    void *ptr;
    int first_instance = 0; // 1 si este proceso crea la memoria

    // Intentar abrir memoria compartida
    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd < 0) {
        if (errno == EEXIST) {
            printf("%s: Memoria compartida ya creada\n", argv[2]);
            shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
        } else {
            perror("Error en shm_open");
            exit(EXIT_FAILURE);
        }
    } else {
        first_instance = 1;
        printf("%s: Creó memoria compartida\n", argv[2]);
        ftruncate(shm_fd, SHM_SIZE); // Ajustar tamaño
    }

    // Mapear memoria compartida
    ptr = mmap(0, SHM_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("Error en mmap");
        exit(EXIT_FAILURE);
    }

    // Crear proceso hijo
    pid_t pid = fork();
    if (pid < 0) {
        perror("Error en fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Proceso hijo - Recibir datos y escribir en memoria compartida
        char *shm_ptr = (char *)ptr;
        for (int i = 0; i < SHM_SIZE; i++) {
            while (shm_ptr[i] == 0) {
                usleep(5000); // Esperar datos del padre
            }
            printf("%c", shm_ptr[i]);
        }
        printf("\n");
    } else {
        // Proceso padre - Enviar datos al hijo
        char *shm_ptr = (char *)ptr;
        for (int i = 0; i < SHM_SIZE; i++) {
            if (i % n == 0) {
                shm_ptr[i] = x; // Escribir en memoria compartida
            }
            usleep(1000); // Pequeño retraso
        }

        // Esperar a que el hijo termine
        wait(NULL);
    }

    // Liberar memoria compartida
    munmap(ptr, SHM_SIZE);
    close(shm_fd);
    if (first_instance) {
        shm_unlink(SHM_NAME);
    }

    return 0;
}
