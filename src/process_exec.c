#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main( int argc, char* argv[] ) {

    printf( "Before running execl()\n" ); // This runs

    // char* const args[] = {
    //     "ls", "-l", "-a", NULL
    // };

    int returned_by_exec = execl( "/usr/bin/ls", "ls", NULL );

    printf( "After running execl()\nexecl() returned %d\n", returned_by_exec ); // This does not run if the execl() function succeeded!

    return 0;
}