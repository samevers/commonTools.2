include $(top_srcdir)/common.mk

bin_PROGRAMS=
lib_LIBRARIES=
#lib_LTLIBRARIES=
SUBDIRS=

lib_LTLIBRARIES=libsug.la
libsug_la_SOURCES=	sug.cpp 
libsug_la_LIBADD=	-lACE -lencoding -lssplatform -ldicmap -lCoreSegmentor -lIQSegmentor -lz -L../index/index_da/ -lindex_da -lencoding -L../segment -lSegment
libsug_la_LDFLAGS=	-DHAVE_CXX_STDHEADERS -DLINUX -DACE_HAS_EVENT_POLL -D_FILE_OFFSET_BITS=64 -fPIC -ggdb `curl-config --cflags` 
AM_CPPFLAGS+=-I./ -L/usr/lib64 -I../include -I../index/index_da/


bin_PROGRAMS+=sug
sug_SOURCES=test.cpp
sug_LDADD=-lpthread -L../index/index_da -lindex_da -L./ -lsug -L../segment -lSegment  -lencoding -lssplatform -ldicmap -lCoreSegmentor -lIQSegmentor
AM_CPPFLAGS+= -I../index/index_da -I../include -I../index/inv_index
sug_CPPFLAGS=$(AM_CPPFLAGS)


