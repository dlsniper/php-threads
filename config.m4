PHP_ARG_ENABLE(threads, whether to enable Threads extension, [  --enable-threads   Enable threads extension])

if test "$PHP_THREADS" != "no"; then

orig_LIBS="$LIBS"

    dnl PHP_REQUIRE_CXX()
    dnl AC_LANG_CPLUSPLUS

    dnl PHP_ADD_LIBRARY(stdc++, , THREADS_SHARED_LIBADD)
  
    dnl export OLD_CPPFLAGS="$CPPFLAGS"
    dnl export CPPFLAGS="$CPPFLAGS $INCLUDES -DHAVE_THREADS"

    dnl AC_MSG_CHECKING(PHP version)
    dnl AC_TRY_COMPILE([#include <php_version.h>], [
    dnl   #if PHP_VERSION_ID < 40000
    dnl   #error  this extension requires at least PHP version 5.3.4
    dnl   #endif
    dnl ],
    dnl [AC_MSG_RESULT(ok)],
    dnl [AC_MSG_ERROR([need at least PHP 5.3.4])])

    dnl export CPPFLAGS="$OLD_CPPFLAGS"

    dnl This will help sending the pthread flag to gcc
    dnl orig_cflags=$CFLAGS
    CFLAGS="$CFLAGS -pthread"    
    
    dnl Define the extension
    PHP_NEW_EXTENSION(threads, php_threads.c, $ext_shared, $CFLAGS)
    
    PHP_SUBST(THREADS_SHARED_LIBADD)
fi
