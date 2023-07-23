#include "board.h"
#include "enums.h"
#include "globals.h"

/**
 * @brief reset the board to its initial state.
 *
 * @param pos (*BOARD) the board be reset.
 *
 * @return void
*/
void resetBoard (BOARD *pos) {

    for (int i = 0; i < BOARD_SQUARES; ++i) {
        pos->pieces[i] = OFF_BOARD;
    }

    for (int i = 0; i < 64; ++i) {
        pos->pieces[SQ120(i)] = EMPTY;
    }

    for (int i = 0; i < 3; ++i) {
        pos->bigPieces[i] = 0;
        pos->majorPieces[i] = 0;
        pos->minorPieces[i] = 0;
        pos->pawns[i] = 0LL;
    }

    for (int i = 0; i < 13; ++i) {
        pos->pieceNumber[i] = 0;
    }

    pos->kingSquare[WHITE] = pos->kingSquare[BLACK] = SQ_NONE;

    pos->sideToMove = BOTH;
    pos->enPassant = SQ_NONE;
    pos->fiftyMove = 0;

    pos->ply = 0;
    pos->hisPly = 0;

    pos->castlePermission = 0;

    pos->posKey = 0ULL;

    //TODO: piece list
}

/**
 * @brief parse a fen.
 *
 * @param fen (*const char) FEN notation string to be parsed (https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation)
 * @param pos (*BOARD) the board to store the parsing result
 *
 * @return 0 on success.
 * @return 1 on fail with a relevant message.
 */
int parseFen (const char *fen, BOARD *pos) {

    if (!fen || !pos)
        return 1;

    int rank = RANK_8;
    int file = FILE_A;
    int count = 0;
    int piece = 0;
    int sq64;
    int sq120;

    resetBoard(pos);

    while ((rank >= RANK_1) && *fen) {
        switch (*fen) {
            count = 1;
            case 'p': piece = p; break;
            case 'r': piece = r; break;
            case 'n': piece = n; break;
            case 'b': piece = b; break;
            case 'k': piece = k; break;
            case 'q': piece = q; break;
            case 'P': piece = P; break;
            case 'R': piece = R; break;
            case 'N': piece = N; break;
            case 'B': piece = B; break;
            case 'K': piece = K; break;
            case 'Q': piece = Q; break;

            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
                piece = EMPTY;
                count = *fen - '0';
                break;

            case '/':
            case ' ':
                rank--;
                file = FILE_A;
                fen++;
                continue;

            default:
                printf("FEN error!\n");
                return 1;
        }

        for (int i = 0; i < count; ++i) {
            sq64 = rank * 8 + file;
            sq120 = SQ120(sq64);
            if (piece != EMPTY)
                pos->pieces[sq120] = piece;
            file++;
        }
        fen++;
    }
    return 0;
}