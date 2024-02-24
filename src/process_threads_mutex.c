#include <stdio.h>
#include <pthread.h>


pthread_mutex_t mutex = {0};
unsigned int global_sum = 0;


void* thread_function( void* ) {
    printf( "[FROM ANOTHER THREAD] : Hello, World!\n" );

    unsigned int local_sum = 0;

    for ( int i = 50001; i <= 100000; i++ ) {
        local_sum += i;

    }

    pthread_mutex_lock( &mutex );
    global_sum += local_sum;
    pthread_mutex_unlock( &mutex );

    //global_sum += local_sum;
}

int main() {
    printf( "Hello, World!\n" );

    pthread_t thread = 0;

    pthread_mutex_init( &mutex, NULL );

    if ( pthread_create( &thread, NULL, thread_function, NULL ) != 0 ) {
        pthread_mutex_destroy( &mutex );
        return 1;
    };

    unsigned int local_sum = 0;

    for ( int i = 1; i <= 50000; i++ ) {
        local_sum += i;
    }


    pthread_mutex_lock( &mutex );
    global_sum += local_sum;
    pthread_mutex_unlock( &mutex );

    // global_sum += local_sum;

    pthread_join( thread, NULL );
    pthread_mutex_destroy( &mutex );

    printf( "Global Sum = %u\n", global_sum );

    return 0;
}