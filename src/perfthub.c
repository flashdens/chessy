#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "perfthub.h"
#include "perft.h"
#include "board.h"

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

void clearStdin () {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
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

    char date[24];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(date, 24, "%d-%m-%Y_%H:%M:%S.log", t);

    char subDirName[256] = "perfthub/";
    strncat(subDirName, date, 19);

    struct stat st;

    if (stat("perfthub", &st) != 0 || !S_ISDIR(st.st_mode))
        if (mkdir("perfthub", 0755) != 0) {
            printf("error creating the perfthub directory\n");
            return 1;
        }


    printf("%s\n", subDirName);
    if (mkdir(subDirName, 0755) != 0) {
        printf("error creating the perfthub subdirectory\n");
        return 1;
    }

    char infoFilename[256];
    snprintf(infoFilename, sizeof(infoFilename), "%s", subDirName);
    snprintf(infoFilename + 28, sizeof(infoFilename), "/perfthub_%s", date);
    char errorFilename[256];
    snprintf(errorFilename, sizeof(infoFilename), "%s", subDirName);
    snprintf(errorFilename + 28, sizeof(infoFilename), "/perfthub_error_%s", date);
    char fullFilename[256];
    snprintf(fullFilename, sizeof(infoFilename), "%s", subDirName);
    snprintf(fullFilename + 28, sizeof(infoFilename), "/perfthub_full_%s", date);

    printf("%s\n", infoFilename);
    printf("%s\n", errorFilename);
    printf("%s\n", fullFilename);

    FILE* input = fopen("perft.txt", "r");
    FILE* info = fopen(strncat(infoFilename, date, 24), "w+");
    FILE* error = fopen(strncat(errorFilename, date, 24), "w+");
    FILE* full = fopen(strncat(fullFilename, date, 24), "w+");

    printf("welcome to perfthub!\nenter a command below or type help for help\n");

    if (!input && getInput() != 0)
        return 1;

    int lines = 0;
    int depth;
    char hehe[5];
    int tests;
    char buf[256];

    while (fgets(buf, sizeof(buf), input) != NULL) {
        lines++;
    }
    rewind(input);

    while (1) {
        printf("please provide the depth of the test (2-7)\n");
        scanf(" %d", &depth);

        if (depth < 2 || depth > 7) {
            printf("please provide a valid number\n");
            clearStdin();
        }
        else {
            break;
        }
    }
    clearStdin();

    while (1) {
        printf("how many positions do you want to test against? (max %d, leave empty to test for that amount)\n", lines);
        fgets(hehe, 5, stdin);

        if (atoi(hehe) < 0 || atoi(hehe) > lines) {
            printf("please provide a valid number\n");
            clearStdin();
        }
        else if (strcmp(hehe, "\n") == 0) {
            tests = lines;
            break;
        }
        else {
            tests = atoi(hehe);
            break;
        }
    }

    fprintf(info, "---PERFTHUB TEST LOG---\nDATE: %.19s\nAMOUNT OF TESTS: %d\nDEPTH: %d\n\n",
            date, tests, depth);
    fprintf(error, "---PERFTHUB TEST LOG---\nDATE: %.19s\nAMOUNT OF TESTS: %d\nDEPTH: %d\n\n",
            date, tests, depth);
    fprintf(full, "---PERFTHUB TEST LOG---\nDATE: %.19s\nAMOUNT OF TESTS: %d\nDEPTH: %d\n\n",
            date, tests, depth);

    BOARD board[1];
    int failed = 0;

    for (int i = 0; i < tests; ++i) {
        U64 expectedValues[13];
        char *token = strtok(buf, ",");
        char *fen = token;

        parseFen(fen, board);

        token = strtok(NULL, "");
        token = strtok(token, ",");

        for (int j = 0; token != NULL && j < depth; ++j) {
            expectedValues[j + 1] = strtoull(token, NULL, 10);
            token = strtok(NULL, ",");
        }

        for (int j = 2; j < depth; ++j) {
            U64 result = perftTest(board, j);

            if (result != expectedValues[j]) {
                fprintf(error, "error: perft test failed for\n%s\nwith depth %d: expected %llu leaf nodes, got %llu\n\n",
                        fen, depth, expectedValues[j], result);
                failed++;
            }
        }

        resetBoard(board);
        fgets(buf, sizeof(buf), input);
    }

    if (failed == 0)
        fprintf(error, "all tests passed, congrats!\n");

    return 0;
}