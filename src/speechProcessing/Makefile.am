include $(top_srcdir)/common.mk

bin_PROGRAMS=
lib_LIBRARIES=
lib_LTLIBRARIES=
SUBDIRS=

lib_LTLIBRARIES+=libspeechPro.la
libspeechPro_la_SOURCES=readWav.cpp headDTW.cpp 
libspeechPro_la_LIBADD=-lm -lpthread -lssplatform -lencoding  -L../Similarity/editDist -leditdist -L../segment -lSegment -L../include/opencore-amr/amrwb -lopencore-amrwb -L../include/opencore-amr/amrnb -lopencore-amrnb
AM_CPPFLAGS+= -I../include -I../

lib_LTLIBRARIES+=libsimilarity.la
libsimilarity_la_SOURCES=similarity.cpp wav.cpp decodeAmr.cpp
libsimilarity_la_LIBADD= -lpthread -lssplatform -lencoding -L./ -lspeechPro -L../Similarity/editDist -leditdist -L../segment -lSegment -L../include/opencore-amr/amrnb -lopencore-amrnb -L../include/opencore-amr/amrwb -lopencore-amrwb  -L../mfccDtw -lmfccDtw
AM_CPPFLAGS+= -I../include  -I../ 

#bin_PROGRAMS+=similarity
#similarity_SOURCES=testAmr.cpp
##similarity_SOURCES=similarity.cpp wav.cpp decodeAmr.cpp
#similarity_LDADD= -lpthread -lssplatform -lencoding -L./ -lsimilarity -lspeechPro -L../Similarity/editDist -leditdist -L../segment -lSegment -L../include/opencore-amr/amrnb -lopencore-amrnb -L../include/opencore-amr/amrwb -lopencore-amrwb 
#AM_CPPFLAGS+= -I../include  -I../ 
#
#bin_PROGRAMS+=readAMR2WAV
#readAMR2WAV_SOURCES=readAMR2WAV.cpp
#readAMR2WAV_LDADD= -lpthread -lssplatform -lencoding -L./ -lsimilarity -lspeechPro -L../Similarity/editDist -leditdist -L../segment -lSegment -L../include/opencore-amr/amrnb -lopencore-amrnb -L../include/opencore-amr/amrwb -lopencore-amrwb 
#AM_CPPFLAGS+= -I../include  -I../ 
#
#
#bin_PROGRAMS+=generateShort
#generateShort_SOURCES=generateShort.cpp
#generateShort_LDADD= -lpthread -lssplatform -lencoding -L./ -lspeechPro -L../Similarity/editDist -leditdist -L../segment -lSegment
#AM_CPPFLAGS+= -I../include  -I../ 
