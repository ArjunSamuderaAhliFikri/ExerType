#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

void showOpening() {
    printf(" ______   __   __   ______   ______   ______   ______   ______    \n");
    printf("/\\  __ \\/\\ \"-.\\ \\ /\\  ___\\ /\\  == \\\\ /\\  ___\\ /\\  ___\\ /\\  == \\   \n");
    printf("\\ \\  __< \\ \\ \\-.  \\\\ \\  __\\\\ \\  __< \\ \\  __\\\\ \\ \\___  \\\\ \\  __<   \n");
    printf(" \\ \\_\\ \\_\\\\ \\_\\\\\"\\_\\\\ \\_____\\\\ \\_\\ \\_\\\\ \\_____\\\\/\\_____\\\\ \\_\\ \\_\\ \n");
    printf("  \\/_/ /_/ \\/_/ \\/_/ \\/_____/ \\/_/ /_/ \\/_____/ \\/_____/ \\/_/ /_/ \n");
    printf("\n");
    printf("                          E   X   E   R   T   Y   P   E\n");
    printf("                     Improve your accuracy and typing speed\n\n");
}

const char* getRandomSentence() {
    static const char* options[5] = {
        "the quick brown fox jumps over the lazy dog and keeps running until sunset above the hills",
        "coding in the terminal can be fun especially when building small applications like typing test tools",
        "practice makes perfect and typing speed will improve as long as you keep training every single day",
        "computer science teaches logic problem solving creativity and critical thinking for everyday challenges",
        "learning the c programming language gives you deep understanding about memory pointers and performance"
    };

    srand(time(NULL));
    return options[rand() % 5];
}

void exerTypeApp() {
    showOpening();

    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    INPUT_RECORD inputRecord;
    DWORD eventsRead;

    const char* sampleText = getRandomSentence();

    int sampleTextLength = strlen(sampleText);

    printf("===========================================================\n");
    printf("Press Esc Key to Exit the Application!\n");
    printf("\033[33mPlease press '.' to finish typing and display the result.\033[0m\n");
    printf("===========================================================\n\n");

    printf("\033[34m%s\033[0m\n", sampleText);

    int isWordFalse = 0;
    int isWordTrue = 0;

    char input[1000] = {0};
    int index = 0;

    clock_t startTimer = 0, endTimer;
    bool started = false;

    while (true) {
        ReadConsoleInput(hInput, &inputRecord, 1, &eventsRead);

        if (inputRecord.EventType == KEY_EVENT && inputRecord.Event.KeyEvent.bKeyDown) {

            char c = inputRecord.Event.KeyEvent.uChar.AsciiChar;

            if (!started && c >= 32 && c <= 126) {
                startTimer = clock();
                started = true;
            }

            if (c == '.' || c == 27) {
                printf("\nCalculate Result...\n");
                break;
            }

            if (c == 8 && index > 0) {
                index--;
                
                input[index] = '\0';
                printf("\b \b");
                continue;
            }

            // Normal input
            if (c >= 32 && c <= 126) {
                if (c == sampleText[index]) {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    isWordTrue++;
                } else {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    isWordFalse++;
                }

                input[index++] = c;
                printf("%c", c);

                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
        }
    }

    endTimer = clock();

    double timeTaken = (double)(endTimer - startTimer) / CLOCKS_PER_SEC;
    int totalCharacter = strlen(input);

    int wordPerMinute = (totalCharacter / 5.0) / (timeTaken / 60.0);

    if(wordPerMinute == 0) {
        timeTaken = 0;
    }

    printf("=============================================================\n");
    printf("| %-20s | %-30s |\n", "Complete : ", input);
    printf("| %-20s | %-30d |\n", "Word Per Minute", wordPerMinute);
    printf("| %-20s | %-30d |\n", "Letters Correct", isWordTrue);
    printf("| %-20s | %-30d |\n", "Wrong Letters", isWordFalse);
    printf("| %-20s | %-30.2f |\n", "Time (Seconds)", timeTaken);
    printf("=============================================================\n\n");
}

int main() {
    exerTypeApp();
    return 0;
}
