#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

#include "perfthub.h"
#include "perft.h"
#include "board.h"

int getInput () {
    printf("perft.txt not found. do you wish to download it (y/n)?\n");

    char choice;
    scanf(" %c", &choice);

    if (choice != 'y' && choice != 'Y') {
        printf("file download rejected. exiting perfthub...\n");
        return EXIT_FAILURE;
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
        return EXIT_FAILURE;
    }

    return 0;
}

void clearStdin () {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void printHelp () {
    printf("help\n");
}

/**
 *
 * @brief perft-test against a set of results stored in a text file.
 *
 * @param argc argument count
 * @param argv arguments
 *
 * @return 0 on success
 * @return EXIT_FAILURE on failure, alongside relevant information
 */
int perftHub (int argc, char **argv) {

    int flags = 0;
    int argFileValue = 0;
    int argDepth = 0;
    int argTests = 0;

    for (int i = 1; i < argc; ++i) {
        if (strncmp(argv[i], "-h", 2) == 0 || strncmp(argv[i], "--help", 6) == 0 ) {
            flags |= H_FLAG;
        }

        else if (strncmp(argv[i], "-l", 2) == 0 || strncmp(argv[i], "--loose", 7) == 0) {
            flags |= L_FLAG;
        }

        else if (strncmp(argv[i], "-e", 2) == 0 || strncmp(argv[i], "--error-to-stdout", 17) == 0) {
            flags |= E_FLAG;
        }

        else if (strncmp(argv[i], "-f", 2) == 0 || strncmp(argv[i], "--files", 7) == 0 && i + 1 < argc) {
            i++;
            char *endptr;
            long int val = strtol(argv[i], &endptr, 10);

            if (*endptr == '\0' && val > 0 && val < 8) {
                argFileValue = (int) val;
                flags |= F_FLAG;
            }
            else {
                printf("invaild argument passed! see phub -h for help\n");
                return EXIT_FAILURE;
            }
        }

        else if (strncmp(argv[i], "-d", 2) == 0 || strncmp(argv[i], "--depth", 7) == 0 && i + 1 < argc) {
            i++;
            char *endptr;
            long int val = strtol(argv[i], &endptr, 10);

            if (*endptr == '\0' && val > 1 && val < 8) {
                argDepth = (int) val;
                flags |= D_FLAG;

            }
            else {
                printf("invaild argument passed! see phub -h for help\n");
                return EXIT_FAILURE;
            }
        }

        else if (strncmp(argv[i], "-t", 2) == 0 || strncmp(argv[i], "--tests", 7) == 0 && i + 1 < argc) {
            i++;
            char *endptr;
            long int val = strtol(argv[i], &endptr, 10);

            if (*endptr == '\0' && val > 0) {
                argTests = (int) val;
                flags |= T_FLAG;
            }
            else {
                printf("invaild argument passed! see phub -h for help\n");
                return EXIT_FAILURE;
            }
        }

        else {
            printf("error processing command line arguments! see phub -h for help\n");
            return EXIT_FAILURE;
        }
    }

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
            return EXIT_FAILURE;
        }

    if (mkdir(subDirName, 0755) != 0) {
        printf("error creating the perfthub subdirectory\n");
        return EXIT_FAILURE;
    }

    char infoFilename[256];
    char errorFilename[256];
    char fullFilename[256];

    snprintf(infoFilename, sizeof(infoFilename), "%s", subDirName);
    snprintf(infoFilename + 28, sizeof(infoFilename), "/perfthub_%s", date);

    snprintf(errorFilename, sizeof(infoFilename), "%s", subDirName);
    snprintf(errorFilename + 28, sizeof(infoFilename), "/perfthub_error_%s", date);

    snprintf(fullFilename, sizeof(infoFilename), "%s", subDirName);
    snprintf(fullFilename + 28, sizeof(infoFilename), "/perfthub_full_%s", date);

    FILE* input = fopen("perft.txt", "r");

        FILE *info = fopen(strncat(infoFilename, date, 24), "w+");
        FILE *error = fopen(strncat(errorFilename, date, 24), "w+");
        FILE *full = fopen(strncat(fullFilename, date, 24), "w+");

        printf("welcome to perfthub!\nenter a command below or type help for help\n");

    if (!input && getInput() != 0)
        return EXIT_FAILURE;


    int lines = 0;
    int maxDepth = argDepth;
    int tests = argTests;
    char dBuf[5];
    char buf[256];

    while (fgets(buf, sizeof(buf), input) != NULL) {
        lines++;
    }
    rewind(input);

    while (1) {
        printf("please provide the depth of the test (2-7)\n");
        scanf(" %d", &maxDepth);

        if (maxDepth < 2 || maxDepth > 7) {
            printf("please provide a valid number\n");
            clearStdin();
        }
        else {
            break;
        }
    }
    clearStdin();

    while (!(flags & T_FLAG) && tests > lines) {
        printf("how many positions do you want to test against? (max %d, leave empty to test for that amount)\n", lines);
        fgets(dBuf, 5, stdin);

        if (atoi(dBuf) < 0 || atoi(dBuf) > lines) {
            printf("please provide a valid number\n");
            clearStdin();
        }
        else if (strcmp(dBuf, "\n") == 0) {
            tests = lines;
            break;
        }
        else {
            tests = atoi(dBuf);
            break;
        }
    }

    fprintf(info, "---PERFTHUB SHORT TEST LOG---\nDATE: %.19s\nAMOUNT OF TESTS: %d\nDEPTH: %d\n\n",
            date, tests, maxDepth);
    fprintf(error, "---PERFTHUB ERROR TEST LOG---\nDATE: %.19s\nAMOUNT OF TESTS: %d\nDEPTH: %d\n\n",
            date, tests, maxDepth);
    fprintf(full, "---PERFTHUB FULL TEST LOG---\nDATE: %.19s\nAMOUNT OF TESTS: %d\nDEPTH: %d\n\n---STARTING THE TEST---\n",
            date, tests, maxDepth);

    BOARD board[1];

    time_t totalStart = clock();

    int failedTests = 0;
    int totalTests = 0;

    for (int i = 0; i < tests; ++i) {
        U64 expectedValues[13];
        char *token = strtok(buf, ",");
        char *fen = token;

        parseFen(fen, board);

        token = strtok(NULL, "");
        token = strtok(token, ",");

        for (int j = 0; token != NULL && j < maxDepth; ++j) {
            expectedValues[j + 1] = strtoull(token, NULL, 10);
            token = strtok(NULL, ",");
        }

        for (int currentDepth = 2; currentDepth <= maxDepth; ++currentDepth) {
            clock_t testStart;
            clock_t testEnd;
            U64 result;

            fprintf(full, "Starting perft test for %s with depth %d\n\n", fen, currentDepth);
            printf("Starting perft test for %s depth %d\n\n", fen, currentDepth);

            testStart = clock();
            result = perftTest(board, currentDepth, full);
            testEnd = clock();

            if (result != expectedValues[currentDepth]) {
                fprintf(error, "error: perft test failed in %ldd for\n%s\ndepth %d: expected %llu leaf nodes, got %llu\n\n",
                        (long) testEnd - testStart / CLOCKS_PER_SEC, fen, currentDepth, expectedValues[currentDepth], result);
                fprintf(full, "error: perft test failed in %ldd for\n%s\ndepth %d: expected %llu leaf nodes, got %llu\n\n",
                         (long) testEnd - testStart / CLOCKS_PER_SEC, fen, currentDepth, expectedValues[currentDepth], result);
                failedTests++;
            }
            else {
                fprintf(full, "success: perft test passed for\n%s\ndepth %d, got %llu\n\n",
                        fen, maxDepth, result);
            }
            totalTests++;
        }

        resetBoard(board);
        fgets(buf, sizeof(buf), input);
    }


    fprintf(info, "ALL TESTS COMPLETE\n\nTOTAL: %d\nPASSED: %d\nFAILED: %d\nACCURACY: %3f%%\nTOTAL TIME ELAPSED: %fs",
            totalTests, totalTests - failedTests, failedTests, (float) (totalTests - failedTests) * 100 / (float) totalTests, (double) ((clock() - totalStart)) / CLOCKS_PER_SEC);
    fprintf(error, "ALL TESTS COMPLETE\n\nTOTAL: %d\nPASSED: %d\nFAILED: %d\nACCURACY: %3f%%\nTOTAL TIME ELAPSED: %fs",
            totalTests, totalTests - failedTests, failedTests, (float) (totalTests - failedTests) / (float) totalTests, (double) ((clock() - totalStart)) / CLOCKS_PER_SEC);
    fprintf(full, "ALL TESTS COMPLETE\n\nTOTAL: %d\nPASSED: %d\nFAILED: %d\nACCURACY: %3f%%\nTOTAL TIME ELAPSED: %fs",
            totalTests, totalTests - failedTests, failedTests, (float) (totalTests - failedTests) / (float) totalTests, (double) ((clock() - totalStart)) / CLOCKS_PER_SEC);

    if (failedTests == 0) {
        fprintf(info, "all tests passed, congrats!\n");
        fprintf(error, "all tests passed, congrats!\n");
        fprintf(full, "all tests passed, congrats!\n");
    } else

    return EXIT_SUCCESS;
}