#include "perft.h"

#ifndef MILOCHESS_PERFTHUB_H
#define MILOCHESS_PERFTHUB_H

#define S_FLAG (1 << 0)
#define H_FLAG (1 << 1)
#define L_FLAG (1 << 2)
#define E_FLAG (1 << 3)
#define F_FLAG (1 << 4)
#define D_FLAG (1 << 5)
#define T_FLAG (1 << 6)

/**
 * @brief utility function to download input for perfthub from a server.
 *
 * TODO: pass an url to download from and ensure it's safe
 *
 * @return 0 on success
 * @return 1 on failure alongside relevant information
 */
int getInput ();

/**
 * @brief utility function to clear stdin.
 *
 * @return void
 */
void clearStdin ();

/**
 * @brief print help regarding perfthub.
 *
 * @return void
 */
void printHelp ();

/**
 *
 * @brief perft-test against a set of results stored in a text file.
 *
 * @param argc argument count
 * @param argv arguments
 *
 * @see printHelp() for more information
 *
 * @return 0 on success
 * @return 1 on failure, alongside relevant information
 */
int perfthub (int argc, char **argv);

#endif //MILOCHESS_PERFTHUB_H
