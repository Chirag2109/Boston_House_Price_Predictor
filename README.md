Boston_House_Price_Predictor
A detailed project in c

Introduction:
The Boston House Price Predictor is designed to predict housing prices in the Boston area based on various features of the homes and their surrounding neighborhoods. This program implements a linear regression model, which has been trained on the famous Boston Housing dataset, to analyze the relationship between different factors such as crime rate, average number of rooms, proximity to employment centers, and more. By leveraging statistical methods like bias calculation, the predictor aims to provide accurate price predictions for potential properties.

Use Case:
This tool is particularly useful for real estate professionals, data analysts, and developers interested in understanding the key drivers of housing prices in urban settings.

Structure:
->Boston_House_Price_Predictor:
    ->Libraries:
      This folder contains all the custom header files which developed and used in this project.
        ->model.h:
          This header file contains the function which is using all other header files to do the required project building.
        ->io_control.h:
          This header file contains the functions which are required to take input from user, read csv file(dataset) and free the space that is being used by the variables used in the processing.
        ->statistics.h:
          This header file contains the functions which are required to do the statistical calculations during the data preprocessing like finding the standard deviation and covariance of the dataset.
        ->linear_regression.h:
          This header file contains the functions which are required to do the actual data processing like training the linear regression model based on the dataset available.
        ->metrics.h:
          This header file contains the functions which are required to calculate the accuracy of the model like finding the r2 score of the model.
    ->Temporary_Files:
      This Folder contain the help.md file for more information.
    ->Main.c:
      This file contains the actual int main function in which i am printing the menu and calling the function depending on user's choice.
    ->boston.csv:
      This csv file contains the dataset from Boston city of the houses with different internal and external features.

-------------------------------------------------------------------------------------------------------------------------------------------------------------
"The file Boston_Dataset_Analysis.h is a specialized library tailored for the Boston house price dataset. But, the other libraries in the project are designed for more general use, allowing for flexibility in training different Linear Regression models on new datasets. However, their performance and efficiency in handling various models have not yet been thoroughly tested, so I cannot guarantee optimal results across all applications."
-------------------------------------------------------------------------------------------------------------------------------------------------------------

Approach:
Step1: Made a function to read the csv file and convert the dataset in a more usable format i.e. a 2D matrix.
Step2: Preprocessing - It contains various tasks to be done before training the data like ->
          i) Checking for the null values in the dataset : Fortunately, the file doesnot contain any null values beforehand so this make our task easier.
         ii) Checking for the features having great impact on label(price in this case) : For this, 
             a. I have made a matrix containing the correlation value of every feature with every other feature.
             b. Then I created a correlated features array which contains the indices of the features having correlation value greater than the threshold value with the label(price in this case).
             c. Then splitdata function is splitting the code into training and testing datasets. I have used the ratio to be 80:20 respectively, but as earliear mentioned this a general function and you can pass any other ratio as an argument to the function.
Step3: Data Processing - Working with features having great impact on label(price in this case) in the train data ->
          i) Then training the data splitted by split data function using linear regression.
         ii) Then predicting the price using the data stored in y_test matrix and storing the prediction in y_pred array.
Step4: Performance - Check the performance of a regression model, we generally analyse three metrices r2 score, mean absolute error and mean squared error ->
             a. mean absolute error: it finds the difference in the prediction stored in y_pred against the price in the y_test matrix and then calculate the mean value of those differences.
             b. mean squared error: it finds the square of the difference in the prediction stored in y_pred against the price in the y_test matrix and then calculate the mean value of those square differences.
             c. R2 score: 1 – (RSS/TSS) Where, R2 represents the requrired R Squared value, RSS represents the residual sum of squares, and TSS represents the total sum of squares.
Step5: UserInput - Now take input of the features present in the correlatedFeatures array from the user and predict the output based on this input and showing the output to the user.

END :)
