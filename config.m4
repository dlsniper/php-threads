PHP_ARG_ENABLE(threads, whether to enable Threads extension, [  --enable-threads   Enable threads extension])

if test "$PHP_THREADS" != "no"; then

orig_LIBS="$LIBS"

    PHP_REQUIRE_CXX
    AC_LANG_CPLUSPLUS

    PHP_ADD_LIBRARY(stdc++, , THREADS_SHARED_LIBADD)
  
    export OLD_CPPFLAGS="$CPPFLAGS"
    export CPPFLAGS="$CPPFLAGS $INCLUDES -DHAVE_THREADS"

    AC_MSG_CHECKING(PHP version)
    AC_TRY_COMPILE([#include <php_version.h>], [
      #if PHP_VERSION_ID < 40000
      #error  this extension requires at least PHP version 5.3.16
      #endif
    ],
    [AC_MSG_RESULT(ok)],
    [AC_MSG_ERROR([need at least PHP 5.3.16])])

    export CPPFLAGS="$OLD_CPPFLAGS"

    dnl This will help sending the pthread flag to gcc
    orig_cflags=$CFLAGS
    CFLAGS="$CFLAGS -pthread"    
    
    dnl Define the extension
    PHP_NEW_EXTENSION(threads, php_threads.cpp, $ext_shared, $CFLAGS)
    
    PHP_SUBST(THREADS_SHARED_LIBADD)
fi
