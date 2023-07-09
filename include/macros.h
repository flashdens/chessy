#include <stdio.h>
#include <stdlib.h>

#ifndef MILOCHESS_MACROS_H
#define MILOCHESS_MACROS_H

#define FR2SQ(f, r) (( 21 + f ) + ( 10 * r ))

#define DEBUG

#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n) \
if (!(n)) {     \
printf("%s - Failed ",#n); \
printf("On %s ",__DATE__); \
printf("At %s ",__TIME__); \
printf("In file %s, ",__FILE__);\
printf("line %d\n",__LINE__); \
exit(1);}
#endif

#endif //MILOCHESS_MACROS_H
