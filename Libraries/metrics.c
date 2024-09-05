// Function to calculate Mean Squared Error
double meanSquaredError(double *y_true, double *y_pred, int size)
{
    double mse = 0.0;
    for (int i = 0; i < size; i++)
    {
        double diff = y_true[i] - y_pred[i];
        mse += diff * diff;
    }
    return mse / size;
}

// Function to calculate Mean Absolute Error
double meanAbsoluteError(double *y_true, double *y_pred, int size)
{
    double mae = 0.0;
    for (int i = 0; i < size; i++)
    {
        double diff = fabs(y_true[i] - y_pred[i]);
        mae += diff;
    }
    return mae / size;
}

// Function to calculate R^2 Score
double r2Score(double *y_true, double *y_pred, int size)
{
    double ss_total = 0.0;
    double ss_residual = 0.0;
    double mean_y_true = 0.0;

    for (int i = 0; i < size; i++)
    {
        mean_y_true += y_true[i];
    }
    mean_y_true /= size;

    for (int i = 0; i < size; i++)
    {
        double y_true_val = y_true[i];
        double y_pred_val = y_pred[i];
        ss_total += (y_true_val - mean_y_true) * (y_true_val - mean_y_true);
        ss_residual += (y_true_val - y_pred_val) * (y_true_val - y_pred_val);
    }

    return 1.0 - (ss_residual / ss_total);
}
