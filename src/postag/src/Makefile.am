include $(top_srcdir)/common.mk

lib_LTLIBRARIES=

SUBDIRS=@PACKAGE_DEPENDENCIES@ 
lib_LTLIBRARIES+=libpostag.la
libpostag_la_SOURCES=*.cpp *.hpp
libpostag_la_LIBADD=-lACE -lssplatform -lencoding 
libpostag_la_LDFLAGS= -no-install -DHAVE_CXX_STDHEADERS -DLINUX -DACE_HAS_EVENT_POLL -D_FILE_OFFSET_BITS=64 -fPIC -ggdb
AM_CPPFLAGS+=-L/usr/lib64  -I$(UTILS_ROOT)  -I$(SSENCODING_ROOT) -I.. -I. 
libpostag_la_CPPFLAGS=$(AM_CPPFLAGS) -DSS_DOCID_BITS=256
