include $(top_srcdir)/common.mk

bin_PROGRAMS=
lib_LIBRARIES=
#lib_LTLIBRARIES=
SUBDIRS=

lib_LTLIBRARIES=libwordSegment.la
libwordSegment_la_SOURCES=	wordSegment.cpp WordSegmentor.cpp GraphSegmentor.cpp
libwordSegment_la_LIBADD=	-lACE -lencoding -lssplatform -ldicmap -lCoreSegmentor -lIQSegmentor -lz 
libwordSegment_la_LDFLAGS=	-DHAVE_CXX_STDHEADERS -DLINUX -DACE_HAS_EVENT_POLL -D_FILE_OFFSET_BITS=64 -fPIC -ggdb `curl-config --cflags` 
AM_CPPFLAGS+=-I./ -L/usr/lib64


bin_PROGRAMS+=wordSegment
wordSegment_SOURCES=test2.cpp
wordSegment_LDADD=-lpthread -L../index/index_da -lindex_da -L./ -lwordSegment
AM_CPPFLAGS+= -I../index/index_da -I../include -I../index/inv_index
wordSegment_CPPFLAGS=$(AM_CPPFLAGS)



lib_LTLIBRARIES+=libSegment.la
libSegment_la_SOURCES=Segment.cpp WordSegmentor.cpp GraphSegmentor.cpp
libSegment_la_LIBADD=-lm -lpthread -lssplatform -lencoding -ldicmap -lCoreSegmentor -lIQSegmentor
AM_CPPFLAGS+= -I../include

bin_PROGRAMS+=segment
segment_SOURCES=main.cpp
segment_LDADD=-lpthread -L../index/index_da -lindex_da -L./ -lSegment
AM_CPPFLAGS+= -I../index/index_da -I../include -I../index/inv_index
segment_CPPFLAGS=$(AM_CPPFLAGS)


