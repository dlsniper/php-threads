PHP_ARG_ENABLE(threads, whether to enable Threads extension, [  --enable-threads   Enable threads extension])

if test "$PHP_THREADS" != "no"; then

orig_LIBS="$LIBS"

    PHP_REQUIRE_CXX
    AC_LANG_CPLUSPLUS

    PHP_ADD_LIBRARY(stdc++,,HELLO_SHARED_LIBADD)

    dnl This will help sending the pthread flag to gcc
    orig_cflags=$CFLAGS
    CFLAGS="$CFLAGS -pthread"    
    
    dnl Define the extension
    PHP_NEW_EXTENSION(threads, php_threads.cpp, $ext_shared, $CFLAGS)
    
    PHP_SUBST(THREADS_LIBRARY_ADD)
fi
