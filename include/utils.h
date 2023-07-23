/**
 * @file utils.h
 * @brief contains short supporting utility macros and functions.
 */

#ifndef MILOCHESS_UTILS_H
#define MILOCHESS_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

/**
 * to save some time typing. U64 means an unsigned 64-bit integer.
 */
#define U64 unsigned long long

#include "globals.h"
#include "init.h"

/**
 * @brief a supporting testing function to assure things don't bug.
 */
 #ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n) \
if(!(n)) { \
printf("%s - Failed",#n); \
printf("On %s ",__DATE__); \
printf("At %s ",__TIME__); \
printf("In File %s ",__FILE__); \
printf("At Line %d\n",__LINE__); \
exit(1);          \
}
#endif

/**
 * @brief obtain the corresponding value of a 120-square based on a 64-square.
 *
 * @var Sq120ToSq64 (int[]) array of 120sq to 64sq values
 *
 * @return the corresponding 120-square based square.
 */
#define SQ64(sq120) Sq120ToSq64[sq120]

/**
 * @brief obtain the corresponding value of a 120-square based on a 64-square.
 *
 * @var Sq120ToSq64 (int[]) array of 120sq to 64sq values
 *
 * @return the corresponding 120-square based square.
 */
#define SQ120(sq64) Sq64ToSq120[sq64]

/**
 * @brief convert a 64 square-based square to its corresponding 120-based square.
 *
 * @param f (int) the file number
 * @param r (int) the rank number
 *
 * @return the corresponding 120-based square.
 */
int FR2SQ (int f, int r);

/**
 * @brief generate a random unsigned 64-bit integer.
 *
 * @return a random 64-bit integer.
 */
U64 generateRandomU64 ();

#endif //MILOCHESS_UTILS_H
