#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int CheckEmptyOrNullInput(const char* input)
{
    if (strcmp(input, "") == 0 || strcmp(input, "0") == 0) {
        return 0;
    }
}


void replaceNewlineWithDelimiter(char* modifiedInput, char* delimiter)
{
    // Replace newline characters with the delimiter
    for (int i = 0; modifiedInput[i]; i++) {
        if (modifiedInput[i] == '\n') {
            modifiedInput[i] = *delimiter;
        }
    }
}

char* getModifiedInput(const char* input, char* delimiter) {
    char* modifiedInput = strdup(input);
    *delimiter = ','; // Default delimiter

    if (strncmp(modifiedInput, "//", 2) == 0) {
        // Custom delimiter found
        *delimiter = modifiedInput[2];
        modifiedInput = modifiedInput + 4; // Skip the delimiter part (e.g., "//;\n")
    }

    replaceNewlineWithDelimiter(modifiedInput, delimiter);

    return modifiedInput;
}

int processToken(char* token) {
    int num = atoi(token);

    if (num < 0) {
        printf("Negatives not allowed: %d\n", num);
        return -1;  // Handle negative numbers
    }

    if (num <= 1000) {
        return num;
    }

    return 0;
}

int add(const char* input) {
    CheckEmptyOrNullInput(input);
    
    char delimiter;
    char* modifiedInput = getModifiedInput(input, &delimiter);

    int sum = 0;
    char* token = strtok(modifiedInput, &delimiter);
    
    while (token != NULL) {
        int num = processToken(token);
        if (num == -1) {
            return -1;  // Return immediately on encountering a negative number
        }
        sum += num;
        token = strtok(NULL, &delimiter);
    }

    return sum;
}
