include $(top_srcdir)/common.mk

bin_PROGRAMS=
AM_CPPFLAGS=
lib_LTLIBRARIES=

lib_LTLIBRARIES+=libkmeans.la
libkmeans_la_SOURCES=kmeans.cpp
libkmeans_la_LIBADD=-lm -lpthread
AM_CPPFLAGS+= -I../../include 


bin_PROGRAMS+=test
test_SOURCES= test.cpp
test_LDADD= -lz -lkmeans
test_LDFLAGS= -DHAVE_CXX_STDHEADERS -DLINUX -DACE_HAS_EVENT_POLL -D_FILE_OFFSET_BITS=64 -fPIC -ggdb
test_CPPFLAGS=$(AM_CPPFLAGS) -DSS_LOG_DEFAULT_MODULE=fea_gen -DSS_DOCID_BITS=256

