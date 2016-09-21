include $(top_srcdir)/common.mk

bin_PROGRAMS=
#AM_CPPFLAGS=


bin_PROGRAMS+=main.gram
main_gram_SOURCES= main.gram.cpp \
				Index_da.cpp word_gram.cpp general.cpp 
main_gram_LDADD= -lz -lencoding -lssplatform -lencoding -ldicmap -lCoreSegmentor
main_gram_LDFLAGS= -DHAVE_CXX_STDHEADERS -DLINUX -DACE_HAS_EVENT_POLL -D_FILE_OFFSET_BITS=64 -fPIC -ggdb
AM_CPPFLAGS+=-L/usr/lib64 -I$(UTILS_ROOT) -I$(SSENCODING_ROOT) -I../include -I../../word_segmentor
main_gram_CPPFLAGS=$(AM_CPPFLAGS) -DSS_LOG_DEFAULT_MODULE=fea_gen -DSS_DOCID_BITS=256

bin_PROGRAMS+=main.word
main_word_SOURCES= main.word.cpp \
				general.cpp word_distribute.cpp
main_word_LDADD= -lz -lencoding 
main_word_LDFLAGS= -DHAVE_CXX_STDHEADERS -DLINUX -DACE_HAS_EVENT_POLL -D_FILE_OFFSET_BITS=64 -fPIC -ggdb
AM_CPPFLAGS+=-L/usr/lib64 -I$(UTILS_ROOT) -I$(SSENCODING_ROOT) -I../include
main_word_CPPFLAGS=$(AM_CPPFLAGS) -DSS_LOG_DEFAULT_MODULE=fea_gen -DSS_DOCID_BITS=256

bin_PROGRAMS+=main
main_SOURCES= main.cpp \
				general.cpp naive_bayes.cpp
main_LDADD= -lz -lencoding 
main_LDFLAGS= -DHAVE_CXX_STDHEADERS -DLINUX -DACE_HAS_EVENT_POLL -D_FILE_OFFSET_BITS=64 -fPIC -ggdb
AM_CPPFLAGS+=-L/usr/lib64 -I$(UTILS_ROOT) -I$(SSENCODING_ROOT) -I../include
main_CPPFLAGS=$(AM_CPPFLAGS) -DSS_LOG_DEFAULT_MODULE=fea_gen -DSS_DOCID_BITS=256
