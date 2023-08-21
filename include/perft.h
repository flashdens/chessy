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
void perft (BOARD *pos, int depth, long *leafNodes);

/**
 * @brief
 * @param pos
 * @param depth
 */
void perftTest (BOARD *pos, int depth);

/**
 *
 * @brief perft-test against a set of results stored in a text file.
 *
 * @param argc argument count
 * @param argv arguments
 *
 * @return 0 on success
 * @return 1 on failure, alongside relevant information
 */
int perftHub();

#endif //MILOCHESS_PERFT_H
