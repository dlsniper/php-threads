#ifndef PHP_THREADS_H
#define PHP_THREADS_H

extern zend_module_entry threads_module_entry;
#define phpext_threads_ptr &threads_module_entry


#ifdef PHP_WIN32
#	define PHP_THREADS_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_THREADS_API __attribute__ ((visibility("default")))
#else
#	define PHP_THREADS_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#define PHP_THREADS_EXTNAME "threads"
#define PHP_THREADS_VERSION "0.2"

PHP_MINIT_FUNCTION(threads);
PHP_MSHUTDOWN_FUNCTION(threads);
PHP_RINIT_FUNCTION(threads);
PHP_RSHUTDOWN_FUNCTION(threads);
PHP_MINFO_FUNCTION(threads);

PHP_FUNCTION(runThreads);
PHP_FUNCTION(getThreadsMaxCount);

/*
ZEND_BEGIN_MODULE_GLOBALS(threads)
    int numberOfCpuCores;
ZEND_END_MODULE_GLOBALS(threads)
*/

#ifdef ZTS
#define THREADS_G(v) TSRMG(threads_globals_id, zend_threads_globals *, v)
#else
#define THREADS_G(v) (threads_globals.v)
#endif

#endif	/* PHP_THREADS_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
