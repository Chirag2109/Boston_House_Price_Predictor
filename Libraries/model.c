#include "Package.h"

#define MAX_FEATURES 14
#define TD 0.5
#define TSR 0.8

int model(double **y_test_ptr, double **y_pred_ptr, int *test_size_ptr, int num_args, ...)
{
    double **data = NULL;
    double *labels = NULL;
    int numPoints, numFeatures;

    // Default values
    double THRESHOLD = TD;
    double TRAIN_SIZE_RATIO = TSR;

    if (readCSV("../boston.csv", &data, &numPoints, &numFeatures) != 0)
    {
        printf("\033[38;2;255;165;0mError reading CSV file!\033[0m\n");
        return -1;
    }

    va_list args;
    va_start(args, num_args);

    // If the user provided a custom THRESHOLD
    if (num_args >= 1)
    {
        THRESHOLD = va_arg(args, double);
    }

    // If the user provided a custom TRAIN_SIZE_RATIO
    if (num_args >= 2)
    {
        TRAIN_SIZE_RATIO = va_arg(args, double);
    }

    va_end(args);

    int train_size = (int)(TRAIN_SIZE_RATIO * numPoints);
    int test_size = numPoints - train_size;

    // Store the test_size in the main function through pointer
    *test_size_ptr = test_size;

    // Allocate memory for the correlation matrix
    double **corrMatrix = (double **)malloc(numFeatures * sizeof(double *));
    if (!corrMatrix)
    {
        printf("\033[38;2;255;165;0mMemory allocation failed for corrMatrix!\033[0m\n");
        free2DArray(data, numPoints);
        return -1;
    }
    for (int i = 0; i < numFeatures; i++)
    {
        corrMatrix[i] = (double *)malloc(numFeatures * sizeof(double));
        if (!corrMatrix[i])
        {
            printf("\033[38;2;255;165;0mMemory allocation failed for corrMatrix row %d!\033[0m\n", i);
            free2DArray(data, numPoints);
            free2DArray(corrMatrix, i); // Free allocated rows so far
            return -1;
        }
    }

    correlation_matrix(data, corrMatrix, numPoints, numFeatures);

    labels = (double *)malloc(numPoints * sizeof(double));
    if (!labels)
    {
        printf("\033[38;2;255;165;0mMemory allocation failed for labels!\033[0m\n");
        free2DArray(data, numPoints);
        free2DArray(corrMatrix, numFeatures);
        return -1;
    }
    for (int i = 0; i < numPoints; i++)
    {
        labels[i] = data[i][numFeatures - 1]; // Last column of data "medv"
    }

    int correlatedFeatures[MAX_FEATURES];
    int correlatedSize;

    getCorrelatedFeatures(corrMatrix, numFeatures, correlatedFeatures, &correlatedSize, THRESHOLD);

    double **X_train = NULL, **X_test = NULL;
    double *y_train = NULL, *y_test = NULL;
    splitData(data, labels, &X_train, &y_train, &X_test, &y_test, numPoints, numFeatures, correlatedFeatures, correlatedSize, test_size, train_size);

    double *weights = (double *)malloc(correlatedSize * sizeof(double));
    if (!weights)
    {
        printf("\033[38;2;255;165;0mMemory allocation failed for weights!\033[0m\n");
        free(labels);
        free2DArray(data, numPoints);
        free2DArray(corrMatrix, numFeatures);
        free2DArray(X_train, train_size);
        free2DArray(X_test, test_size);
        free(y_train);
        free(y_test);
        return -1;
    }
    double bias;
    trainLinearRegression(X_train, y_train, weights, &bias, train_size, correlatedSize);

    double *y_pred = (double *)malloc(test_size * sizeof(double));
    if (!y_pred)
    {
        printf("\033[38;2;255;165;0mMemory allocation failed for y_pred!\033[0m\n");
        free(weights);
        free(labels);
        free2DArray(data, numPoints);
        free2DArray(corrMatrix, numFeatures);
        free2DArray(X_train, train_size);
        free2DArray(X_test, test_size);
        free(y_train);
        free(y_test);
        return -1;
    }
    predict(X_test, weights, bias, y_pred, test_size, correlatedSize);

    // Pass y_test and y_pred back to the main function
    *y_test_ptr = y_test;
    *y_pred_ptr = y_pred;

    // Create test data for the user-provided feature values
    double *userPrediction = (double *)malloc(sizeof(double));
    double **userTestData = (double **)malloc(sizeof(double *));
    if (!userPrediction || !userTestData)
    {
        printf("\033[38;2;255;165;0mMemory allocation failed for user prediction data!\033[0m\n");
        free(y_pred);
        free(weights);
        free(labels);
        free2DArray(data, numPoints);
        free2DArray(corrMatrix, numFeatures);
        free2DArray(X_train, train_size);
        free2DArray(X_test, test_size);
        free(y_train);
        free(y_test);
        if (userPrediction)
            free(userPrediction);
        if (userTestData)
            free(userTestData);
        return -1;
    }

    // Prompt user for feature values
    double userFeatures[MAX_FEATURES];
    getUserInput(userFeatures, correlatedSize, correlatedFeatures, MAX_FEATURES);
    userTestData[0] = (double *)malloc(correlatedSize * sizeof(double));
    if (!userTestData[0])
    {
        printf("\033[38;2;255;165;0mMemory allocation failed for userTestData!\033[0m\n");
        return -1;
    }

    for (int i = 0; i < correlatedSize; i++)
    {
        userTestData[0][i] = userFeatures[i];
    }

    // Predict using the user-provided feature values
    predict(userTestData, weights, bias, userPrediction, 1, correlatedSize);
    printf("\033[38;2;0;255;0mPredicted value for the entered features: US$\033[0m %.2f\n", userPrediction[0]);
    free(userTestData[0]);
    userTestData[0] = NULL;

    // Free allocated memory
    free(labels);
    free2DArray(data, numPoints);
    free2DArray(corrMatrix, numFeatures);
    free2DArray(X_train, train_size);
    free2DArray(X_test, test_size);
    free(y_train);
    free(y_test);
    free(weights);
    free(y_pred);
    free(userPrediction);
    free(userTestData);

    return 0;
}

int report(double *y_test, double *y_pred, int test_size)
{
    double mse = meanSquaredError(y_test, y_pred, test_size);
    double mae = meanAbsoluteError(y_test, y_pred, test_size);
    double r2 = r2Score(y_test, y_pred, test_size);

    printf("\033[38;2;0;255;0mR^2 Score:\033[0m %.2f %%\n", r2 * 100);
    printf("\033[38;2;0;255;0mMean Absolute Error (MAE):\033[0m %.2f\n", mae);
    printf("\033[38;2;0;255;0mMean Squared Error (MSE):\033[0m %.2f\n", mse);
}
