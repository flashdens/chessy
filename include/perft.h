//
// Created by miloszek on 07.08.23.
//

#ifndef MILOCHESS_PERFT_H
#define MILOCHESS_PERFT_H

#include "board.h"

/**
 * @brief
 * @param pos
 * @param depth
 */
void perft (BOARD *pos, int depth);

/**
 * @brief
 * @param pos
 * @param depth
 */
void perftTest (BOARD *pos, int depth);

#endif //MILOCHESS_PERFT_H
