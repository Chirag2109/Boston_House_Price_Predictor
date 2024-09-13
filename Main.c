#include "Libraries/Package.h"

int main()
{
    double *y_test = NULL;
    double *y_pred = NULL;
    int test_size = 0;

    printf("\n");
    printf("\t\t\033[1;4;38;2;255;0;255m --- Model Testing Menu --- \033[0m\t\n\n");
    printf("\033[38;2;192;192;192mExit Testing       -> Enter -1 to exit the testing phase.\033[0m\n");
    printf("\033[38;2;192;192;192mPerformance Report -> Enter  0 to view the performance report of the model.\033[0m\n");
    printf("\033[38;2;192;192;192mTest the Model      \033[0m\n");
    printf("\033[38;2;192;192;192m                   -> Enter  1 to begin testing the model.\033[0m\n");
    printf("\033[38;2;192;192;192m                   -> Enter  2 to test the model with a different threshold value.\033[0m\n");
    printf("\033[38;2;192;192;192m                   -> Enter  3 to test the model with a different train size ratio.\033[0m\n");
    printf("\033[38;2;192;192;192m                   -> Enter  4 to test the model with a different threshold and train size ratio.\033[0m\n");
    printf("\033[38;2;0;255;255mPlease select an option by entering the corresponding number!\033[0m\n\n");

    int flag = 1;
    while (flag)
    {
        double THRESHOLD = 0.5;
        double TRAIN_SIZE_RATIO = 0.75;
        int n;
        printf("\n\033[38;2;100;149;237mEnter your choice: \033[0m");
        if (scanf("%d", &n) != 1)
        {
            printf("\033[38;2;255;255;0mInvalid input. Please enter a valid number.\033[0m\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (n)
        {
        case 0:
            if (y_test != NULL && y_pred != NULL)
            {
                report(y_test, y_pred, test_size);
            }
            else
            {
                printf("\033[38;2;255;255;0mModel has not been tested yet. Please test the model first!\033[0m\n");
            }
            break;

        case 1:
            model(&y_test, &y_pred, &test_size, THRESHOLD, TRAIN_SIZE_RATIO);
            break;

        case 2:
            validdouble("Enter the new threshold (0 <= THRESHOLD <= 0.73): ", 0, 0.73, &THRESHOLD);

            if (THRESHOLD == 0.5)
            {
                printf("\033[38;2;255;255;0mThis is the default value of threshold. For this you can choose \"1\" in the Model Testing Menu.\033[0m\n");
                break;
            }
            else
            {
                model(&y_test, &y_pred, &test_size, THRESHOLD, TRAIN_SIZE_RATIO);
                break;
            }

        case 3:

            validdouble("Enter the new train size ratio (0 < TRAIN_SIZE_RATIO < 1): ", 0, 1, &TRAIN_SIZE_RATIO);

            if (TRAIN_SIZE_RATIO == 0.75)
            {
                printf("\033[38;2;255;255;0mThis is the default value of train size ratio. For this you can choose \"1\" in the Model Testing Menu.\033[0m\n");
                break;
            }
            else
            {
                model(&y_test, &y_pred, &test_size, THRESHOLD, TRAIN_SIZE_RATIO);
                break;
            }

        case 4:

            validdouble("Enter the new threshold (0 <= THRESHOLD <= 0.73): ", 0, 0.73, &THRESHOLD);

            if (THRESHOLD == 0.5)
            {
                printf("\033[38;2;255;255;0mThis is the default value of threshold. For this you can choose \"1\" in the Model Testing Menu.\033[0m\n");
                break;
            }
            else
            {

                validdouble("Enter the new train size ratio (0 < TRAIN_SIZE_RATIO < 1): ", 0, 1, &TRAIN_SIZE_RATIO);

                if (TRAIN_SIZE_RATIO == 0.75)
                {
                    printf("\033[38;2;255;255;0mThis is the default value of train size ratio. For this you can choose \"1\" in the Model Testing Menu.\033[0m\n");
                    break;
                }
                else
                {
                    model(&y_test, &y_pred, &test_size, THRESHOLD, TRAIN_SIZE_RATIO);
                    break;
                }
            }

        case -1:
            printf("\033[38;2;255;165;0mExiting the testing phase...\033[0m\n");
            flag = 0;
            break;

        default:
            printf("\033[38;2;255;255;0mInvalid choice. Please try again.\033[0m\n");
            break;
        }
    }

    return 0;
}
