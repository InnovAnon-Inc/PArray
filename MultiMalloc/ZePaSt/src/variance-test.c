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

/*#include <mean.h>*/
#include <sum.h>
#include <variance.h>

__attribute__ ((nothrow, warn_unused_result))
int main (void) {
   /*mean_t mean;*/
   sum_t sum;
   variance_t variance;

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
   /*mean.cnt = ARRSZ (vals);
   ez_mean (&mean, vals, ARRSZ (vals));*/
   ez_sum (&sum, vals, ARRSZ (vals));

#ifndef NDEBUG
   (void) printf ("sum:%d\n",  (int) (mean.sum));
   (void) printf ("mean:%g\n", mean.res);
#endif

   /*variance.ct = mean.res;*/
   variance.ct = (double) sum / (double) ARRSZ (vals);
   if (ARRSZ (vals) >= 30) variance.df = ARRSZ (vals) - 1;
   else                    variance.df = ARRSZ (vals);
   ez_variance (&variance, vals, ARRSZ (vals));

   (void) printf ("variance:%g\n", variance.sum);
   (void) printf ("stddev:%g\n",   variance.res);

   return EXIT_SUCCESS;
}
