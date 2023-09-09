#include <stdlib.h>

#include "pvtable.h"

PVTABLE* newPVTable () {
    PVTABLE *table = malloc(sizeof(PVTABLE));
    table->size = 64;
    table->itemsNum = 0;
    table->items = calloc((size_t)table->size, sizeof(PVENTRY));
    return table;
}