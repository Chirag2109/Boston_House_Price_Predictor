void clearInputBuffer();
void free2DArray(double **array, int rows);
int readCSV(const char *filename, double ***data, int *numPoints, int *numFeatures);
void getUserInput(double *features, int numFeatures, int *indices, int MAX_FEATURES);
