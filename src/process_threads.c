#include <stdio.h>
#include <pthread.h>

unsigned int global_sum = 0;

void* thread_function( void* ) {
    printf( "[FROM ANOTHER THREAD] : Hello, World!\n" );

    int local_sum = 0;

    for ( int i = 50001; i <= 100000; i++ ) {
        global_sum += i;
    }

    //global_sum += local_sum;
}

int main() {
    printf( "Hello, World!\n" );

    pthread_t thread = 0;

    if ( pthread_create( &thread, NULL, thread_function, NULL ) != 0 ) {
        return 1;
    };

    int local_sum = 0;

    for ( int i = 1; i <= 50000; i++ ) {
        global_sum += i;
    }

    // global_sum += local_sum;

    pthread_join( thread, NULL );

    printf( "Global Sum = %u\n", global_sum );

    return 0;
}