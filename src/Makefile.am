AM_CPPFLAGS = -D__STDC_INT64__

#if USE_SUBMODULES
#SUBDIRS = ../glitter
#AM_CPPFLAGS += -I $(top_srcdir)/glitter/src
#
#SUBDIRS += ../swap
#AM_CPPFLAGS += -I $(top_srcdir)/swap/src
#
#SUBDIRS += ../MultiMalloc
#AM_CPPFLAGS += -I $(top_srcdir)/MultiMalloc/src
#endif

lib_LTLIBRARIES =
include_HEADERS =
bin_PROGRAMS    =

include Makefile-LIBADD.inc

lib_LTLIBRARIES += libparray.la
libparray_la_LIBADD = $(LIBPARRAY_LIBADD)
include_HEADERS += parray.h
#bin_PROGRAMS += parray-test
#parray_test_LDADD = libparray.la $(LIBPARRAY_LIBADD)
