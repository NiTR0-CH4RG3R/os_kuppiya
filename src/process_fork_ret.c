#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    printf( "Before calling fork()\n" );

    pid_t my_pid_before_fork = getpid();

    printf( "My PID is %u\n", my_pid_before_fork );

    pid_t returned_by_fork = fork();

    // pid_t my_pid_after_fork = getpid();

    // if ( my_pid_after_fork == my_pid_before_fork ) {
    //     printf( "This line is printed by the parent process. My PID is %u and the value returned by fork() is %u\n", my_pid_after_fork, returned_by_fork );
    // }
    // else {
    //     printf( "This line is printed by the child process. My PID is %u and the value returned by fork() is %u\n", my_pid_after_fork, returned_by_fork );
    // }

    if ( returned_by_fork == 0 ) {
        // this is the child process
    }
    else if ( returned_by_fork > 0 ) {
        // this is the parent process
    }
    else {
        // error
    }

    return 0;
}