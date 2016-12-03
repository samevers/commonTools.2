include $(top_srcdir)/common.mk

bin_PROGRAMS=httpserver
httpserver_SOURCES=main.cpp http_server.cpp task_base.cpp configuration.cpp HttpResponse.cpp HttpHandler.cpp 
httpserver_LDADD=-lpthread -lssplatform  -L"../locate_getresult" -llocateresult -L"../speechProcessing/" -lspeechPro  -L"../speechProcessing/" -lsimilarity -L../Similarity/editDist -leditdist -L../segment -lSegment -L"../include/opencore-amr/amrnb" -lopencore-amrnb -L"../include/opencore-amr/amrwb" -lopencore-amrwb  -L"../jsoncpp" -ljsoncpp
AM_CPPFLAGS+=-DSS_DOCID_BITS=256
AM_CPPFLAGS+=-I../sys 
