include $(top_srcdir)/common.mk

bin_PROGRAMS=
lib_LIBRARIES=
lib_LTLIBRARIES=
SUBDIRS=

lib_LTLIBRARIES+=libspeechPro.la
libspeechPro_la_SOURCES=readWav.cpp
libspeechPro_la_LIBADD=-lm -lpthread -lssplatform -lencoding  -L../Similarity/editDist -leditdist -L../segment -lSegment
AM_CPPFLAGS+= -I../include -I../

bin_PROGRAMS+=similarity
similarity_SOURCES=similarity.cpp
similarity_LDADD= -lpthread -lssplatform -lencoding -L./ -lspeechPro -L../Similarity/editDist -leditdist -L../segment -lSegment
AM_CPPFLAGS+= -I../include  -I../ 
