#include "generate.h"
#include "globals.h"
#include "enums.h"

/**
 * @brief add a quiet move to the move list.
 *
 * a move is considered quiet if it's not a capture, not a check or not a significant threat to the opponent.
 *
 * @param pos (const *BOARD) the position
 * @param list (*MOVELIST) the move list to append the move
 * @param move the move to be added to the move list
 *
 * @return void
 */
void addQuietMove (const BOARD *pos, MOVELIST *list, int move) {
    list->moves[list->count].info = move;
    list->moves[list->count].score = 0;
    list->count++;
}

void addCaptureMove (const BOARD *pos, MOVELIST *list, int move) {
    list->moves[list->count].info = move;
    list->moves[list->count].score = 0;
    list->count++;
}

void addEnPassantMove (const BOARD *pos, MOVELIST *list, int move) {
    list->moves[list->count].info = move;
    list->moves[list->count].score = 0;
    list->count++;
}

/**
 * @brief add a pawn move to the move list.
 *
 * @param pos (const *BOARD) the position in which a move is made
 * @param from (const) the square from which a move is made
 * @param to (const) the square to which a move is made
 * @param capture (const) the captured piece (if so)
 * @param list (*MOVELIST) the list append the move to
 */
void addPawnMove (const BOARD *pos, const int from, const int to, MOVELIST *list) {

    ASSERT(isSquareOnBoard(from));
    ASSERT(isSquareOnBoard(to));

    // is the move a promotion?
    if (boardRanks[from] == RANK_7 && pos->sideToMove == WHITE) {
        addQuietMove(pos, list, MOVE(from, to, EMPTY, Q, 0));
        addQuietMove(pos, list, MOVE(from, to, EMPTY, R, 0));
        addQuietMove(pos, list, MOVE(from, to, EMPTY, B, 0));
        addQuietMove(pos, list, MOVE(from, to, EMPTY, N, 0));
    }
    else if (boardRanks[from] == RANK_2 && pos->sideToMove == BLACK) {
        addQuietMove(pos, list, MOVE(from, to, EMPTY, q, 0));
        addQuietMove(pos, list, MOVE(from, to, EMPTY, r, 0));
        addQuietMove(pos, list, MOVE(from, to, EMPTY, b, 0));
        addQuietMove(pos, list, MOVE(from, to, EMPTY, n, 0));
    }
    // if not..
    else {
        addQuietMove(pos, list, MOVE(from, to, EMPTY, EMPTY, 0));
    }
}

/**
 * @brief add a pawn capture move the the move list.
 *
 * @param pos (const *BOARD) the position in which a move is made
 * @param from (const) the square from which a move is made
 * @param to (const) the square to which a move is made
 * @param capture (const) the captured piece (if so)
 * @param list (*MOVELIST) the list append the move to
 */
void addPawnCaptureMove (const BOARD *pos, const int from, const int to, const int capture, MOVELIST *list) {

    ASSERT(isPieceValidOrEmpty(capture));
    ASSERT(isSquareOnBoard(from));
    ASSERT(isSquareOnBoard(to));


    // is the move a promotion?
    if (boardRanks[from] == RANK_7 && pos->sideToMove == WHITE) {
        addCaptureMove(pos, list, MOVE(from, to, capture, Q, 0));
        addCaptureMove(pos, list, MOVE(from, to, capture, R, 0));
        addCaptureMove(pos, list, MOVE(from, to, capture, B, 0));
        addCaptureMove(pos, list, MOVE(from, to, capture, N, 0));
    }
    else if (boardRanks[from] == RANK_2 && pos->sideToMove == BLACK) {
        addCaptureMove(pos, list, MOVE(from, to, capture, q, 0));
        addCaptureMove(pos, list, MOVE(from, to, capture, r, 0));
        addCaptureMove(pos, list, MOVE(from, to, capture, b, 0));
        addCaptureMove(pos, list, MOVE(from, to, capture, n, 0));
    }
    else {
        addCaptureMove(pos, list, MOVE(from, to, capture, EMPTY, 0));
    }
}

void generateWhitePawnMoves (const BOARD *pos, MOVELIST *list) {

    int piece = EMPTY;
    int square = 0;
    int tempSquare = 0;
    int numOfPieces = 0;


    for (int i = 0; i < pos->numOfPieces[P]; ++i) {
        square = pos->pieceList[P][i];
        ASSERT(isSquareOnBoard(square));

        // consider a quiet move
        if (pos->pieces[square + 10] == EMPTY) {
            addPawnMove(pos, square, square + 10, list);
            // consider a 2-square "jump" from the starting field
            if (boardRanks[square] == RANK_2 && pos->pieces[square + 20] == EMPTY)
                addQuietMove(pos, list, MOVE(square, square + 20, EMPTY, EMPTY, ISPAWNSTART));
        }

        // consider a capture move
        if (isSquareOnBoard(square + 9) && pos->sideToMove == WHITE, pieceCol[pos->pieces[square + 9]] == BLACK)
            addPawnCaptureMove(pos, square, square + 9, pos->pieces[square + 9], list);

        if (isSquareOnBoard(square + 11) && pos->sideToMove == WHITE, pieceCol[pos->pieces[square + 11]] == BLACK)
            addPawnCaptureMove(pos, square, square + 11, pos->pieces[square + 9], list);

        // consider an en passant move
        if (square + 9 == pos->enPassant)
            addCaptureMove(pos, list, MOVE(square, square + 9, EMPTY, EMPTY, ISENPASSANT));

        if (square + 11 == pos->enPassant)
            addCaptureMove(pos, list, MOVE(square, square + 11, EMPTY, EMPTY, ISENPASSANT));
    }
}

void generateBlackPawnMoves (const BOARD *pos, MOVELIST *list) {

    int piece = EMPTY;
    int square = 0;
    int tempSquare = 0;
    int numOfPieces = 0;
    int dir = 0;

    for (int i = 0; i < pos->numOfPieces[p]; ++i) {
        square = pos->pieceList[p][i];
        ASSERT(isSquareOnBoard(square));

        // consider a quiet move
        if (pos->pieces[square - 10] == EMPTY) {
            addPawnMove(pos, square, square - 10, list);
            // consider a 2-square "jump" from the starting field
            if (boardRanks[square] == RANK_7 && pos->pieces[square - 20] == EMPTY)
                addQuietMove(pos, list, MOVE(square, square - 20, EMPTY, EMPTY, ISPAWNSTART));
        }

        // consider a capture move
        if (isSquareOnBoard(square - 9) && pos->sideToMove == BLACK, pieceCol[pos->pieces[square - 9]] == WHITE)
            addPawnCaptureMove(pos, square, square - 9, pos->pieces[square - 9], list);

        if (isSquareOnBoard(square - 11) && pos->sideToMove == BLACK, pieceCol[pos->pieces[square - 11]] == WHITE)
            addPawnCaptureMove(pos, square, square - 11, pos->pieces[square - 9], list);

        // consider an en passant move
        if (square - 9 == pos->enPassant)
            addCaptureMove(pos, list, MOVE(square, square - 9, EMPTY, EMPTY, ISENPASSANT));

        if (square - 11 == pos->enPassant)
            addCaptureMove(pos, list, MOVE(square, square - 11, EMPTY, EMPTY, ISENPASSANT));
    }
}

void generateSlidingPieceMoves (const BOARD *pos, MOVELIST *list) {

    int slidePieces[3] = {
            (pos->sideToMove == WHITE) ? B : b,
            (pos->sideToMove == WHITE) ? R : r,
            (pos->sideToMove == WHITE) ? Q : q
    };

    for (int i = 0; i < 3; ++i) {
        ASSERT(isPieceValid(slidePieces[i]));
        printf("slider piece index: %d, piece %d\n", i, slidePieces[i]);
    }
}

void generateNonSlidingPieceMoves (const BOARD *pos, MOVELIST *list) {

    const int nonSlidePieces[2] = {
            (pos->sideToMove == WHITE) ? N : n,
            (pos->sideToMove == WHITE) ? K : k,
    };
    int square = 0;
    int dir = 0;
    int tempSquare = 0;

    for (int i = 0; i < 2; ++i) {
        for (int piece = 0; piece < pos->numOfPieces[nonSlidePieces[i]]; ++piece) {
            square = pos->pieceList[nonSlidePieces[i]][piece];
            ASSERT(isSquareOnBoard(square));
            printf("Piece %c on %s\n", pieceChar[nonSlidePieces[i]], printSquare(square));

            for (int j = 0; j < 8; ++j) {
                dir = (nonSlidePieces[i] == N || nonSlidePieces[i] == n) ?  knightDir[j] : kingDir[j];
                tempSquare = square + dir;

                if (!isSquareOnBoard(tempSquare))
                    continue;

                if (pos->pieces[tempSquare] != EMPTY) {
                    if (pieceCol[pos->pieces[tempSquare]] != pos->sideToMove)
                        printf("\t\tcapture on %s!\n", printSquare(tempSquare));
                    continue;
                }

                printf("\t\tquiet on %s\n", printSquare(tempSquare));
            }
        }
    }
}

void generateAllMoves (const BOARD *pos, MOVELIST *list) {

    ASSERT(assertBoard(pos));

    if (pos->sideToMove == WHITE) {
        generateWhitePawnMoves(pos, list);
        generateSlidingPieceMoves(pos, list);
        generateNonSlidingPieceMoves(pos, list);
    }
    else {
        generateBlackPawnMoves(pos, list);
        generateSlidingPieceMoves(pos, list);
        generateNonSlidingPieceMoves(pos, list);
    }
}
