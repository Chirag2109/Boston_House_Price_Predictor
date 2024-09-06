#include "Package.h"

void splitData(double **data, double *labels, double ***X_train, double **y_train, double ***X_test, double **y_test, int numPoints, int numFeatures, int *correlatedFeatures, int correlatedSize, int testSize, int trainSize)
{
    // Allocate memory for the training set
    *X_train = (double **)malloc(trainSize * sizeof(double *));
    *y_train = (double *)malloc(trainSize * sizeof(double));

    // Allocate memory for the testing set
    *X_test = (double **)malloc(testSize * sizeof(double *));
    *y_test = (double *)malloc(testSize * sizeof(double));

    // Allocate memory for the features in training and testing sets
    for (int i = 0; i < trainSize; i++)
    {
        (*X_train)[i] = (double *)malloc(correlatedSize * sizeof(double));
    }
    for (int i = 0; i < testSize; i++)
    {
        (*X_test)[i] = (double *)malloc(correlatedSize * sizeof(double));
    }

    int *indices = (int *)malloc(numPoints * sizeof(int));
    for (int i = 0; i < numPoints; i++)
    {
        indices[i] = i;
    }

    srand(50);
    // Shuffle the indices
    for (int i = numPoints - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    // Split the data into training and testing sets
    for (int i = 0; i < trainSize; i++)
    {
        for (int j = 0; j < correlatedSize; j++)
        {
            (*X_train)[i][j] = data[indices[i]][correlatedFeatures[j]];
        }
        (*y_train)[i] = labels[indices[i]];
    }

    for (int i = 0; i < testSize; i++)
    {
        for (int j = 0; j < correlatedSize; j++)
        {
            (*X_test)[i][j] = data[indices[trainSize + i]][correlatedFeatures[j]];
        }
        (*y_test)[i] = labels[indices[trainSize + i]];
    }

    free(indices);
}

// Function to train linear regression model
void trainLinearRegression(double **X_train, double *y_train, double *weights, double *bias, int numPoints, int numFeatures)
{
    gsl_matrix *X = gsl_matrix_alloc(numPoints, numFeatures);
    gsl_matrix *X_transpose = gsl_matrix_alloc(numFeatures, numPoints);
    gsl_matrix *X_transpose_X = gsl_matrix_alloc(numFeatures, numFeatures);
    gsl_matrix *X_transpose_X_inv = gsl_matrix_alloc(numFeatures, numFeatures);
    gsl_vector *X_transpose_y = gsl_vector_alloc(numFeatures);
    gsl_vector *y_train_gsl = gsl_vector_alloc(numPoints);
    gsl_vector *w = gsl_vector_alloc(numFeatures);

    // Fill gsl_matrix X
    for (int i = 0; i < numPoints; i++)
    {
        for (int j = 0; j < numFeatures; j++)
        {
            gsl_matrix_set(X, i, j, X_train[i][j]);
        }
    }

    // Fill gsl_vector y_train
    for (int i = 0; i < numPoints; i++)
    {
        gsl_vector_set(y_train_gsl, i, y_train[i]);
    }

    // Compute X_transpose
    gsl_matrix_transpose_memcpy(X_transpose, X);

    // Compute X_transpose_X
    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, X_transpose, X, 0.0, X_transpose_X);

    // Compute X_transpose_y
    gsl_blas_dgemv(CblasNoTrans, 1.0, X_transpose, y_train_gsl, 0.0, X_transpose_y);

    // Compute the inverse of X_transpose_X
    gsl_permutation *perm = gsl_permutation_alloc(numFeatures);
    int signum;
    gsl_linalg_LU_decomp(X_transpose_X, perm, &signum);
    gsl_linalg_LU_invert(X_transpose_X, perm, X_transpose_X_inv);
    gsl_permutation_free(perm);

    // Compute the weights: w = (X_transpose_X)^-1 * X_transpose_y
    gsl_blas_dgemv(CblasNoTrans, 1.0, X_transpose_X_inv, X_transpose_y, 0.0, w);

    // Extract the weights from the gsl_vector w
    for (int i = 0; i < numFeatures; i++)
    {
        weights[i] = gsl_vector_get(w, i);
    }

    // Calculate bias as the mean of y_train minus the weighted sum of means of X_train
    double y_mean = 0;
    double X_means[numFeatures];
    for (int i = 0; i < numPoints; i++)
    {
        y_mean += y_train[i];
    }
    y_mean /= numPoints;

    for (int i = 0; i < numFeatures; i++)
    {
        X_means[i] = 0;
        for (int j = 0; j < numPoints; j++)
        {
            X_means[i] += X_train[j][i];
        }
        X_means[i] /= numPoints;
    }

    *bias = y_mean;
    for (int i = 0; i < numFeatures; i++)
    {
        *bias -= weights[i] * X_means[i];
    }

    // Free allocated memory
    gsl_matrix_free(X);
    gsl_matrix_free(X_transpose);
    gsl_matrix_free(X_transpose_X);
    gsl_matrix_free(X_transpose_X_inv);
    gsl_vector_free(X_transpose_y);
    gsl_vector_free(y_train_gsl);
    gsl_vector_free(w);
}

// Function to predict using linear regression model
void predict(double **X_test, double *weights, double bias, double *y_pred, int numPoints, int numFeatures)
{
    for (int i = 0; i < numPoints; i++)
    {
        double prediction = bias;
        for (int j = 0; j < numFeatures; j++)
        {
            prediction += X_test[i][j] * weights[j];
        }
        y_pred[i] = prediction;
    }
}

void getCorrelatedFeatures(double **correlationMatrix, int numFeatures, int *correlatedFeatures, int *correlatedSize, double THRESHOLD)
{
    int k = 0;
    int lastFeatureIndex = numFeatures - 1;

    for (int i = 0; i < numFeatures - 1; i++)
    {
        // Check correlation of feature i with the last feature
        if (fabs(correlationMatrix[i][lastFeatureIndex]) > THRESHOLD)
        {
            correlatedFeatures[k++] = i;
        }
    }

    *correlatedSize = k;
}
