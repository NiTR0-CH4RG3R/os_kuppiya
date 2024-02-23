#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf( "Before calling fork()\n" );

    pid_t my_pid_before_fork = getpid();

    printf( "My PID is %u\n", my_pid_before_fork );


    // This will create 4 prcesses as the child from the first fork and the parent will both create child processes from the second fork
    pid_t returned_by_fork_1 = fork();
    
    if ( returned_by_fork_1 < 0 ) {
        return EXIT_FAILURE;
    }

    pid_t returned_by_fork_2 = fork();

    if ( returned_by_fork_2 < 0 ) {
        return EXIT_FAILURE;
    }

    // if ( returned_by_fork_1 == 0 && returned_by_fork_2 == 0 ) {
    //     // This is the child of the first child process
    // }
    // else if ( returned_by_fork_1 == 0 && returned_by_fork_2 > 0 ) {
    //     // This is the first child process of the parent
    // }
    // else if ( returned_by_fork_1 > 0 && returned_by_fork_2 == 0 ) {
    //     // This is the second child of the parent process
    // }
    // else {
    //     // This is the parent process
    // }

    if ( returned_by_fork_1 == 0 ) {
        // First child
        if ( returned_by_fork_2 == 0 ) {
            // Child of the first child
            sleep( 2 );
            printf( "[Child of the first child] : Slept for 2s\n" );
        }
        else {
            // First Child
            sleep( 1 );
            printf( "[First child] : Slept for 1s\n" );
            wait(NULL);
            printf( "[First child] : Waited for child to finish\n" );
        }
    }
    else {
        // Parent
        if ( returned_by_fork_2 == 0 ) {
            // Second child of the parent
            sleep( 3 );
            printf( "[Second child] : Slept for 3s\n" );
        }
        else {
            // Parent
            wait(NULL);
            wait(NULL);
            printf( "[Parent] : Waited for all the children and grand child to be terinated!\n" );
        }
    }


    // if ( returned_by_fork_1 == 0 ) {
    //     // this is the child process
    //     printf( "I'm the child process. My PID is %u\n", getpid() );
    //     sleep( 5 );
    //     printf( "Slept for 5 seconds\n" );
    // }
    // else {
    //     // this is the parent process
    //     int state_returned_by_wait = 0;
    //     pid_t returned_by_wait = wait( &state_returned_by_wait );
    //     printf( "Waited for child to wakeup!\n" );
    //     printf( "Value returned by the wait() function : %u\n", returned_by_wait );
    // }



    return 0;
}