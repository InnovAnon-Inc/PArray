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

#include <sum.h>

__attribute__ ((nothrow, warn_unused_result))
int main (void) {
   sum_t sum;

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
   ez_sum (&sum, vals, ARRSZ (vals));

   (void) printf ("sum:%d\n",  (int) sum);

   return EXIT_SUCCESS;
}
