
lib_LTLIBRARIES = libpyscan3parea.la
lib_LIBRARIES = libpyscan3parea.a
#libpyscan3parea_la_CFLAGS = -O0  
libpyscan3parea_la_CPPFLAGS=-I../mm3parea -I../rm3parea -DNDEBUG -DRM2_BUILD_LIBRARY
libpyscan3parea_a_CPPFLAGS=$libpyscan3parea_la_CPPFLAGS
libpyscan3parea_la_SOURCES = debug.h goals.h inc.h main.c appl.h debug2.h inc.c main.h x_io1.h lex.yy_.c x_rm1.tab1.c
libpyscan3parea_a_SOURCES=$libpyscan3parea_la_SOURCES
#DD01_HOWTO(LINUX01_automake) otherincludedir
#http://stackoverflow.com/questions/5603902/placing-header-files-in-a-subdirectory-of-usr-include-with-automake
otherincludedir = $(includedir)/pyscan3parea
otherinclude_HEADERS = x_rm1.tab.h python.h

noinst_PROGRAMS = pyscan3parea_test
pyscan3parea_test_SOURCES = pythontest.cpp
pyscan3parea_test_LDFLAGS = -L../rm3parea -L../mm3parea 
pyscan3parea_test_LDADD =   -lpyscan3parea -lmm3parea -lrm3parea -lpcre

EXTRA_DIST = python.c x_rm1.lex x_rm1.y

#-L/usr/local/lib 

#lex.yy_.c: x_rm1.lex
#	flex $(LFLAGS) -8 -Pyy_ x_rm1.lex
#x_rm1.tab.c x_rm1.tab.h: x_rm1.y
#	bison $(YFLAGS) -d x_rm1.y
