include $(top_srcdir)/common.mk

bin_PROGRAMS=
lib_LIBRARIES=
lib_LTLIBRARIES=
SUBDIRS=

lib_LTLIBRARIES+=libindex_da.la
libindex_da_la_SOURCES=Index_da.cpp darts-clone.cpp
libindex_da_la_LIBADD=-lm -lpthread -lssplatform -lencoding -ldicmap -lCoreSegmentor -L../../segment -lSegment
AM_CPPFLAGS+= -I../../include 

bin_PROGRAMS+=index_da_make_index
index_da_make_index_SOURCES=index_da_make_index.cpp
index_da_make_index_LDADD= -lpthread -lssplatform -lencoding -lindex_da -L../../segment -lSegment

bin_PROGRAMS+=preProcessCor_bin
preProcessCor_bin_SOURCES=FormatDlgCor.cpp
preProcessCor_bin_LDADD= -lpthread -lssplatform -lencoding -L../../segment -lSegment

lib_LTLIBRARIES+=libContainSearch.la
libContainSearch_la_SOURCES=ContainSearch.cpp
libContainSearch_la_LIBADD=-lm -lpthread -lssplatform -lencoding -ldicmap -lCoreSegmentor -L../../segment -lSegment

bin_PROGRAMS+=containSearchTest
containSearchTest_SOURCES=ContainSearchTest.cpp
containSearchTest_LDADD= -lpthread -lssplatform -lencoding -L../../segment -lSegment -lContainSearch

lib_LTLIBRARIES+=libCommonPrefixSearch.la
libCommonPrefixSearch_la_SOURCES=CommonPrefixSearch.cpp
libCommonPrefixSearch_la_LIBADD=-lm -lpthread -lssplatform -lencoding -ldicmap -lCoreSegmentor -L../../segment -lSegment

bin_PROGRAMS+=commonPrefixSearchTest
commonPrefixSearchTest_SOURCES=CommonPrefixSearchTest.cpp
commonPrefixSearchTest_LDADD= -lpthread -lssplatform -lencoding -L../../segment -lSegment -lCommonPrefixSearch

