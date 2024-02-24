#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

void child_signal_sigquit_handler( int sig ) {
    printf( "[INFO] : Child process caught the SIGQUIT\n" );
    printf( "[INFO] : Waiting for 5 seconds...\n" );
    sleep( 5 );
    exit( EXIT_SUCCESS );
}

int main() {
    pid_t pid = fork();

    if ( pid < 0 ) {
        // ERROR
        return EXIT_FAILURE;
    }

    if ( pid == 0 ) {
        // CHILD PROCESS
        if ( signal( SIGQUIT, child_signal_sigquit_handler ) == SIG_ERR ) return EXIT_FAILURE;

        while( 1 ) {

        }
    }
    else {
        // PARENT PROCESS
        sleep( 5 );
        kill( pid, SIGQUIT );
        printf( "[PARENT] : Waiting for child to finish...\n" );
        wait( NULL );
        printf( "[PARENT] : Child successfully returned!\n" );

    }

    return 0;
}