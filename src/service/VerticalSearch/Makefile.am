include $(top_srcdir)/common.mk

bin_PROGRAMS=
lib_LIBRARIES=
lib_LTLIBRARIES=
SUBDIRS=

lib_LTLIBRARIES+=libVerticalDA.la
libVerticalDA_la_SOURCES=VerticalDA.cpp
libVerticalDA_la_LIBADD=-lpthread -lssplatform -lencoding -L../../index/inv_index/ -ldoc_index -L../../index/index_da -lindex_da -lnormalize -L../../da_search -lda_search 

AM_CPPFLAGS+=-DSS_DOCID_BITS=256 -I../../include -I../../index/index_da/ -I../../index/inv_index -I../../segment -I../../da_search -I../../include/common  -I../../
libVerticalDA_la_CPPFLAGS=$(AM_CPPFLAGS) -DSS_DOCID_BITS=256

lib_LTLIBRARIES+=libVerticalDOC.la
libVerticalDOC_la_SOURCES=VerticalDOC.cpp
libVerticalDOC_la_LIBADD=-lpthread -lssplatform -lencoding -L../../index/inv_index/ -ldoc_index -L../../index/index_da -lindex_da -L../../doc_search -ldoc_search -lnormalize -L../../da_search -lda_search  -L../../Similarity/editDist/ -leditdist

AM_CPPFLAGS+=-DSS_DOCID_BITS=256 -I../../include -I../../index/index_da/ -I../../index/inv_index -I../../segment -I../../da_search -I../../doc_search -I../../include/common  -I../../
libVerticalDOC_la_CPPFLAGS=$(AM_CPPFLAGS) -DSS_DOCID_BITS=256


##
bin_PROGRAMS+=music_run
music_run_SOURCES=music.cpp
music_run_LDADD= -lssplatform -lencoding -lVerticalDA -lVerticalDOC -L../../index/index_da -lindex_da -lnormalize -L../../da_search -lda_search 

music_run_LDFLAGS=-DHAVE_CXX_STDHEADERS -DLINUX -DACE_HAS_EVENT_POLL -D_FILE_OFFSET_BITS=64 -fPIC -ggdb

AM_CPPFLAGS+=-DSS_DOCID_BITS=256 -I../../include -I../../index/index_da/ -I../../segment -I../../da_search -I../../include/common -I../../


#AM_CPPFLAGS+=-I../../sys

