#ifndef STATISTICS_H
#define STATISTICS_H

double mean(double *arr, int n);
double stddev(double *arr, int n, double mean);
double covariance(double *x, double *y, int n, double meanX, double meanY);
void correlation_matrix(double **data, double **corrMatrix, int numPoints, int numFeatures);

#endif
