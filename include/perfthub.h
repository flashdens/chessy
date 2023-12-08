#include "perft.h"

#ifndef MILOCHESS_PERFTHUB_H
#define MILOCHESS_PERFTHUB_H

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
