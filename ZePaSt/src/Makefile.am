AM_CPPFLAGS = -D__STDC_INT64__

#if USE_SUBMODULES
#SUBDIRS = ../glitter
#AM_CPPFLAGS += -I $(top_srcdir)/glitter/src
#
#SUBDIRS += ../iSqrt
#AM_CPPFLAGS += -I $(top_srcdir)/iSqrt/src
#endif

lib_LTLIBRARIES =
include_HEADERS =
bin_PROGRAMS    =

include_HEADERS += stat-common.h

include Makefile-LIBADD.inc

lib_LTLIBRARIES += libstat.la
libstat_la_LIBADD = $(LIBSTAT_LIBADD)
include_HEADERS += stat.h
#bin_PROGRAMS += stat-test

lib_LTLIBRARIES += libstat_off.la
libstat_off_la_LIBADD = $(LIBSTAT_OFF_LIBADD)
include_HEADERS += stat_off.h
#bin_PROGRAMS += stat_off-test

lib_LTLIBRARIES += libstat_off_diff.la
libstat_off_diff_la_LIBADD = $(LIBSTAT_OFF_DIFF_LIBADD)
include_HEADERS += stat_off_diff.h
bin_PROGRAMS += stat_off_diff-test
stat_off_diff_test_LDADD = libstat_off_diff.la $(LIBSTAT_OFF_LIBADD) libmean.la $(LIBMEAN_LIBADD) libvariance.la $(LIBVARIANCE_LIBADD)

# TODO libdstat (i.e., doubles as unigrams)
# TODO libdstat_ngram (i.e., able to represent RGB values and such)

# TODO libnstat (i.e., void * as unigram, size_t bytesz, use memcpy; see CAQ)

lib_LTLIBRARIES += libpstat.la
libpstat_la_LIBADD = $(LIBPSTAT_LIBADD)
include_HEADERS += pstat.h
#bin_PROGRAMS += pstat-test

lib_LTLIBRARIES += libpstat_off.la
libpstat_off_la_LIBADD = $(LIBPSTAT_OFF_LIBADD)
include_HEADERS += pstat_off.h
#bin_PROGRAMS += pstat_off-test

lib_LTLIBRARIES += libpstat_ngram.la
libpstat_ngram_la_LIBADD = $(LIBPSTAT_NGRAM_LIBADD)
include_HEADERS += pstat_ngram.h
#bin_PROGRAMS += pstat_ngram-test

# TODO libpstat_ngram_off.la
# i.e., differences of ngramgs at different offsets

lib_LTLIBRARIES += libpstat_mulvar.la
libpstat_mulvar_la_LIBADD = $(LIBPSTAT_MULVAR_LIBADD)
include_HEADERS += pstat_mulvar.h
#bin_PROGRAMS += pstat_mulvar-test

# TODO libpstat_mulvar_off.la
# i.e., multivariate analysis of differences of unigrams at different offsets

# TODO libpstat_mulvar_ngram.la
# i.e., multivariate analysis of ngrams

# TODO libpstat_mulvar_ngram_off.la
# i.e., multivariate analysis of differences of ngrams at different offsets

lib_LTLIBRARIES += libzepast.la
libzepast_la_LIBADD = $(LIBZEPAST_LIBADD)
include_HEADERS += zepast.h stats.h
bin_PROGRAMS += zepast-test
zepast_test_LDADD = libzepast.la $(LIBZEPAST_LIBADD) libmean.la $(LIBMEAN_LIBADD) libvariance.la $(LIBVARIANCE_LIBADD) libabsdev.la $(LIBABSDEV_LIBADD)

lib_LTLIBRARIES += libsum.la
libsum_la_LIBADD = $(LIBSTAT_LIBADD)
include_HEADERS += sum.h
bin_PROGRAMS += sum-test
sum_test_LDADD = libsum.la $(LIBSUM_LIBADD)

lib_LTLIBRARIES += libmean.la
libmean_la_LIBADD = $(LIBMEAN_LIBADD)
include_HEADERS += mean.h
bin_PROGRAMS += mean-test
mean_test_LDADD = libmean.la $(LIBMEAN_LIBADD)

lib_LTLIBRARIES += libvariance.la
libvariance_la_LIBADD = $(LIBVARIANCE_LIBADD)
include_HEADERS += variance.h
bin_PROGRAMS += variance-test
variance_test_LDADD = libvariance.la $(LIBVARIANCE_LIBADD) libmean.la $(LIBMEAN_LIBADD)

lib_LTLIBRARIES += libivariance.la
libivariance_la_LIBADD = $(LIBIVARIANCE_LIBADD)
include_HEADERS += ivariance.h
bin_PROGRAMS += ivariance-test
ivariance_test_LDADD = libivariance.la $(LIBIVARIANCE_LIBADD) libmean.la $(LIBMEAN_LIBADD)

lib_LTLIBRARIES += libabsdev.la
libabsdev_la_LIBADD = $(LIBABSDEV_LIBADD)
include_HEADERS += absdev.h
bin_PROGRAMS += absdev-test
# TODO libmedian.la
absdev_test_LDADD = libabsdev.la $(LIBABSDEV_LIBADD) libmean.la $(LIBMEAN_LIBADD)

# variance/stddev
# absdev/MAD

#stat_test_SOURCES = stat-test.c
#stat_test_LDADD = libzepast.la libstat.la libmean.la libvariance.la libabsdev.la -lm

# trololol
#dist_doc_DATA += src/Makefile.am
