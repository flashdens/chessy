//
// Created by miloszek on 3/19/24.
//

#include "enums.h"
#include "globals.h"

#ifndef MILOCHESS_MOVEORDER_H
#define MILOCHESS_MOVEORDER_H

const int victimScore[13] = {0, 100, 200, 300, 400, 500, 600, 100, 200, 300, 400, 500, 600};
static int vScores[13][13];
/**
 * MVV-LVA - Most Valuable Victim - Least Valuable Attacker,
 * i shorten all the names regarding this to V, since the acronym is super ugly
 * @brief initialize the MVVLVA arrays

 * @return void
 */
void initV () {
    for (int attacker = P; attacker < k; ++attacker) {
        for (int victim = P; victim < k; ++victim) {
            vScores[victim][attacker] = victimScore[victim] + 6 - (victimScore[attacker] / 100);
        }
    }

    for (int victim = P; victim <= k; ++victim) {
        for (int attacker = P; attacker <= k; ++attacker) {
            printf("%c x %c = %d\n", pieceChar[attacker], pieceChar[victim], vScores[victim][attacker]);
        }
    }
}
#endif //MILOCHESS_MOVEORDER_H
