AM_CPPFLAGS = -D__STDC_INT64__

lib_LTLIBRARIES =
include_HEADERS =
bin_PROGRAMS    =

lib_LTLIBRARIES += libparray.la
libparray_la_CPPFLAGS = $(GLITTER_CFLAGS) $(MMALLOC_CFLAGS) $(SWAP_CFLAGS)
libparray_la_LIBADD   = $(GLITTER_LIBS)   $(MMALLOC_LIBS)   $(SWAP_LIBS)
include_HEADERS += parray.h

#bin_PROGRAMS += parray-test
#parray_test_LDADD = libparray.la $(LIBPARRAY_LIBADD)

