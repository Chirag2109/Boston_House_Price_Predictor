#ifndef IO_CONTROL_H
#define IO_CONTROL_H

void clearInputBuffer();
void validdouble(char *s, double minLimit, double maxLimit, double *VALUE);
void free2DArray(double **array, int rows);
int readCSV(const char *filename, double ***data, int *numPoints, int *numFeatures);
void getUserInput(double *features, int numFeatures, int *indices, int MAX_FEATURES);

#endif
