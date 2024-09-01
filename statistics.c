#include <math.h>

double mean(double *feature, int numPoints) {
  double sum = 0.0;
    for (int i = 0; i < numPoints; i++) {
        sum += feature[i];
    }
    return sum / numPoints;
}

double stddev(double *feature, int numPoints, double mean) {
  double sum = 0.0;
  for (int i = 0; i < numPoints; i++) {
        sum += (feature[i] - mean) * (feature[i] - mean);
    }
    return sqrt(sum / (numPoints - 1));
}

double covariance(double *feature1, double *feature2, int numPoints, double mean1, double mean2) {
    double sum = 0.0;
    for (int i = 0; i < numPoints; i++) {
        sum += (feature1[i] - mean1) * (feature2[i] - mean2);
    }
    return sum / (numPoints - 1);
}

void correlation_matrix(double **data, double **corrMatrix, int numPoints, int numFeatures) {
    for (int i = 0; i < numFeatures; i++) {
        for (int j = 0; j < numFeatures; j++) {
            if (i == j) {
                corrMatrix[i][j] = 1.0;
            } else {
                double x[numPoints], y[numPoints];
                for (int k = 0; k < numPoints; k++) {
                    x[k] = data[k][i];
                    y[k] = data[k][j];
                }
                double meanX = mean(x, numPoints);
                double meanY = mean(y, numPoints);
                double stdX = stddev(x, numPoints, meanX);
                double stdY = stddev(y, numPoints, meanY);
                double covXY = covariance(x, y, numPoints, meanX, meanY);
                corrMatrix[i][j] = covXY / (stdX * stdY);
            }
        }
    }
}
