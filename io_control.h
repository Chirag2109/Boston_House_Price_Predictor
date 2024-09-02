void clearInputBuffer();
void free2DArray(double **array, int rows);
void getUserInput(double *features, int numFeatures, int *indices, int MAX_FEATURES);

int readCSV(const char *filename, double ***data, int *numPoints, int *numFeatures);
