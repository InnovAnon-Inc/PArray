#if HAVE_CONFIG_H
#include <config.h>
#endif

#define _POSIX_C_SOURCE 200112L
#define __STDC_VERSION__ 200112L

#define NDEBUG 1

#ifndef NDEBUG
#include <stdio.h>
#endif

#include <math.h>

#include <variance.h>

__attribute__ ((leaf, nonnull (1), nothrow))
void init_variance (void *restrict _dest) {
   variance_t *restrict dest = (variance_t *restrict) _dest;
   dest->sum = 0;
   /*if (nval >= 30) dest->df  = nval - 1;
   else            dest->df  = nval;*/
#ifndef NDEBUG
   printf ("dest->sum:%d\n", (int) (dest->sum)); fflush (stdout);
   printf ("dest->df:%d\n", (int) (dest->df)); fflush (stdout);
#endif
}

__attribute__ ((leaf, nonnull (1), nothrow))
void update_variance (void *restrict _dest, unigram_t val) {
   variance_t *restrict dest = (variance_t *restrict) _dest;
   double dev;
#ifndef NDEBUG
   printf ("dest->sum:%g\n", dest->sum); fflush (stdout);
   printf ("dest->val:%d\n", (int) val); fflush (stdout);
#endif
   TODO (check overflow X2)
   dev = dest->ct - val;
#ifndef NDEBUG
   printf ("dev:%g\n", dev); fflush (stdout);
#endif
   dev = dev * dev;
#ifndef NDEBUG
   printf ("dev ** 2:%g\n", dev); fflush (stdout);
#endif
   dest->sum += dev;
#ifndef NDEBUG
   printf ("dest->sum:%g\n", dest->sum); fflush (stdout);
#endif
}

/* if the ct were an integer,
 * then we could use int sqrt() here */
__attribute__ ((leaf, nonnull (1), nothrow))
void finish_variance (void *restrict _dest) {
   variance_t *restrict dest = (variance_t *restrict) _dest;
   dest->res = sqrt (dest->sum) / (double) (dest->df);
#ifndef NDEBUG
   printf ("dest->sum:%g\n", dest->sum); fflush (stdout);
   printf ("dest->res:%g\n", dest->res); fflush (stdout);
#endif
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void init_variance_stat (
   stat_t *restrict stat, variance_t *restrict variance) {
   stat->init   = init_variance;
   stat->update = update_variance;
   stat->finish = finish_variance;
   stat->stat   = variance;
}


__attribute__ ((nonnull (1, 2), nothrow))
void ez_variance (
   variance_t *restrict variance,
   unigram_t const vals[], size_t nval) {
   stat_t s;
   init_variance_stat (&s, variance);
   ez_stat (&s, vals, nval);
}

__attribute__ ((nonnull (3), nothrow, pure, warn_unused_result))
double ezr_variance (
   double ct, size_t df,
   unigram_t const vals[], size_t nval) {
   variance_t variance;
   variance.ct = ct;
   variance.df = df;
   ez_variance (&variance, vals, nval);
   return variance.res;
}

