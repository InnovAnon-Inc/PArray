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

#include <absdev.h>

__attribute__ ((leaf, nonnull (1), nothrow))
void init_absdev (void *restrict _dest) {
   absdev_t *restrict dest = (absdev_t *restrict) _dest;
   dest->sum = 0;
#ifndef NDEBUG
   printf ("dest->sum:%d\n", (int) (dest->sum)); fflush (stdout);
#endif
}

/* if the ct were an integer,
 * then we could use int abs() here */
__attribute__ ((leaf, nonnull (1), nothrow))
void update_absdev (void *restrict _dest, unigram_t val) {
   absdev_t *restrict dest = (absdev_t *restrict) _dest;
   double dev;
#ifndef NDEBUG
   printf ("dest->sum:%g\n", dest->sum); fflush (stdout);
   printf ("dest->val:%d\n", (int) val); fflush (stdout);
#endif
   TODO (check overflow)
   dev = dest->ct - val;
#ifndef NDEBUG
   printf ("dev:%g\n", dev); fflush (stdout);
#endif
   dev = fabs (dev);
#ifndef NDEBUG
   printf ("|dev|:%g\n", dev); fflush (stdout);
#endif
   dest->sum += dev;
#ifndef NDEBUG
   printf ("dest->sum:%g\n", dest->sum); fflush (stdout);
#endif
}

__attribute__ ((leaf, nonnull (1), nothrow))
void finish_absdev (void *restrict _dest) {
   absdev_t *restrict dest = (absdev_t *restrict) _dest;
   TODO (compute median deviation)
   dest->res = dest->sum / (double) (dest->df);
#ifndef NDEBUG
   printf ("dest->sum:%g\n", dest->sum); fflush (stdout);
   printf ("dest->res:%g\n", dest->res); fflush (stdout);
#endif
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void init_absdev_stat (stat_t *restrict stat, absdev_t *restrict absdev) {
   stat->init   = init_absdev;
   stat->update = update_absdev;
   stat->finish = finish_absdev;
   stat->stat   = absdev;
}

__attribute__ ((nonnull (1, 2), nothrow))
void ez_absdev (
   absdev_t *restrict absdev,
   unigram_t const vals[], size_t nval) {
   stat_t s;
   init_absdev_stat (&s, absdev);
   ez_stat (&s, vals, nval);
}

__attribute__ ((nonnull (2), nothrow, pure, warn_unused_result))
double ezr_absdev (double ct, unigram_t const vals[], size_t nval) {
   absdev_t absdev;
   absdev.ct = ct;
   ez_absdev (&absdev, vals, nval);
   return absdev.res;
}
