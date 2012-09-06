#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

// Include PHP API and various other PHP functions
#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "zend_API.h"
#include "zend_exceptions.h"

// Include the threads support from C
#include <pthread.h>

// Include our header file
#include "php_threads.h"

/* If you declare any globals in php_threads.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(threads)
*/

/* True global resources - no need for thread safety here */
static int numberOfCpuCores;

/* {{{ threads_functions[]
 *
 * Every user visible function must have an entry in threads_functions[].
 */
const zend_function_entry threads_functions[] = {
    PHP_FE(runThreads, NULL)
    PHP_FE(getThreadsMaxCount, NULL)
    PHP_FE_END	/* Must be the last line in threads_functions[] */
};
/* }}} */

/* {{{ threads_module_entry
 */
zend_module_entry threads_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_THREADS_EXTNAME,
    threads_functions,
    PHP_MINIT(threads),
    PHP_MSHUTDOWN(threads),
    NULL,
    NULL,
    PHP_MINFO(threads),
#if ZEND_MODULE_API_NO >= 20010901
    PHP_THREADS_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_THREADS
ZEND_GET_MODULE(threads)
#endif

/* {{{ PHP_INI
 */
/*
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("threads.max_threads_count",      "4", PHP_INI_ALL, OnUpdateLong, global_value, zend_threads_globals, threads_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_threads_init_globals
 */
/*
static void php_threads_init_globals(zend_threads_globals *threads_globals)
{
    // Get the number of CPUs from the system to know how many threads we can handle
    numberOfCpuCores = sysconf(_SC_NPROCESSORS_ONLN);
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(threads)
{
    /*
    REGISTER_INI_ENTRIES();
    */

    // Get the number of CPUs from the system to know how many threads we can handle
    numberOfCpuCores = sysconf(_SC_NPROCESSORS_ONLN);

    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(threads)
{
    /*
    UNREGISTER_INI_ENTRIES();
    */

    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(threads) {
    char buf[5];

    php_info_print_table_start();

    php_info_print_table_row(2, "Threads support", "enabled");

    php_info_print_table_row(2, "Version", PHP_THREADS_VERSION);

    snprintf(buf, sizeof(buf), "%ld", numberOfCpuCores);
    php_info_print_table_row(2, "Maximum number of threads", buf);

    php_info_print_table_end();

    /*
    DISPLAY_INI_ENTRIES();
    */
}
/* }}} */

void *printHello(void *thFunc) {

    threadableFunction *thData;
    thData = (threadableFunction *) thFunc;

    long tid, tcnt;
    tid = ((long)thData->threadId) + 1;
    tcnt = ((long)thData->threadCount);

    php_printf("Hello World! It's me, ze random thread #%2d out of many many threads (%2d to be more accurate)!<br/>\n", tid, tcnt);


    if (zend_call_function(thData->fci, thData->fci_cache TSRMLS_CC) == SUCCESS && thData->fci->retval_ptr_ptr && *thData->fci->retval_ptr_ptr) {
        //COPY_PZVAL_TO_ZVAL(*return_value, *fci.retval_ptr_ptr);
    }

    pthread_exit(0);
}

/* {{{ proto string runThreads(int arg)
   Return a string that matches the return number from the threads */
PHP_FUNCTION(runThreads) {

    // Get the number of threads that the user wants to create
    long threadsNumber;

    zval *retval_ptr = NULL;
    zend_fcall_info fci;
    zend_fcall_info_cache fci_cache;
    threadableFunction *thFunc;

    // Parse the input parameters
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lf*", &threadsNumber, &fci, &fci_cache, &fci.params, &fci.param_count) == FAILURE) {
        RETURN_NULL();
    }

    // Assign the output pointer stuff yada yada
    fci.retval_ptr_ptr = &retval_ptr;

    // Validate that we can run that number of threads
    if (threadsNumber > numberOfCpuCores ||
        threadsNumber < 1
        ) {
        threadsNumber = numberOfCpuCores;
    }

    // Allocate the memory for the function we are about to run
    thFunc = (threadableFunction*)emalloc(sizeof(threadableFunction));
    memset(thFunc, 0, sizeof(threadableFunction));

    // Assign the thingies
    thFunc->threadCount = threadsNumber;
    thFunc->fci = &fci;
    thFunc->fci_cache = &fci_cache;

    // Define our threads array
    pthread_t threads[threadsNumber];
    int rc;
    long t;

    // Create the threads
    for(t=0; t<threadsNumber; t++){
        thFunc->threadId = t;
        rc = pthread_create(&threads[t], NULL, printHello, (void *)thFunc);

        // Check if we have ze error
        if (rc){
            // @TODO: Convert this to an exception
            php_printf("ERROR; return code from pthread_create() is %d<br/>\n", rc);
            exit(-1);
        }

        // And make them run so that we don't finish the function until we finished the threads
        pthread_join(threads[t], NULL);
    }

    // Free memory, I hope
    if (thFunc->fci->params) {
        efree(thFunc->fci->params);
    }

    // Free memory, I hope
    efree(thFunc);

    // Buh bye
    RETURN_NULL();
}
/* }}} */

/* {{{ proto string getThreadsMaxCount()
   Return a string that matches the return number from the threads */
PHP_FUNCTION(getThreadsMaxCount) {
    RETURN_LONG(numberOfCpuCores);
}
/* }}} */



/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
