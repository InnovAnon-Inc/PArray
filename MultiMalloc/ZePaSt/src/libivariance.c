#if HAVE_CONFIG_H
#include <config.h>
#endif

#define _POSIX_C_SOURCE 200112L
#define __STDC_VERSION__ 200112L

#define NDEBUG 1

#ifndef NDEBUG
#include <stdio.h>
#endif

#include <isqrt.h>
#include <ivariance.h>

__attribute__ ((leaf, nonnull (1), nothrow))
void init_ivariance (void *restrict _dest) {
   ivariance_t *restrict dest = (ivariance_t *restrict) _dest;
   dest->sum = 0;
#ifndef NDEBUG
   printf ("dest->sum:%d\n", (int) (dest->sum)); fflush (stdout);
   printf ("dest->df:%d\n", (int) (dest->df)); fflush (stdout);
#endif
}

__attribute__ ((leaf, nonnull (1), nothrow))
void update_ivariance (void *restrict _dest, unigram_t val) {
   ivariance_t *restrict dest = (ivariance_t *restrict) _dest;
   ssize_t dev;
#ifndef NDEBUG
   printf ("dest->sum:%d\n", (int) (dest->sum)); fflush (stdout);
   printf ("dest->val:%d\n", (int) val); fflush (stdout);
#endif
   TODO (check overflow X2)
   dev = dest->ct - val;
#ifndef NDEBUG
   printf ("dev:%d\n", (int) dev); fflush (stdout);
#endif
   dev = dev * dev;
#ifndef NDEBUG
   printf ("dev ** 2:%d\n", (int) dev); fflush (stdout);
#endif
   dest->sum += (size_t) dev;
#ifndef NDEBUG
   printf ("dest->sum:%d\n", (int) (dest->sum)); fflush (stdout);
#endif
}

/* if the ct were an integer,
 * then we could use int sqrt() here */
__attribute__ ((leaf, nonnull (1), nothrow))
void finish_ivariance (void *restrict _dest) {
   ivariance_t *restrict dest = (ivariance_t *restrict) _dest;
   size_t sq = isqrt_size_t ((size_t) (dest->sum));
   TODO (check whether sum is negative)
   dest->res = (double) sq / (double) (dest->df);
#ifndef NDEBUG
   printf ("dest->sum:%d\n", (int) (dest->sum)); fflush (stdout);
   printf ("dest->res:%g\n", dest->res); fflush (stdout);
#endif
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void init_ivariance_stat (
   stat_t *restrict stat, ivariance_t *restrict ivariance) {
   stat->init   = init_ivariance;
   stat->update = update_ivariance;
   stat->finish = finish_ivariance;
   stat->stat   = ivariance;
}

__attribute__ ((nonnull (1, 2), nothrow))
void ez_ivariance (
   ivariance_t *restrict ivariance,
   unigram_t const vals[], size_t nval) {
   stat_t s;
   init_ivariance_stat (&s, ivariance);
   ez_stat (&s, vals, nval);
}

__attribute__ ((nonnull (3), nothrow, pure, warn_unused_result))
double ezr_ivariance (
   unigram_t ct, size_t df,
   unigram_t const vals[], size_t nval) {
   ivariance_t ivariance;
   ivariance.ct = ct;
   ivariance.df = df;
   ez_ivariance (&ivariance, vals, nval);
   return ivariance.res;
}
