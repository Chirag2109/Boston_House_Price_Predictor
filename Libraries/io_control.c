#include "header.h"

#define MAX_LINE_LENGTH 1024

// Function to clear the input buffer
void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        // Clear the buffer
    }
}

// Function to free 2D array
void free2DArray(double **array, int rows)
{
    if (array != NULL)
    {
        for (int i = 0; i < rows; i++)
        {
            if (array[i] != NULL)
            {
                free(array[i]);
            }
        }
        free(array);
    }
}

// Function to read CSV file and populate data matrix
int readCSV(const char *filename, double ***data, int *numPoints, int *numFeatures)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("\033[38;2;255;165;0mError opening file\033[0m");
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    int cols = 0;
    int rows = 0;

    // First pass to count columns
    if (fgets(line, sizeof(line), file))
    {
        char *token = strtok(line, ",");
        while (token)
        {
            cols++;
            token = strtok(NULL, ",");
        }
    }

    *numFeatures = cols; // Include the last column as a feature
    *numPoints = 0;

    // Count the number of data points
    while (fgets(line, sizeof(line), file))
    {
        (*numPoints)++;
    }
    rewind(file);

    // Allocate memory for data
    *data = (double **)malloc(*numPoints * sizeof(double *));
    for (int i = 0; i < *numPoints; i++)
    {
        (*data)[i] = (double *)malloc(*numFeatures * sizeof(double));
    }

    // Skip header line
    fgets(line, sizeof(line), file);

    int lineNumber = 0;

    while (fgets(line, sizeof(line), file))
    {
        char *token = strtok(line, ",");
        for (int i = 0; i < *numFeatures; i++)
        {
            (*data)[lineNumber][i] = atof(token);
            token = strtok(NULL, ",");
        }
        lineNumber++;
    }

    fclose(file);
    return 0;
}

void getUserInput(double *features, int numFeatures, int *indices, int MAX_FEATURES)
{
    const char *featureNames[] = {
        "CRIM (per capita crime rate by town)",
        "ZN (proportion of residential land zoned for lots over 25,000 sq. ft.)",
        "INDUS (proportion of non-retail business acres per town)",
        "CHAS (Charles River dummy variable (1 if tract bounds river; 0 otherwise))",
        "NOX (nitric oxides concentration (parts per 10 million))",
        "RM (average number of rooms per dwelling)",
        "AGE (proportion of owner-occupied units built prior to 1940)",
        "DIS (weighted distances to five Boston employment centers)",
        "RAD (index of accessibility to radial highways)",
        "TAX (full-value property tax rate per $10,000)",
        "PTRATIO (pupil-teacher ratio by town)",
        "B (1000(Bk - 0.63)^2 where Bk is the proportion of black residents by town)",
        "LSTAT (\% lower status of the population)"};

    const double examples[] = {
        0.3,   // CRIM
        18.0,  // ZN
        8.14,  // INDUS
        0.0,   // CHAS
        0.54,  // NOX
        6.575, // RM
        65.2,  // AGE
        4.09,  // DIS
        1.0,   // RAD
        296.0, // TAX
        15.3,  // PTRATIO
        396.9, // B
        4.98   // LSTAT
    };

    char inputBuffer[100];
    for (int i = 0; i < numFeatures; i++)
    {
        int featureIndex = indices[i];
        if (featureIndex >= MAX_FEATURES)
        {
            fprintf(stderr, "\033[38;2;255;165;0mFeature index %d is out of bounds.\033[0m\n", featureIndex);
            continue;
        }

        int validInput = 0;

        // Set specific limits for CHAS as it's a boolean, otherwise use DBL_MIN and DBL_MAX
        double minLimit = (featureIndex == 3) ? 0.0 : DBL_MIN;  // CHAS (index 3) is boolean
        double maxLimit = (featureIndex == 3) ? 1.0 : DBL_MAX;

        while (!validInput)
        {
            printf("\033[38;2;100;149;237mEnter value for %s (Example: %.2f): \033[0m", featureNames[featureIndex], examples[featureIndex]);
            fgets(inputBuffer, sizeof(inputBuffer), stdin);

            // Check if input is a valid double
            char *endPtr;
            double inputValue = strtod(inputBuffer, &endPtr);

            if (endPtr == inputBuffer || *endPtr != '\n') // Not a valid double or there are extra characters
            {
                printf("\033[38;2;255;255;0mInvalid input! Please enter a numerical value.\033[0m\n");
                continue;
            }

            // Check if input is within the defined range
            if (inputValue < minLimit || inputValue > maxLimit)
            {
                printf("\033[38;2;255;255;0mInvalid input! Please enter a value within the range %.2e - %.2e for %s.\033[0m\n", minLimit, maxLimit, featureNames[featureIndex]);
            }
            else
            {
                features[i] = inputValue;
                validInput = 1;
            }
        }
    }
}
