#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>

#include "perfthub.h"
#include "milochess.h"

#define S_FLAG (1 << 0)
#define H_FLAG (1 << 1)
#define L_FLAG (1 << 2)
#define E_FLAG (1 << 3)
#define F_FLAG (1 << 4)
#define D_FLAG (1 << 5)
#define T_FLAG (1 << 6)

/**
 * @brief utility function to download input for perfthub from a server.
 *
 * TODO: pass an url to download from and ensure it's safe
 *
 * @return 0 on success
 * @return 1 on failure alongside relevant information
 */
int getInput () {

    printf("perft.txt not found. do you wish to download it (y/n)?\n");
    char choice;
    scanf(" %c", &choice);
    clearStdin();

    if (choice != 'y' && choice != 'Y') {
        printf("file download rejected. exiting perfthub...\n");
        return EXIT_FAILURE;
    }

    int result;
    char command[90] = "wget --no-check-certificate https://wierzba.wzks.uj.edu.pl/~21_bogacz/milochess/perft.txt";

    result = system(command);
    printf("%s\n", command);

    if (result == 0) {
        printf("perft.txt downloaded successfully\n");
        return 0;
    }
    else {
        printf("failed to download perft.txt. exiting perfthub...\n");
        return EXIT_FAILURE;
    }
}

/**
 * @brief utility function to clear stdin.
 *
 * @return void
 */
void clearStdin () {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief print help regarding perfthub.
 *
 * @return void
 */
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
           "write error logs to stdout alongside the files, therefore not printing information about test starts to stdout.\n\n"

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
 * @param argv (**char) argument array
 *
 * @see printHelp() for more information
 *
 * @return 0 on success
 * @return 1 on failure, alongside relevant information
 */
int perfthub (int argc, char **argv) {

    int flags = 0;
    int argFiles = 7;
    int argDepth = 0;
    int argTests = 0;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--skip") == 0 ) {
            flags |= S_FLAG;
        }

        else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0 ) {
            flags |= H_FLAG;
            printHelp();
            if (argc == 2)
                return EXIT_SUCCESS;
        }

        else if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--loose") == 0) {
            flags |= L_FLAG;
        }

        else if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--error-to-stdout") == 0) {
            flags |= E_FLAG;
        }

        else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--files") == 0 && i + 1 < argc) {
            i++;
            char *endptr;
            long int val = strtol(argv[i], &endptr, 10);

            if (*endptr == '\0' && val > 0 && val < 8) {
                argFiles = (int) val;
                flags |= F_FLAG;
            }
            else {
                printf("invaild argument passed! see phub -h for help\n");
                return EXIT_FAILURE;
            }
        }

        else if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--depth") == 0 && i + 1 < argc) {
            i++;
            char *endptr;
            long int val = strtol(argv[i], &endptr, 10);

            if (*endptr == '\0' && val > 0 && val < 8) {
                argDepth = (int) val;
                flags |= D_FLAG;

            }
            else {
                printf("invaild argument passed! see phub -h for help\n");
                return EXIT_FAILURE;
            }
        }

        else if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--tests") == 0 && i + 1 < argc) {
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

    char subDirName[29] = "perfthub/";
    strncat(subDirName, date, 19);

    struct stat st;

    if (stat("perfthub", &st) != 0 || !S_ISDIR(st.st_mode))
        if (mkdir("perfthub", 0755) != 0) {
            printf("error creating the perfthub directory\n");
            return EXIT_FAILURE;
        }

    if (mkdir(subDirName, 0755) != 0) {
        printf("error creating the test subdirectory\n");
        return EXIT_FAILURE;
    }

    char infoFilename[62];
    char errorFilename[68];
    char fullFilename[67];

    snprintf(infoFilename, 29, "%s", subDirName);
    snprintf(infoFilename + 28, 34, "/perfthub_%s", date);

    snprintf(errorFilename, 29, "%s", subDirName);
    snprintf(errorFilename + 28, 40, "/perfthub_error_%s", date);

    snprintf(fullFilename, 29, "%s", subDirName);
    snprintf(fullFilename + 28, 39, "/perfthub_full_%s", date);

    FILE* input = fopen("perft.txt", "r");

    FILE *fInfo = NULL;
    FILE *fError = NULL;
    FILE *fFull = NULL;

    if (argFiles < 0 || argFiles > 7) {
        printf("error processing file arguments, see phub -h for help\n");
        return EXIT_FAILURE;
    }

    if (argFiles - 4 >= 0) {
        fInfo = fopen(infoFilename, "w+"); // TODO fopen returns null and filenames double
        argFiles -= 4;
    }

    if (argFiles - 2 >= 0) {
        fError = fopen(errorFilename, "w+");
        argFiles -= 2;
    }

    if (argFiles - 1 == 0) {
        fFull = fopen(fullFilename, "w+");
        argFiles -= 1;
    }

    if (!input && getInput() != 0) {
        if (fInfo)  fclose(fInfo);
        if (fError)  fclose(fError);
        if (fFull)  fclose(fFull);
        return EXIT_FAILURE;
    }

    input = fopen("perft.txt", "r");

    int lines = 0;
    int maxDepth = argDepth;
    int tests = argTests;
    char buf[256];

    while (fgets(buf, sizeof(buf), input) != NULL && !(flags & T_FLAG)) {
        if (buf[0] != '#')
            lines++;
    }
    fseek(input, 0, SEEK_SET);

    while (!(flags & D_FLAG)) {
        printf("please provide the depth of the test (1-7)\n");
        scanf(" %d", &maxDepth);

        if (maxDepth < 1 || maxDepth > 7) {
            printf("please provide a valid number\n");
            clearStdin();
        }
        else {
            break;
        }
    }

    while (!(flags & T_FLAG) || tests > lines) {
        char dBuf[5];
        clearStdin();
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

    printf("Starting a session of %d tests with depth %d\n\n", tests, maxDepth);
    if (fInfo) {
        fprintf(fInfo, "---PERFTHUB SHORT TEST LOG---\nDATE: %.19s\nNUMBER OF POSITIONS: %d\nDEPTH: %d\nCALLED WITH: ",
                date, tests, maxDepth);
        for (int i = 1; i < argc; ++i) { fprintf(fInfo, "%s ", argv[i]); } fprintf(fInfo, "\n\n");
    }
    if (fError) {
        fprintf(fError, "---PERFTHUB ERROR TEST LOG---\nDATE: %.19s\nNUMBER OF POSITIONS: %d\nDEPTH: %d\nCALLED WITH: ",
                date, tests, maxDepth);
        for (int i = 1; i < argc; ++i) { fprintf(fError, "%s ", argv[i]); } fprintf(fError, "\n\n");
    }
    if (fFull) {
        fprintf(fFull, "---PERFTHUB FULL TEST LOG---\nDATE: %.19s\nNUMBER OF POSITIONS: %d\nDEPTH: %d\nCALLED WITH: ",
                date, tests, maxDepth);
        for (int i = 1; i < argc; ++i) { fprintf(fFull, "%s ", argv[i]);} fprintf(fFull, "\n\n");
    }

    BOARD board[1];
    time_t totalStart = clock();
    time_t totalEnd;

    int failedTests = 0;
    int totalTests = 0;

    for (int i = 0; i < tests; ++i) {
        U64 expectedValues[13];
        fgets(buf, sizeof(buf), input);

        // comment detected
        if (buf[0] == '#') {
            i--;
            continue;
        }

        char *token = strtok(buf, ",");
        char *fen = token;

        if (parseFen(fen, board) != 0) {
            if (fInfo)  fclose(fInfo);
            if (fError)  fclose(fError);
            if (fFull)  fclose(fFull);
        }

        token = strtok(NULL, "");
        token = strtok(token, ",");

        if (!(flags & L_FLAG)) {
            for (int j = 1; token != NULL && j <= maxDepth; ++j) {
                expectedValues[j] = strtoull(token, NULL, 10);
                token = strtok(NULL, ",");
            }
        }

        if (!(flags & E_FLAG)) printf("Starting perft test for %s depth %d\n\n", fen, maxDepth);

        for (int currentDepth = 1; currentDepth <= maxDepth; ++currentDepth) {
            clock_t testStart;
            clock_t testEnd;
            U64 result;

            if (fFull) fprintf(fFull, "Starting perft test for %s with depth %d, expecting %llu leaf nodes\n\n", \
            fen, currentDepth, expectedValues[currentDepth]);

            testStart = clock();
            result = perftTest(board, currentDepth, fFull);
            testEnd = clock();
            totalTests++;

            if (result != expectedValues[currentDepth] && !(flags & L_FLAG)) {
                failedTests++;

                if (fError) {
                    fprintf(fError,
                            "error: perft test failed in %ld s for\n%s\ndepth %d: expected %llu leaf nodes, got %llu\n\n",
                            ((testEnd - testStart)) / CLOCKS_PER_SEC, fen, currentDepth,
                            expectedValues[currentDepth], result);
                }

                if (fFull) {
                    fprintf(fFull,
                            "\nerror: perft test failed in %ld s for\n%s\ndepth %d: expected %llu leaf nodes, got %llu\n\n",
                            ((testEnd - testStart)) / CLOCKS_PER_SEC, fen, currentDepth,
                            expectedValues[currentDepth], result);
                }

                if (flags & E_FLAG)
                    printf("error: perft test failed in %ld s for\n%s\ndepth %d: expected %llu leaf nodes, got %llu\n\n",
                           (testEnd - testStart) / CLOCKS_PER_SEC, fen, currentDepth, expectedValues[currentDepth], result);
            }

            else if (result == expectedValues[currentDepth]){
                if (fFull) {
                    fprintf(fFull, "\nsuccess: perft test passed in %ld s for\n%s\ndepth %d, got %llu\n\n",
                            (testEnd - testStart) / CLOCKS_PER_SEC, fen, currentDepth, result);
                }
            }

            else if (flags & L_FLAG) {
                if (fFull) {
                    fprintf(fFull, "\ninfo: perft test ended in %ld seconds for\n%s\ndepth %d: got %llu leaf nodes\n\n",
                            (testEnd - testStart) / CLOCKS_PER_SEC, fen, currentDepth, result);

                }
            }
        }
        resetBoard(board);
    }

    totalEnd = clock();

    if (fInfo) {
    fprintf(fInfo, "ALL TESTS COMPLETE\n\nTOTAL: %d\nPASSED: %d\nFAILED: %d\nACCURACY: %3f%%\nTOTAL TIME ELAPSED: %ld s\n",
            totalTests, totalTests - failedTests, failedTests, (float) (totalTests - failedTests) * 100 / (float) totalTests, ((totalEnd - totalStart)) / CLOCKS_PER_SEC);
    }

    if (fError) {
        if (failedTests == 0) fprintf(fError, "NO ERRORS FOUND\n\n");
    fprintf(fError, "ALL TESTS COMPLETE\n\nTOTAL: %d\nPASSED: %d\nFAILED: %d\nACCURACY: %3f%%\nTOTAL TIME ELAPSED: %ld s\n",
            totalTests, totalTests - failedTests, failedTests, (float) (totalTests - failedTests) * 100 / (float) totalTests, ((totalEnd - totalStart)) / CLOCKS_PER_SEC);
    }

    if (fFull) {
    fprintf(fFull, "ALL TESTS COMPLETE\n\nTOTAL: %d\nPASSED: %d\nFAILED: %d\nACCURACY: %3f%%\nTOTAL TIME ELAPSED: %ld s\n",
            totalTests, totalTests - failedTests, failedTests, (float) (totalTests - failedTests) * 100 / (float) totalTests, ((totalEnd - totalStart)) / CLOCKS_PER_SEC);
    }

    printf("tests finished.\n");
    printf("see %s/%s for results\n", (getcwd(buf, sizeof(buf))), subDirName);

    if (failedTests == 0 && !(flags & L_FLAG)) {
        if (fInfo) fprintf(fInfo, "all tests passed, congrats!\n");
        if (fError) fprintf(fError, "all tests passed, congrats!\n");
        if (fFull) fprintf(fFull, "all tests passed, congrats!\n");
        printf("by the way, all passed! congrats!\n");
    }

    if (fInfo)  fclose(fInfo);
    if (fError)  fclose(fError);
    if (fFull)  fclose(fFull);

    return EXIT_SUCCESS;
}