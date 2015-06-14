AC_INIT(parea3,2.0)
AM_INIT_AUTOMAKE

LT_INIT
#AC_LANG_C
#AC_PROG_CC
AC_PROG_CC
AC_PROG_CXX
# libtool gives error: ../libtool: fork: retry: Resource temporarily unavailable
#AC_PROG_LIBTOOL
AC_PROG_RANLIB

#AC_PROG_YACC
#YACC='bison -d'
#AM_PROG_LEX

#prevents warning on cygwin
#LDFLAGS="$LDFLAGS -no-undefined"

#CFLAGS="$CFLAGS -ansi"

CFLAGS="$CFLAGS -O0"  #there are problems on Debian 6 64bit with -O2

AC_OUTPUT(Makefile mm3parea/Makefile rm3parea/Makefile pyscan3parea/Makefile pyindent3parea/Makefile)
