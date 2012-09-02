PHP_ARG_ENABLE(threads, whether to enable Threads extension, [  --enable-threads   Enable threads extension])

if test "$PHP_THREADS" != "no"; then

    CFLAGS="$CFLAGS -pthread"    

    dnl Define the extension
    PHP_NEW_EXTENSION(threads, threads.c, $ext_shared, $CFLAGS)
fi
