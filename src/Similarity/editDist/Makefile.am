#include $(top_srcdir)/common.mk

bin_PROGRAMS=
lib_LTLIBRARIES=
AM_CPPFLAGS=

lib_LTLIBRARIES+=libeditdist.la
libeditdist_la_SOURCES=EditDist.cpp
libeditdist_la_LIBADD=-lm -lpthread -lencoding
AM_CPPFLAGS+=-DSS_DOCID_BITS=256 -I../../ -I../
libeditdist_la_CPPFLAGS=$(AM_CPPFLAGS)

bin_PROGRAMS+=editDist
editDist_SOURCES=test.cpp
editDist_LDADD= -lpthread -lssplatform -lencoding -leditdist -L../../segment -lSegment -ldicmap
AM_CPPFLAGS+= -I../ -I../../
editDist_CPPFLAGS=$(AM_CPPFLAGS)

bin_PROGRAMS+=editDist_word
editDist_word_SOURCES=test.word.cpp
editDist_word_LDADD= -lpthread -lssplatform -lencoding -leditdist -L../../segment -lSegment -lIQSegmentor -ldicmap -lwordSegment
AM_CPPFLAGS+= -I../ -I../../
editDist_word_CPPFLAGS=$(AM_CPPFLAGS)
