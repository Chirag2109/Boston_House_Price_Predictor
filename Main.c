#include "Libraries/Package.h"

int main()
{
    double THRESHOLD;
    double TRAIN_SIZE_RATIO;

    double *y_test = NULL; // To store test labels
    double *y_pred = NULL; // To store predicted labels
    int test_size = 0;     // To store the test size

    printf("\n");
    printf("\t\t\033[1;4;38;2;255;0;255m --- Model Testing Menu --- \033[0m\t\n\n");
    printf("\033[38;2;192;192;192mExit Testing       -> Enter -1 to exit the testing phase.\033[0m\n");
    printf("\033[38;2;192;192;192mPerformance Report -> Enter  0 to view the performance report of the model.\033[0m\n");
    printf("\033[38;2;192;192;192mTest the Model      \033[0m\n");
    printf("\033[38;2;192;192;192m                   -> Enter  1 to begin testing the model.\033[0m\n");
    printf("\033[38;2;192;192;192m                   -> Enter  2 to test testing the model with a diffrent threshold value.\033[0m\n");
    printf("\033[38;2;192;192;192m                   -> Enter  3 to test testing the model with different threshold and train size ratio.\033[0m\n");
    printf("\033[38;2;0;255;255mPlease select an option by entering the corresponding number!\033[0m\n\n");

    int flag = 1;
    while (flag)
    {
        int n;
        printf("\n\n\033[38;2;100;149;237mEnter your choice: \033[0m");
        if (scanf("%d", &n) != 1)
        {
            printf("\033[38;2;255;255;0mInvalid input. Please enter a valid number.\033[0m\n");
            clearInputBuffer();
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
            model(&y_test, &y_pred, &test_size, 0);
            break;

        case 2:
            printf("\033[38;2;100;149;237mEnter the new threshold : \033[0m");
            if (scanf("%lf", &THRESHOLD) != 1)
            {
                printf("\033[38;2;255;255;0mInvalid input. Please enter a valid number.\033[0m\n");
                clearInputBuffer();
            }
            clearInputBuffer();
            model(&y_test, &y_pred, &test_size, 1, THRESHOLD);
            break;

        case 3:
            printf("\033[38;2;100;149;237mEnter the new threshold : \033[0m");
            if (scanf("%lf", &THRESHOLD) != 1)
            {
                printf("\033[38;2;255;255;0mInvalid input. Please enter a valid number.\033[0m\n");
                clearInputBuffer();
            }

            printf("\033[38;2;100;149;237mEnter the new train size ratio : \033[0m");
            if (scanf("%lf", &TRAIN_SIZE_RATIO) != 1)
            {
                printf("\033[38;2;255;255;0mInvalid input. Please enter a valid number.\033[0m\n");
                clearInputBuffer();
            }
            clearInputBuffer();

            model(&y_test, &y_pred, &test_size, 2, THRESHOLD, TRAIN_SIZE_RATIO);
            break;

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
