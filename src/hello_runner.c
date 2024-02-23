#include <unistd.h>
#include <stdio.h>

int main() {
    printf( "Called before execl()\n" );

    int returned_by_exec = execl( "/home/buddhima/dev/os_kuppiya/bin/hello_world.exe", NULL );

    printf( "After running execl()\nexecl() returned %d\n", returned_by_exec ); // This does not run if the execl() function succeeded!


    return 0;
}