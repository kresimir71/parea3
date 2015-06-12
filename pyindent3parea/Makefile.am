
bin_PROGRAMS = parea3pyindent
parea3pyindent_SOURCES = decorate.cpp main.cpp
parea3pyindent_LDFLAGS = -L../rm3parea -L../mm3parea -L../pyscan3parea
parea3pyindent_LDADD =   -lpyscan3parea -lmm3parea -lrm3parea -lpcre
libpyscan3parea_la_CPPFLAGS=-I.. -I../mm3parea -I../rm3parea -DNDEBUG

EXTRA_DIST = python.c x_rm1.lex x_rm1.y

#-L/usr/local/lib 

#lex.yy_.c: x_rm1.lex
#	flex $(LFLAGS) -8 -Pyy_ x_rm1.lex
#x_rm1.tab.c x_rm1.tab.h: x_rm1.y
#	bison $(YFLAGS) -d x_rm1.y
