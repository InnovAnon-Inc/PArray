#if HAVE_CONFIG_H
#include <config.h>
#endif

#define _POSIX_C_SOURCE 200112L
#define __STDC_VERSION__ 200112L

#define NDEBUG 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <mean.h>
TODO (median.h)
#include <absdev.h>

__attribute__ ((nothrow, warn_unused_result))
int main (void) {
   mean_t mean;
   absdev_t absdev;

   char const str[] = "Hello, World!";
   unigram_t vals[sizeof (str) * sizeof (char)];
   size_t vi;

   /*(void) memcpy (vals, str, sizeof (str));*/
   TODO (check overflow)
#ifndef NDEBUG
   printf ("ARRSZ (vals):%d\n", (int) ARRSZ (vals)); fflush (stdout);
#endif
	#pragma GCC ivdep
   for (vi = 0; vi != ARRSZ (vals); vi++) {
      vals[vi] = (unigram_t) str[vi];
#ifndef NDEBUG
      printf ("vals[%d]:%d %c\n", (int) vi,
         (int) (vals[vi]), (char) (vals[vi])); fflush (stdout);
#endif
   }
   mean.cnt = ARRSZ (vals);
   ez_mean (&mean, vals, ARRSZ (vals));

#ifndef NDEBUG
   (void) printf ("sum:%d\n",  (int) (mean.sum));
   (void) printf ("mean:%g\n", mean.res);
#endif

   absdev.ct = mean.res;
   absdev.df = ARRSZ (vals);
   ez_absdev (&absdev, vals, ARRSZ (vals));

   (void) printf ("absvar:%g\n", absdev.sum);
   (void) printf ("absdev:%g\n", absdev.res);

   return EXIT_SUCCESS;
}
