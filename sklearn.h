void splitData(double **data, double *labels, double ***X_train, double **y_train, double ***X_test, double **y_test, int numPoints, int numFeatures, int *correlatedFeatures, int correlatedSize, int testSize, int trainSize);
void trainLinearRegression(double **X_train, double *y_train, double *weights, double *bias, int numPoints, int numFeatures);
void predict(double **X_test, double *weights, double bias, double *y_pred, int numPoints, int numFeatures);
void getCorrelatedFeatures(double **correlationMatrix, int numFeatures, int *correlatedFeatures, int *correlatedSize, double THRESHOLD);
