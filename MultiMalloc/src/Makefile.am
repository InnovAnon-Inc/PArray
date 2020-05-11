AM_CPPFLAGS = -D__STDC_INT64__

#if USE_SUBMODULES
#SUBDIRS = ../glitter
#AM_CPPFLAGS += -I $(top_srcdir)/glitter/src
##AM_CPPFLAGS += -I $(top_srcdir)/ZePaSt/src
#endif

lib_LTLIBRARIES =
include_HEADERS =
bin_PROGRAMS    =

include Makefile-LIBADD.inc

lib_LTLIBRARIES += libmmalloc.la
libmmalloc_la_LIBADD = $(LIBMMALLOC_LIBADD)
include_HEADERS += mmalloc.h
#bin_PROGRAMS += mmalloc-test
#mmalloc_test_LDADD = libmmalloc.la -lsum
