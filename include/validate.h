/**
 * @file validate.h
 * @brief various validation function declarations for validate.c
 */

/**
 * @brief check if a square is on the board.
 *
 * @param sq  the square to be checked
 *
 * @return (bool) true if true
 * @return (bool) false otherwise
 */
extern bool isSquareOnBoard (int sq);

/**
 * @brief check if it's either white or black to make a move.
 *
 * @param piece  the side to move
 *
 * @return (bool) true if true
 * @return (bool) false otherwise
 */
extern bool isSideValid (int side);

/**
 * @brief check if a file or rank is on the board.
 *
 * @param piece  the file or rank to be checked
 *
 * @return (bool) true if true
 * @return (bool) false otherwise
 */
extern bool isFileRankValid (int fr);

/**
 * @brief check if a piece is valid or empty.
 *
 * @param piece  the piece to be checked
 *
 * @return (bool) true if true
 * @return (bool) false otherwise
 */
extern bool isPieceValidOrEmpty (int piece);

/**
 * @brief check if a piece is valid (not empty).
 *
 * @param piece  the piece to be checked
 *
 * @return (bool) true if true
 * @return (bool) false otherwise
 */
extern bool isPieceValid (int piece);