#ifndef MODEL_H
#define MODEL_H

void report(double *y_test, double *y_pred, int test_size);
int model(double **y_test_ptr, double **y_pred_ptr, int *test_size_ptr, double THRESHOLD, double TRAIN_SIZE_RATIO);

#endif
