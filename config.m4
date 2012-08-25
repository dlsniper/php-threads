PHP_ARG_ENABLE(threads, whether to enable Threads extension, [  --enable-threads   Enable threads extension])

if test "$PHP_THREADS" != "no"; then
    dnl Define the extension
    PHP_NEW_EXTENSION(threads, php_threads.c, $ext_shared)

    dnl OS X compatibility 
    case $build_os in
        darwin1*.*.*)
        AC_MSG_CHECKING([whether to compile for recent osx architectures])
        CFLAGS="$CFLAGS -arch i386 -arch x86_64 -mmacosx-version-min=10.5"
        AC_MSG_RESULT([yes])
        ;;
    darwin*)
        AC_MSG_CHECKING([whether to compile for every osx architecture ever])
        CFLAGS="$CFLAGS -arch i386 -arch x86_64 -arch ppc -arch ppc64"
        AC_MSG_RESULT([yes])
        ;;
    esac
fi
