#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {

    int pipefd[2] = {0};

    if ( pipe( pipefd ) < 0 ) {
        printf( "[ERROR] : pipe() failed!\n" );
        return EXIT_FAILURE;
    }


    pid_t pid = fork();

    if ( pid < 0 ) {
        // fork() has failed!
        close( pipefd[0] );
        close( pipefd[1] );
        return EXIT_FAILURE;
    }

    if ( pid > 0 ) {
        // PARENT
        close( pipefd[0] );

        const char message1[] = "Message 01 from parent!";
        write( pipefd[1], message1, sizeof( message1 ) );
        printf( "[PARENT] : Wrote message %s\n", message1 );

        const char message2[] = "02 from parent!";
        write( pipefd[1], message2, sizeof( message2 ) );
        printf( "[PARENT] : Wrote message %s\n", message1 );

        wait(NULL);
    }
    else {
        // CHILD
        close( pipefd[1] );

        char buffer[512] = {0};

        read( pipefd[0], buffer, sizeof( buffer ) );
        printf( "[CHILD] : Message recieved : %s\n", buffer );

        // memset( buffer, 0, sizeof( buffer ));
        read( pipefd[0], buffer, sizeof( buffer ) );
        printf( "[CHILD] : Message recieved : %s\n", buffer );
    }

    return EXIT_SUCCESS;
}