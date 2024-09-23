#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int CheckEmptyOrNullInput(const char* input) {
    if (input == NULL || *input == '\0') {
        return 0; // Handle null or empty input
    }

    if (strcmp(input, "0") == 0) {
        return 0; // Return 0 for input "0"
    }

    return 1; // Valid input
}

char* setDelimiterAndGetModifiedInput(const char* input, char* delimiter) {
    *delimiter = ','; // Default delimiter

    if (strncmp(input, "//", 2) == 0) {
        *delimiter = input[2];  // Custom delimiter
        return strdup(input + 4);  // Skip "//;\n"
    }

    return strdup(input);  // No custom delimiter
}

void replaceNewlinesWithDelimiter(char* modifiedInput, char delimiter) {
    for (int i = 0; modifiedInput[i]; i++) {
        if (modifiedInput[i] == '\n') {
            modifiedInput[i] = delimiter;
        }
    }
}

int processToken(char* token) {
    int num = atoi(token);

    if (num < 0) {
        printf("Negatives not allowed: %d\n", num);
        return -1;
    }

    return (num <= 1000) ? num : 0;  // Ignore numbers > 1000
}

int add(const char* input) {
    if (!CheckEmptyOrNullInput(input)) {
        return 0;
    }

    char delimiter;
    char* modifiedInput = setDelimiterAndGetModifiedInput(input, &delimiter);
    replaceNewlinesWithDelimiter(modifiedInput, delimiter);

    int sum = 0;
    char* token = strtok(modifiedInput, &delimiter);
    
    while (token != NULL) {
        int num = processToken(token);
        if (num == -1) {
            free(modifiedInput);  // Free the duplicated input
            return -1;
        }
        sum += num;
        token = strtok(NULL, &delimiter);
    }

    free(modifiedInput);  // Free the duplicated input
    return sum;
}
