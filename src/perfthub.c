#include <stdio.h>
#include <string.h>
#include <time.h>

#include "perfthub.h"
#include "perft.h"

int getInput () {

    printf("perft.txt not found. do you wish to download it (y/n)?\n");

    char choice;
    scanf(" %c", &choice);

    if (choice != 'y' && choice != 'Y') {
        printf("file download rejected. exiting perfthub...\n");
        return 1;
    }

    int result;
    char command[100] = "wget ";
    const char *url = "https://wierzba.wzks.uj.edu.pl/~21_bogacz/milochess/perft.txt";

    strncat(command, url, strlen(url));
    result = system(command);
    printf("%s\n", command);

    if (result == 0) {
        printf("perft.txt downloaded successfully\n");
    }
    else {
        printf("failed to download perft.txt. exiting perfthub...");
        return 1;
    }

    return 0;
}

/**
 *
 * @brief perft-test against a set of results stored in a text file.
 *
 * @param argc argument count
 * @param argv arguments
 *
 * @return 0 on success
 * @return 1 on failure, alongside relevant information
 */
int perftHub (int argc, int **argv) {

    char buf[256];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    strftime(buf, 33, "perfthub_%d-%m-%Y_%H_%M_%S.log", t);
    FILE* input = fopen("perft.txt", "r");
    FILE* output = fopen(buf, "w+");

    printf("welcome to perfthub!\nenter a command below or type help for help\n");

    if (!input && !getInput())
        return 1;

    int depth;

    printf("please provide the depth of the test (2-7)\n");
    while (1) {
        scanf(" %d", &depth);

        if (depth < 2 || depth > 7) {
            printf("please provide a valid number\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF); // clear stdin
        }
        else {
            break;
        }
    }

    int lines = 0;


    while (fgets(buf, sizeof(buf), input) != NULL) {
        lines++;
    }

    rewind(input);

    BOARD board[1];
    char *token = strtok(buf, ",");
    char *fen = token;
    parseFen(fen, board);
    token = strtok(NULL, "");
    token = strtok(token, ",");
    int perftValues[13];
    for (int i = 0; token != NULL && i < depth; ++i) {
        perftValues[i + 1] = atoi(token);
        printf("%d\n", perftValues[i]);
        token = strtok(NULL, ",");
    }

//    for (int i = 2; i < depth; ++i) {
//        if (perftTest(board, i) == perftValues[i])
//    }

    return 0;
}