/**
 * @file board.c
 * @brief contains functions which modify the BOARD structure defined in board.h.
 */

#include <stdbool.h>

#include "board.h"
#include "globals.h"
#include "enums.h"
#include "hashkeys.h"
#include "bitboards.h"

/**
 * @brief reset the board to its default state.
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

    pos->kingSquare[WHITE] = pos->kingSquare[BLACK] = SQ_NONE;

    pos->sideToMove = BOTH;
    pos->enPassant = SQ_NONE;
    pos->fiftyMove = 0;

    for (int i = 0; i < 13; ++i) {
        pos->numOfPieces[i] = 0;
    }

    for (int i = 0; i < 2; ++i) {
        pos->pawns[i] = 0LL;
        pos->bigPieces[i] = 0;
        pos->majPieces[i] = 0;
        pos->minPieces[i] = 0;
        pos->material[i] = 0;
    }
    pos->pawns[2] = 0LL;

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
 * the operation loads the data into the board structure step by step.
 *
 * first the board setup is loaded into the piece array,
 * then side to move, castle permissions, en passant square and ply.
 *
 * @return 0 on success.
 * @return 1 on fail with a relevant message.
 */
int parseFen (const char *fen, BOARD *pos) {

    if (!fen || !pos)
        return 1;

    int rank = RANK_8;
    int file = FILE_A;
    int count = 1;
    int piece = 0;
    int sq64;
    int sq120;

    resetBoard(pos);

    // process pieces
    while ((rank >= RANK_1) && *fen) {
        count = 1;
        switch (*fen) {
            case 'p':
                piece = p;
                break;
            case 'r':
                piece = r;
                break;
            case 'n':
                piece = n;
                break;
            case 'b':
                piece = b;
                break;
            case 'k':
                piece = k;
                break;
            case 'q':
                piece = q;
                break;
            case 'P':
                piece = P;
                break;
            case 'R':
                piece = R;
                break;
            case 'N':
                piece = N;
                break;
            case 'B':
                piece = B;
                break;
            case 'K':
                piece = K;
                break;
            case 'Q':
                piece = Q;
                break;

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

    ASSERT(*fen == 'w' || *fen == 'b');

    // process side to move
    pos->sideToMove = (*fen == 'w') ?
            WHITE
            : BLACK;

    fen += 2;

    // process castle permissions
    for (int i = 0; i < 4; ++i) {
        if (*fen == ' ')
            break;

        switch (*fen) {
            case 'K':
                pos->castlePermission |= WKCA;
                break;
            case 'Q':
                pos->castlePermission |= WQCA;
                break;
            case 'k':
                pos->castlePermission |= BKCA;
                break;
            case 'q':
                pos->castlePermission |= BQCA;
                break;
            default:
                break;
        }
        fen++;
    }
    fen++;

    ASSERT(pos->castlePermission >= 0 && pos->castlePermission <= 15);

    // process the en passant square
    if (*fen != '-') {
        file = fen[0] - 'a';
        rank = fen[1] - '1';

        ASSERT(file >= FILE_A && file <= FILE_H);
        ASSERT(rank >= RANK_1 && rank <= RANK_8);

        pos->enPassant = FR2SQ(file, rank);
    }

    pos->posKey = generatePositionKey(pos);

    updateMaterialLists(pos);

    return 0;
}

/**
 * @brief print the board and other important information to stdout.
 *
 * @param pos (*BOARD) the board to be printed
 *
 * @return void
 */
void printBoard (const BOARD *pos) {

    int square;
    int piece;

    printf("Current board state:\n");
    for (int rank = RANK_8; rank >= RANK_1; --rank) {
        printf("%d ", rank + 1);
        for (int file = FILE_A; file <= FILE_H; ++file) {
          square = FR2SQ(file, rank);
          piece = pos->pieces[square];
          printf("%3c", pieceChar[piece]);
        }
        printf("\n");
    }

    printf("\n  ");
    for (int file = FILE_A; file <= FILE_H; ++file) {
        printf("%3c",'a' + file);
    }
    printf("\n\n");

    printf("side to move:%c\n",sideChar[pos->sideToMove]);
    printf("en passant square: %d\n",pos->enPassant);
    printf("castle permissions: %c%c%c%c\n",
           pos->castlePermission & WKCA ? 'K' : '-',
           pos->castlePermission & WQCA ? 'Q' : '-',
           pos->castlePermission & BKCA ? 'k' : '-',
           pos->castlePermission & BQCA ? 'q' : '-'
    );
    printf("position key: %llX\n",pos->posKey);
    printf("\n");
}

/**
 * @brief update material piece lists.
 *
 * @param pos (*BOARD) the position to have the lists updated.
 *
 * @return void
 */
void updateMaterialLists (BOARD *pos) {

    int square;
    int piece;
    int colour;


    for (int i = 0; i < BOARD_SQUARES; ++i) {
        square = i;
        piece = pos->pieces[i];
        if (piece != OFF_BOARD && piece != EMPTY) {
            colour = pieceCol[piece];

            // update the according lists
            if (isPieceMin[piece] == true)
                pos->minPieces[colour]++;
            if (isPieceMaj[piece] == true)
                pos->majPieces[colour]++;
            if (isPieceBig[piece] == true)
                pos->bigPieces[colour]++;

            // update the material counter
            pos->material[colour] += pieceVal[piece];

            // update the main piece list
            pos->pieceList[piece][pos->numOfPieces[piece]] = square;
            pos->numOfPieces[piece]++;

            // update the king square
            if (piece == K)
                pos->kingSquare[WHITE] = square;
            if (piece == k)
                pos->kingSquare[BLACK] = square;

            if (piece == P) {
                setBit(&pos->pawns[WHITE], SQ64(square));
                setBit(&pos->pawns[BOTH], SQ64(square));
            }
            else if (piece == p) {
                setBit(&pos->pawns[BLACK], SQ64(square));
                setBit(&pos->pawns[BOTH], SQ64(square));
            }
        }
    }
}

/**
 * @brief assert if the board structure contains correct information about the board.
 *
 * @param pos (*const BOARD) the position to be checked.
 *
 * @return 0 on success
 * @return program exit with code 1 on failure
 */
int assertBoard (const BOARD *pos) {

   int square;
   int square64;
   int checkNumOfPieces2;
   int colour;
   int pawnCount;
   int tempPiece;

   int tempNumOfPieces[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
   int tempMinPieces[2] = {0, 0};
   int tempBigPieces[2] = {0, 0};
   int tempMajPieces[2] = {0, 0};
   int tempMaterial[2] = {0, 0};

   U64 tempPawns[3] = {0ULL, 0ULL, 0ULL};

   tempPawns[WHITE] = pos->pawns[WHITE];
   tempPawns[BLACK] = pos->pawns[BLACK];
   tempPawns[BOTH] = pos->pawns[BOTH];
   // check piece lists
    for (tempPiece = 0; tempPiece < 13; ++tempPiece) {
        for (int pieceNumber = 0; pieceNumber < pos->numOfPieces[tempPiece]; ++pieceNumber) {
            square = pos->pieceList[tempPiece][pieceNumber];
            ASSERT(pos->pieces[square] == tempPiece);
        }
    }

   // count the actual number of pieces...
    for (square64 = 0; square64 < 64; ++square64) {
        square = SQ120(square64);
        tempPiece = pos->pieces[square];
        tempNumOfPieces[tempPiece]++;
        colour = pieceCol[tempPiece];

        if (isPieceMin[tempPiece] == true)
            tempMinPieces[colour]++;
        if (isPieceMaj[tempPiece] == true)
            tempMajPieces[colour]++;
        if (isPieceBig[tempPiece] == true)
            tempBigPieces[colour]++;

        tempMaterial[colour] += pieceVal[tempPiece];
    }

    // ...and compare with the position!
    for (int i = 1; i < 13; ++i) {
        ASSERT(tempNumOfPieces[i] == pos->numOfPieces[i]);
    }

    // check pawn count
    pawnCount = countSetBits(tempPawns[WHITE]);
    ASSERT(pawnCount == pos->numOfPieces[P]);
    pawnCount = countSetBits(tempPawns[BLACK]);
    ASSERT(pawnCount == pos->numOfPieces[p]);
    pawnCount = countSetBits(tempPawns[BOTH]);
    ASSERT(pawnCount == pos->numOfPieces[P] + pos->numOfPieces[p]);

    // check pawns' position on bitboards
    while (tempPawns[WHITE]) {
        square64 = popBit(&tempPawns[WHITE]);
        ASSERT(pos->pieces[SQ120(square64)] == P);
    }
    while (tempPawns[BLACK]) {
        square64 = popBit(&tempPawns[BLACK]);
        ASSERT(pos->pieces[SQ120(square64)] == p);
    }
    while (tempPawns[BOTH]) {
        square64 = popBit(&tempPawns[BOTH]);
        ASSERT(pos->pieces[SQ120(square64)] == P || pos->pieces[SQ120(square64)] == p);
    }

    // check material
    ASSERT(tempMaterial[WHITE] == pos->material[WHITE] && tempMaterial[BLACK] == pos->material[BLACK]);
    ASSERT(tempMinPieces[WHITE] == pos->minPieces[WHITE] && tempMinPieces[BLACK] == pos->minPieces[BLACK]);
    ASSERT(tempBigPieces[WHITE] == pos->bigPieces[WHITE] && tempBigPieces[BLACK] == pos->bigPieces[BLACK]);
    ASSERT(tempMajPieces[WHITE] == pos->majPieces[WHITE] && tempMajPieces[BLACK] == pos->majPieces[BLACK]);


    // check the rest:
    // side to move
    ASSERT(!(pos->sideToMove == WHITE) != !(pos->sideToMove == BLACK));



    // en passant square
    ASSERT((pos->enPassant == SQ_NONE) ||
            ((boardRanks[pos->enPassant] == RANK_6 && pos->sideToMove == WHITE)||
            (boardRanks[pos->enPassant] == RANK_3 && pos->sideToMove == BLACK)));

    // king position
    ASSERT(pos->pieces[pos->kingSquare[WHITE]] == K);
    ASSERT(pos->pieces[pos->kingSquare[BLACK]] == k);

    // position key
    ASSERT(generatePositionKey(pos) == pos->posKey);

    return 0;
}

char* printSquare (int sq) {

    static char sqString[3];

    int file = boardFiles[sq];
    int rank = boardRanks[sq];

    sprintf(sqString, "%c%c", ('a' + file), ('1' + rank));

    return sqString;
}