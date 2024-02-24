#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    int pipefd[2] = {0};

    if ( pipe( pipefd ) < 0 ) {
        printf( "[ERROR] : pipe() failed!\n" );
        return EXIT_FAILURE;
    }

    const char message[] = "Hello, World!";
    const size_t message_size = strlen( message );

    write( pipefd[1], message, message_size );

    sleep( 3 );

    // size_t recieved_message_size = (message_size + 1);
    // char* recieved_message = (char*)malloc( sizeof(char) * recieved_message_size );

    // read( pipefd[0], recieved_message, sizeof(char) * recieved_message_size );

    // recieved_message[recieved_message_size - 1] = '\0';

    // printf( "[RECIEVED_MESSAGE] : %s\n", recieved_message );

    // free( recieved_message );

    char buffer[512] = {0};
    read( pipefd[0], buffer, sizeof(buffer) );
    printf( "[RECIEVED_MESSAGE] : %s\n", buffer );

    return EXIT_SUCCESS;
}