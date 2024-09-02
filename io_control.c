#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

// Function to clear the input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Clear the buffer
    }
}

// Function to free 2D array
void free2DArray(double **array, int rows)
{
    if (array != NULL) {
        for (int i = 0; i < rows; i++) {
            if (array[i] != NULL) {
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
