#ifndef METRICS_H
#define METRICS_H

double r2Score(double *y_true, double *y_pred, int size);
double meanSquaredError(double *y_true, double *y_pred, int size);
double meanAbsoluteError(double *y_true, double *y_pred, int size);

#endif
