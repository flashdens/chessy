#include <stdbool.h>

#include "validate.h"
#include "globals.h"
#include "enums.h"

/**
 * @brief check if a square is on the board.
 *
 * @param sq  the square to be checked
 *
 * @return (bool) true if true
 * @return (bool) false otherwise
 */
bool isSquareOnBoard (const int sq) {
    return (boardFiles[sq] != OFF_BOARD) ? true : false;
}

/**
 * @brief check if it's either white or black to make a move.
 *
 * @param side  the side to move
 *
 * @return (bool) true if true
 * @return (bool) false otherwise
 */
bool isSideValid (const int side) {
    return (side == WHITE || side == BLACK) ? true : false;
}

/**
 * @brief check if a file or rank is on the board.
 *
 * @param fr  the file or rank to be checked
 *
 * @return (bool) true if true
 * @return (bool) false otherwise
 */
bool isFileRankValid (const int fr) {
    return (fr >= 0 && fr <= 7) ? true : false;
}

/**
 * @brief check if a piece is valid or empty.
 *
 * @param piece  the piece to be checked
 *
 * @return (bool) true if true
 * @return (bool) false otherwise
 */
bool isPieceValidOrEmpty (const int piece) {
    return (piece >= EMPTY && piece <= k) ? true : false;
}

/**
 * @brief check if a piece is valid (not empty).
 *
 * @param piece  the piece to be checked
 *
 * @return (bool) true if true
 * @return (bool) false otherwise
 */
bool isPieceValid (const int piece) {
    return (piece >= P && piece <= k) ? true : false;
}


