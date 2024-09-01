double mean(double *arr, int n);
double stddev(double *arr, int n, double mean);
double r2Score(double *y_true, double *y_pred, int size);
double meanSquaredError(double *y_true, double *y_pred, int size);
double meanAbsoluteError(double *y_true, double *y_pred, int size);
double covariance(double *x, double *y, int n, double meanX, double meanY);
void correlated_matrix(double **data, double **corrMatrix, int numPoints, int numFeatures);
