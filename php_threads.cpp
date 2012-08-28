// include PHP API
#include <php.h>

// header file we'll create below
#include "php_threads.h"

#define BOOST_DISABLE_ASSERTS 1

#include <boost/thread.hpp>

// define the function(s) we want to add
zend_function_entry threads_functions[] = {
  PHP_FE(thread, NULL)
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

#ifdef __cplusplus 
extern "C" {
// install module
ZEND_GET_MODULE(threads)
}
#endif

void task1() { 
    php_printf("This is the TASK 1 FUNCTION post threads\n");
}

void task2() { 
    php_printf("This is the TASK 2 FUNCTION post threads\n");
}



// actual non-template code!
PHP_FUNCTION(thread) {
  
    php_printf("This is the MAIN FUNCTION pre threads\n");
  
    using namespace boost; 
    
    thread thread_1 = thread(task1);
    thread thread_2 = thread(task2);
    
    // do other stuff
    thread_2.join();
    thread_1.join();

    // php_printf is PHP's version of printf, it's essentially "echo" from C
    php_printf("This is the MAIN FUNCTION post threads\n");
}
