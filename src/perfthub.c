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
        printf("failed to download perft.txt. exiting perfthub...\n");
        return EXIT_FAILURE;
    }

    return 0;
}

void clearStdin () {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void printHelp () {
    printf("PERFTHUB\n\n"

           "perfthub is a tool that lets you perft test the milochess chess engine. you can use flags to modify its behaviour.\n\n"

           "by default, 3 .log files are generated for each test run:\n"
           "- perfthub_info -  basic information about the test (4)\n"
           "- perfthub_error -  detailed information about failed tests (2)\n"
           "- perfthub_full -  all information about each test (1)\n\n"

           "they are stored in {milochess_executable_path}/perfthub/{test_time} directories."
           "(the perfthub directory is created if it doesn't exist under the current path, test run directories are created dynamically).\n\n"

           "perfthub requires you to provide \"perft.txt\" in the exe path, which includes the FEN positions alongside expected values.\n"
           "if you don't have the file present, perfthub will download it for you from https://wierzba.wzks.uj.edu.pl/~21_bogacz/milochess/perft.txt.\n"
           "you can also look up the link as a reference to how the file should look like (if you want only fens to be parsed, look up the -l flag).\n\n"

           "perfthub started with no flags will first handle perft.txt, then ask for test depth and amount, afterwards proceeding with the tests.\n\n"

           "OPTIONS\n\n"

           "WITHOUT ARGUMENTS\n\n"

           "-h, --help\n"
           "print help (this very document).\n\n"

           "-l, --loose\n"
           "omit testing against expected values, outputting the results the files anyway. be sure to pass the flag if your perft.txt file doesn't include expected values of the test to avoid errors\n\n"

           "-e --error-to-stdout\n"
           "write error logs to stdout instead of a file\n\n"

           "WITH ARGUMENTS\n\n"

           "-f --files (0-7)\n"
           "specify which log files to generate after the flag. each file has a numeric value (see above) which lets you choose the files in the chmod manner.\n"
           "for example, 0 means generate no log files, 4 means generate only perfthub_info, 7 means generate all (which is the default option).\n\n"

           "-d, --depth (2-7)\n"
           "pass the maximum depth of the test after the flag, skipping being prompted to do so later.\n\n"

           "-t, --tests (0-num of lines of perft.txt)\n"
           "pass the amount of positions to be tested after the flag, skipping being prompted to do so later.\n"
           "first x positions from the file will be tested.\n\n"
           "EXAMPLE USAGE\n"
           "\n");
}

/**
 *
 * @brief perft-test against a set of results stored in a text file.
 *
 * @param argc argument count
 * @param argv arguments
 *
 *
 * @return 0 on success
 * @return 1 on failure, alongside relevant information
 */
int perfthub (int argc, char **argv) {

    int flags = 0;
    int argFileValue = 7;
    int argDepth = 0;
    int argTests = 0;

    for (int i = 1; i < argc; ++i) {
        if (strncmp(argv[i], "-s", 2) == 0 || strncmp(argv[i], "--skip", 6) == 0 ) {
            flags |= S_FLAG;
        }

        else if (strncmp(argv[i], "-h", 2) == 0 || strncmp(argv[i], "--help", 6) == 0 ) {
            flags |= H_FLAG;
            printHelp();
            if (argc == 2)
                return EXIT_SUCCESS;
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

    char choice;
    while (!(flags & S_FLAG)) {
        printf("welcome to perfthub!\n"
               "press enter to proceed\n"
               "h to print help\n"
               "q to quit\n");

        choice = (char) fgetc(stdin);

        if (strncmp(&choice, "\n", 1) == 0) {
            break;
        }
        if (strncmp(&choice, "h", 1) == 0) {
            printHelp();
            clearStdin();
            continue;
        }
        else if (strncmp(&choice, "q", 1) == 0) {
            printf("exiting...\n");
            return EXIT_SUCCESS;
        }
        else {
            printf("please provide a valid option\n");
            clearStdin();
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

    snprintf(infoFilename, 29, "%s", subDirName);
    snprintf(infoFilename + 28, 29, "/perfthub_%s", date);

    snprintf(errorFilename, 29, "%s", subDirName);
    snprintf(errorFilename + 28, 29, "/perfthub_error_%s", date);

    snprintf(fullFilename, 29, "%s", subDirName);
    snprintf(fullFilename + 28, 29, "/perfthub_full_%s", date);

    FILE* input = fopen("perft.txt", "r");

        FILE *info = NULL;
        FILE *error = NULL;
        FILE *full = NULL;

        if ((argFileValue - 4) > 0) {
            info = fopen(strncat(infoFilename, date, 24), "w+");
            argFileValue -= 4;
        }
        if ((argFileValue - 2) > 0) {
            error = fopen(strncat(errorFilename, date, 24), "w+");
            argFileValue -= 2;
        }
        if (argFileValue - 1 == 0) {
            full = fopen(strncat(fullFilename, date, 24), "w+");
            argFileValue -= 1;
        }
        if (argFileValue != 0) {
            printf("error processing file arguments\n");
            return EXIT_FAILURE;
        }

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

    while (!(flags & T_FLAG) || tests > lines) {
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
    time_t totalEnd;

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

    totalEnd = clock();

    fprintf(info, "ALL TESTS COMPLETE\n\nTOTAL: %d\nPASSED: %d\nFAILED: %d\nACCURACY: %3f%%\nTOTAL TIME ELAPSED: %fs\n",
            totalTests, totalTests - failedTests, failedTests, (float) (totalTests - failedTests) * 100 / (float) totalTests, (double) ((totalEnd - totalStart)) / CLOCKS_PER_SEC);
    fprintf(error, "ALL TESTS COMPLETE\n\nTOTAL: %d\nPASSED: %d\nFAILED: %d\nACCURACY: %3f%%\nTOTAL TIME ELAPSED: %fs\n",
            totalTests, totalTests - failedTests, failedTests, (float) (totalTests - failedTests) / (float) totalTests, (double) ((totalEnd - totalStart)) / CLOCKS_PER_SEC);
    fprintf(full, "ALL TESTS COMPLETE\n\nTOTAL: %d\nPASSED: %d\nFAILED: %d\nACCURACY: %3f%%\nTOTAL TIME ELAPSED: %fs\n",
            totalTests, totalTests - failedTests, failedTests, (float) (totalTests - failedTests) / (float) totalTests, (double) ((totalEnd - totalStart)) / CLOCKS_PER_SEC);

    if (failedTests == 0) {
        fprintf(info, "all tests passed, congrats!\n");
        fprintf(error, "all tests passed, congrats!\n");
        fprintf(full, "all tests passed, congrats!\n");
    }

    return EXIT_SUCCESS;
}