include $(top_srcdir)/common.mk

bin_PROGRAMS=
lib_LIBRARIES=
lib_LTLIBRARIES=
SUBDIRS=

lib_LTLIBRARIES+=libahoCorasick.la
libahoCorasick_la_SOURCES=AhoCorasick.cpp
libahoCorasick_la_LIBADD=-lm -lpthread -lssplatform -lencoding
AM_CPPFLAGS+= -I../../include 

bin_PROGRAMS+=test
test_SOURCES=test.cpp
test_LDADD= -lpthread -lssplatform -lencoding -L./ -lahoCorasick

