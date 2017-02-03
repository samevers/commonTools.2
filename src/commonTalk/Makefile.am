include $(top_srcdir)/common.mk

bin_PROGRAMS=
lib_LIBRARIES=
#lib_LTLIBRARIES=
SUBDIRS=

lib_LTLIBRARIES=libcommonTalk.la
libcommonTalk_la_SOURCES=	commonTalk.cpp
libcommonTalk_la_LIBADD=	-lACE -lz -L../segment -lSegment -L../QueryMatch -lquerymatch
libcommonTalk_la_LDFLAGS=	-DHAVE_CXX_STDHEADERS -DLINUX -DACE_HAS_EVENT_POLL -D_FILE_OFFSET_BITS=64 -fPIC -ggdb `curl-config --cflags` 
AM_CPPFLAGS+=-I./ -L/usr/lib64


bin_PROGRAMS+=commonTalk
commonTalk_SOURCES=test.cpp
commonTalk_LDADD=-lpthread  -L../segment -lSegment -L../QueryMatch -lquerymatch -L./ -lcommonTalk 
AM_CPPFLAGS+= -I../include
commonTalk_CPPFLAGS=$(AM_CPPFLAGS)


