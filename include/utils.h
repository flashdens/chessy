#ifndef MILOCHESS_UTIL_H
#define MILOCHESS_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define U64 unsigned long long

#include "globals.h"
#include "init.h"


#define FR2SQ(f, r) (( 21 + f ) + ( 10 * r ))
#define SQ64(sq120) Sq120ToSq64[sq120]


#define DEBUG
#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n) \
if (!(n)) {       \
printf("%s - Failed ",#n); \
printf("On %s ",__DATE__); \
printf("At %s ",__TIME__); \
printf("In file %s, ",__FILE__);\
printf("line %d\n",__LINE__); \
exit(1);          \
}
#endif

U64

#endif //MILOCHESS_UTIL_H
