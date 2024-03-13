#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>

/**
 * In this tutorial we will look into how to create a shared memory block for implementing IPC (Inter-Process Communication)
 * between the parent process and its child processes.
*/

int main() {

    // We will initialize a shared memory block using mmap() function which will return a void pointer to the newly allocated memory block.
    // For this instance we will create a memory block with the size of an int.
    // The second parameter determines the size of the block while third parameter sets the protections
    // See the man pages for full specification.
    int* shared_int = mmap( NULL, sizeof( int ), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0 );

    // The mmap function will MAP_FAILED if the function failed
    if ( shared_int == MAP_FAILED ) {
        printf( "[ERROR] : mmap() function failed!\n" );
        goto cleanup;
    }
 
    pid_t child = 0;

    if ( ( child = fork() ) < -1 ) {
        printf( "[ERROR] : fork() function failed!\n" );
        goto cleanup;
    }

    if ( child == 0 ) {
        // Child process

        // Read from the shared_int
        for ( size_t i = 0; i < 10; i++ ) {
            sleep( 1 );
            int value = *shared_int;
            printf( "[CHILD] : Read %d from the shared_int\n", value );
        }

    }
    else {
        // Parent process
        
        // Write to the shared_int
        for ( size_t i = 0; i < 10; i++ ) {
            *shared_int = (int)i + 5;
            printf( "[PARENT] : Wrote %d to the shared_int\n", (int)i + 5 );
            sleep( 1 );
        }
    }

cleanup:
    munmap( shared_int, sizeof( int ) );
    return 0;
}