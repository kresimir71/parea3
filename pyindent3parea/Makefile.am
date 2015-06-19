
bin_PROGRAMS = pyindent3parea
pyindent3parea_SOURCES = decorate.cpp main.cpp
pyindent3parea_LDFLAGS = -L../rm3parea -L../mm3parea -L../pyscan3parea
pyindent3parea_LDADD =   -lpyscan3parea -lmm3parea -lrm3parea -lpcre
libpyscan3parea_la_CPPFLAGS=-I. -I.. -DNDEBUG

EXTRA_DIST = python.c x_rm1.lex x_rm1.y

info_TEXINFOS = pyindent3parea.texi

pyindent3parea.html: pyindent3parea.texi 
	makeinfo --html --no-split pyindent3parea.texi

