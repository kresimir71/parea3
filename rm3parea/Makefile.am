
lib_LTLIBRARIES = librm3parea.la
lib_LIBRARIES = librm3parea.a
librm3parea_la_SOURCES = aa.c col.h Makefile.am rbt.h stack.c aa.h list.c misc.c rbt_shortcuts.h stack.h col.c list.h misc.h rbt.c rm1.h
librm3parea_a_SOURCES = $librm3parea_la_SOURCES

#DD01_HOWTO(LINUX01_autoconf) CPPFLAGS
#also AC_CPPFLAGS
librm3parea_la_CPPFLAGS=-I../mm3parea
librm3parea_a_CPPFLAGS=$librm3parea_la_CPPFLAGS

#librm3parea_la_CFLAGS = -O0  

otherincludedir = $(includedir)/rm3parea
otherinclude_HEADERS = stack.h rm1.h rbt.h rbt_shortcuts.h misc.h list.h col.h aa.h
