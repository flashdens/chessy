#include <stdio.h>
#include <stdlib.h>

#include "init.h"
#include "enums.h"
#include "board.h"
#include "bitboards.h"
#include "utils.h"

int main() {
    initAll();

    U64 piece = generateRandomU64();
    U64 piece2 = generateRandomU64();

    printf("Piece 1: %llx \n", piece);
    printf("Piece 2: %llx \n", piece2);

    int key = piece ^ piece2;
    int temp = piece;
    printf("%d\n",temp);
    temp ^= piece2;
    printf("%d\n",temp);
    temp ^= piece2;
    printf("%d\n",temp);
    temp ^= piece2;
    printf("%d\n",key);
    printf("it works!");
    return 0;
}
