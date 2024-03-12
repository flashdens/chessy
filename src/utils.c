/**
 * @file utils.c
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
 * @brief obtain the corresponding value of a 120-square based on a 64-square.
 *
 * @var Sq120ToSq64 (int[]) array of 120sq to 64sq values
 */
#define SQ64(sq120) Sq120ToSq64[sq120]

/**
 * @brief convert a 64 square-based square to its corresponding 120-based square.
 *
 * @param f (int) the file number
 * @param r (int) the rank number
 *
 * @return the corresponding 120-based square.
 */
int FR2SQ (int f, int r) {
    return (( 21 + f ) + ( 10 * r ));
}

/**
 * @brief print a binary number to stdout.
 *
 * @param num the number to be printed
 *
 * @return void
 */
void printBinaryNumber (int num) {

    int numBits = sizeof(num) * 8;
    unsigned int mask = 1 << (numBits - 1);

    for (int i = 0; i < numBits; i++) {
        if ((num & mask) != 0)
            printf("1");
        else
            printf("0");

        mask >>= 1;

        if (i % 4 == 3)
            printf(" ");
    }
    printf("\n");
}

#endif //MILOCHESS_UTILS_H
