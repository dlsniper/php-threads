// include PHP API
#include <php.h>
#include <pthread.h>

// header file we'll create below
#include "php_threads.h"

//#include <boost/thread.hpp>

// define the function(s) we want to add
zend_function_entry threads_functions[] = {
  PHP_FE(threaduri, NULL)
  { NULL, NULL, NULL }
};

// "threads_functions" refers to the struct defined above
// we'll be filling in more of this later: you can use this to specify
// globals, php.ini info, startup and teardown functions, etc.
zend_module_entry threads_module_entry = {
  STANDARD_MODULE_HEADER,
  PHP_THREADS_EXTNAME,
  threads_functions,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  PHP_THREADS_VERSION,
  STANDARD_MODULE_PROPERTIES
};

// install module
ZEND_GET_MODULE(threads)

void *PrintHello(void *threadid)
{
   long tid;
   tid = (long)threadid;
   php_printf("Hello World! It's me, thread #%ld!\n", tid);
   pthread_exit(NULL);
}

// actual non-template code!
PHP_FUNCTION(threaduri) {
  
    php_printf("This is the MAIN FUNCTION pre threads\n");
/*  
    using namespace boost; 
    
    thread thread_1 = thread(task1);
    thread thread_2 = thread(task2);
    
    // do other stuff
    thread_2.join();
    thread_1.join();
*/

    pthread_t threads[NUM_THREADS];

    int rc;
    long t;
    for(t=0; t<NUM_THREADS; t++){
       php_printf("In main: creating thread %ld\n", t);
       rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
       if (rc){
          php_printf("ERROR; return code from pthread_create() is %d\n", rc);
          exit(-1);
       }
    }

    pthread_exit(NULL);

    // php_printf is PHP's version of printf, it's essentially "echo" from C
    php_printf("This is the MAIN FUNCTION post threads\n");
}
