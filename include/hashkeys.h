#include <stdlib.h>

#include "utils.h"
#include "board.h"

#ifndef MILOCHESS_HASHKEYS_H
#define MILOCHESS_HASHKEYS_H

/**
 * @brief generate a random unsigned 64-bit integer.
 *
 * @return a random 64-bit integer.
 */
U64 generateRandomU64 ();

/**
 * @brief generate a hash key for a given position.
 *
 * @param pos [*BOARD] a pointer to the given BOARD structure.
 *
 * @return [U64] the hash key of the position.
 */
U64 generatePositionKey (const BOARD *pos);

#endif //MILOCHESS_HASHKEYS_H
