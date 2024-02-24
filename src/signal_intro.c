#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void signal_int_handler(int signo) {
    if ( signal( SIGINT, signal_int_handler ) == SIG_ERR ) printf( "[ERROR] : Couldn't register signal handler!\n" );
    printf( "[INFO] : Caught the signal %d\n", signo );
}

void signal_quit_handler(int signo) {
    printf( "[INFO] : SIGQUIT Recieved!" );
    exit(EXIT_SUCCESS);
}

int main() {

    if ( signal( SIGINT, signal_int_handler ) == SIG_ERR ) {
        printf( "[ERROR] : Couldn't register signal handler!\n" );
        return EXIT_FAILURE;
    }
    else {
        printf( "[INFO] : Succesfully registered the signal handler!\n" );
    }

    if ( signal( SIGQUIT, signal_quit_handler ) == SIG_ERR ) {
        printf( "[ERROR] : Couldn't register signal handler!\n" );
        return EXIT_FAILURE;
    }
    else {
        printf( "[INFO] : Succesfully registered the signal handler!\n" );
    }

    while( 1 ) {
        // Do nothing
    }

    return 0;
}