AM_CPPFLAGS = -D__STDC_INT64__

#if USE_SUBMODULES
#SUBDIRS = ../glitter
#AM_CPPFLAGS += -I $(top_srcdir)/glitter/src
#endif

lib_LTLIBRARIES =
include_HEADERS =
bin_PROGRAMS    =

include Makefile-LIBADD.inc

lib_LTLIBRARIES += libswap.la
libswap_la_LIBADD = $(LIBSWAP_LIBADD)
include_HEADERS += swap.h
#bin_PROGRAMS += swap-test
#swap_test_LDADD = libswap.la
