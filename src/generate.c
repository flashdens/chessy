#include "generate.h"
#include "globals.h"
#include "enums.h"
#include "attack.h"

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
    int toSquare = 0;
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
    int toSquare = 0;
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

    /**
  * 0 is for bishops,
  * 1 is for rooks,
  * 2 is for queens
  * 3 is for beans (there is no 3)
  */
    int slidePieces[3] = {
            (pos->sideToMove == WHITE) ? B : b,
            (pos->sideToMove == WHITE) ? R : r,
            (pos->sideToMove == WHITE) ? Q : q
    };

    int square = 0;
    int dir = 0;
    int processedPiece = 0;
    int toSquare;

    for (int i = 0; i < 3; ++i) {
        processedPiece = slidePieces[i];

        // process all instances of the pieces on the board
        for (int piece = 0; piece < pos->numOfPieces[processedPiece]; ++piece) {
            square = pos->pieceList[processedPiece][piece];
            ASSERT(isSquareOnBoard(square));
            printf("Piece %c on %s\n", pieceChar[processedPiece], printSquare(square));

            // check in 4 directions if a piece is a bishop or a rook
            // in 8 if it's a queen
            for (int j = 0; j < ((processedPiece == Q || processedPiece == q) ? 8 : 4); ++j) {
                dir = (processedPiece == B || processedPiece == b) ? bishopDir[j] : rookDir[j];

                /* this one is weird, but when analyzing queen directions, first straight (rook) ones are checked,
                 * and then diagonal (bishop) ones. the code is super unreadable i know right */
                if ((processedPiece == Q || processedPiece == q) && j > 3)
                    dir = bishopDir[j-4];

                toSquare = square + dir;

                while (isSquareOnBoard(toSquare)) {
                    // if a piece is met...
                    if (pos->pieces[toSquare] != EMPTY) {
                        // and it's enemy...
                        if (pieceCol[pos->pieces[toSquare]] != pos->sideToMove)
                            addCaptureMove(pos, list, MOVE(square, toSquare, pos->pieces[toSquare], EMPTY, 0));
                        break;
                    }

                    addQuietMove(pos, list, MOVE(square, toSquare, EMPTY, EMPTY, 0));
                    toSquare += dir;
                }
            }
        }
    }
}

void generateNonSlidingPieceMoves (const BOARD *pos, MOVELIST *list) {

    /**
     * 0 is for knights,
     * 1 is for kings
     */
    const int nonSlidePieces[2] = {
            (pos->sideToMove == WHITE) ? N : n,
            (pos->sideToMove == WHITE) ? K : k,
    };
    int square = 0;
    int dir = 0;
    int toSquare = 0;
    int processedPiece = 0;

    for (int i = 0; i < 2; ++i) {
        processedPiece = nonSlidePieces[i];

        // process all instances of the pieces on the board
        for (int piece = 0; piece < pos->numOfPieces[processedPiece]; ++piece) {
            square = pos->pieceList[processedPiece][piece];
            ASSERT(isSquareOnBoard(square));
            printf("Piece %c on %s\n", pieceChar[processedPiece], printSquare(square));

            // check each direction in which a piece can go
            for (int j = 0; j < 8; ++j) {
                dir = (processedPiece == N || processedPiece == n) ?  knightDir[j] : kingDir[j];
                toSquare = square + dir;

                if (!isSquareOnBoard(toSquare))
                    continue;

                if (pos->pieces[toSquare] != EMPTY) {
                    if (pieceCol[pos->pieces[toSquare]] != pos->sideToMove)
                        addCaptureMove(pos, list, MOVE(square, toSquare, pos->pieces[toSquare], EMPTY, 0));
                    continue;
                }

                addQuietMove(pos, list, MOVE(square, toSquare, EMPTY, EMPTY, 0));
            }
        }
    }
}

void generateWhiteCastlingMoves (const BOARD *pos, MOVELIST *list) {

    if (pos->castlePermission & WKCA) {
        if (!isSquareAttacked(E1, BLACK, pos) &&
        (pos->pieces[F1] == EMPTY && !isSquareAttacked(F1, BLACK, pos)) &&
        (pos->pieces[G1] == EMPTY && !isSquareAttacked(G1, BLACK, pos)))
        {
            addQuietMove(pos, list, MOVE(E1, G1, EMPTY, EMPTY, ISCASTLE));
        }
    }

    if (pos->castlePermission & WQCA) {
        if (!isSquareAttacked(E1, BLACK, pos) &&
            (pos->pieces[D1] == EMPTY && !isSquareAttacked(D1, BLACK, pos)) &&
            (pos->pieces[C1] == EMPTY && !isSquareAttacked(C1, BLACK, pos)))
        {
            addQuietMove(pos, list, MOVE(E1, C1, EMPTY, EMPTY, ISCASTLE));
        }

    }

}

void generateBlackCastlingMoves (const BOARD *pos, MOVELIST *list) {

    if (pos->castlePermission & BKCA) {
        if (!isSquareAttacked(E8, WHITE, pos) &&
            (pos->pieces[F8] == EMPTY && !isSquareAttacked(F8, WHITE, pos)) &&
            (pos->pieces[G8] == EMPTY && !isSquareAttacked(G8, WHITE, pos)))
            addQuietMove(pos, list, MOVE(E8, G8, EMPTY, EMPTY, ISCASTLE));
    }

    if (pos->castlePermission & BQCA) {
        if (!isSquareAttacked(E8, WHITE, pos) &&
            (pos->pieces[D8] == EMPTY && !isSquareAttacked(D8, WHITE, pos)) &&
            (pos->pieces[C8] == EMPTY && !isSquareAttacked(C8, WHITE, pos)))
            addQuietMove(pos, list, MOVE(E8, C8, EMPTY, EMPTY, ISCASTLE));
    }

}

void generateAllMoves (const BOARD *pos, MOVELIST *list) {

    ASSERT(assertBoard(pos));

    if (pos->sideToMove == WHITE) {
        generateWhitePawnMoves(pos, list);
        generateNonSlidingPieceMoves(pos, list);
        generateSlidingPieceMoves(pos, list);
        generateWhiteCastlingMoves(pos, list);
    }
    else {
        generateBlackPawnMoves(pos, list);
        generateNonSlidingPieceMoves(pos, list);
        generateSlidingPieceMoves(pos, list);
        generateBlackCastlingMoves(pos, list);
    }
}
