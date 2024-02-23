#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf( "Before calling fork()\n" );

    pid_t my_pid_before_fork = getpid();

    printf( "My PID is %u\n", my_pid_before_fork );

    pid_t returned_by_fork = fork();

    if ( returned_by_fork < 0 ) {
        return EXIT_FAILURE;
    }

    if ( returned_by_fork == 0 ) {
        // this is the child process
        printf( "I'm the child process. My PID is %u\n", getpid() );
        sleep( 5 );
        printf( "Slept for 5 seconds\n" );
    }
    else {
        // this is the parent process
        int state_returned_by_wait = 0;
        pid_t returned_by_wait = wait( &state_returned_by_wait );
        printf( "Waited for child to wakeup!\n" );
        printf( "Value returned by the wait() function : %u\n", returned_by_wait );
    }



    return 0;
}