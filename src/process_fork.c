#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    printf( "Before calling fork()\n" );

    pid_t pid = fork();

    printf( "After calling fork() - %lu\n", getpid() );

    return 0;
}