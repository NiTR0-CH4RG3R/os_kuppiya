#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/sem.h>
#include <malloc.h>

typedef struct {
    int value;
    int state;
} shared_memory_t;

void V(int sem_id, short sem_no ) {
    struct sembuf semOperation[1];                  // Array of 'struct sembuf' used to define the operation to be done to the semaphore

    semOperation[0].sem_num = sem_no;              // Give the semaphore number
    semOperation[0].sem_op = 1;                     // Give any positive number, to indicate incremention
    semOperation[0].sem_flg = 0;                    // Give 0 flag. (see man page example)

    semop(sem_id, semOperation, 1);
}

void P(int sem_id, short sem_no ) {
    struct sembuf semOperation[1];                  // Array of 'struct sembuf' used to define the operation to be done to the semaphore

    semOperation[0].sem_num = sem_no;              // Give the semaphore number
    semOperation[0].sem_op = -1;                    // Give any negative number, to indicate decremention
    semOperation[0].sem_flg = 0;                    // Give 0 flag. (see man page example)

    semop(sem_id, semOperation, 1);  // Give the semaphore id, above struct array and the length of the above struct arra
}

int main() {
    int sem_id = semget( IPC_PRIVATE, 2, IPC_CREAT | 0600 ); // (1) create a 

    if ( sem_id == -1 ) {
        return EXIT_FAILURE;
    }

    semctl( sem_id, 0, SETVAL, 0 );
    semctl( sem_id, 1, SETVAL, 1 );

    shared_memory_t* shared_memory = (shared_memory_t*)mmap( NULL, sizeof( shared_memory_t ), PROT_EXEC | PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0 );

    if ( shared_memory == MAP_FAILED ) {
        return EXIT_FAILURE;
    }

    // int* shared_memory = ( int* ) malloc( sizeof( int ) );

    pid_t pid = fork();

    if ( pid < 0 ) {
        return EXIT_FAILURE;
    }

    if ( pid == 0 ) {
        // Child
        printf( "[CHILD_PROC] : %p\n", shared_memory );
        for ( int i = 0; i < 10; i++ ) {
            P( sem_id, 0 );
            printf( "[CHILD_PROC] : read %d from the shared memory\n", shared_memory->value );
            V( sem_id, 1 );
        }

    }
    else {
        // Parent
        printf( "[PARENT_PROC] : %p\n", shared_memory );

        shared_memory->state = 1;

        for ( int i = 0; i < 10; i++ ) {
            P( sem_id, 1 );
            shared_memory->state = 1;
            shared_memory->value = i + 5;
            printf( "[PARENT_PROC] : wrote %d to the shared memory\n", i + 5);
            shared_memory->state = 0;
            V( sem_id, 0 );
        }


        shared_memory->state = 2;

        wait(NULL);
    }

    munmap( shared_memory, sizeof( int ) );
    // free( shared_memory );
    return 0;
}