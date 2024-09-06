Here's a neatly formatted version of your `Boston_House_Price_Predictor` project documentation:

---

# Boston_House_Price_Predictor

---

### Introduction:  
The **Boston House Price Predictor** is designed to predict housing prices in the Boston area based on various features of the homes and their surrounding neighborhoods. This program implements a linear regression model, trained on the famous Boston Housing dataset, to analyze the relationship between factors such as crime rate, average number of rooms, proximity to employment centers, and more. By leveraging statistical methods like bias calculation, the predictor aims to provide accurate price predictions for potential properties.

### Use Case:  
This tool is particularly useful for real estate professionals, data analysts, and developers interested in understanding the key drivers of housing prices in urban settings.

---

### Structure:

- **Boston_House_Price_Predictor:**
    - **Libraries:**
        - This folder contains all the custom header files developed and used in this project.  
        - **model.h:**  
            Contains functions using other header files to build the project.
        - **io_control.h:**  
            Contains functions required for user input, reading the CSV file (dataset), and freeing up memory used by variables during processing.
        - **statistics.h:**  
            Contains functions for statistical calculations during data preprocessing, such as finding standard deviation and covariance.
        - **linear_regression.h:**  
            Contains functions required for actual data processing, such as training the linear regression model using the available dataset.
        - **metrics.h:**  
            Contains functions required to calculate the model's accuracy, such as finding the R² score.
        - **Package.h:**  
            Contains `#include` statements for all other header files, acting as a package consisting of libraries.
    - **Temporary_Files:**  
        This folder contains the `help.md` file for more information.
    - **Main.c:**  
        Contains the `main()` function, which prints the menu and calls functions based on the user's choice.
    - **boston.csv:**  
        This CSV file contains the dataset from Boston, detailing houses with various internal and external features.

> "The file `model.h` is a specialized library tailored for the Boston house price dataset. However, the other libraries in the project are designed for general use, allowing flexibility in training different linear regression models on new datasets. That said, their performance and efficiency for different models have not been thoroughly tested, so I cannot guarantee optimal results across all applications."

---

### Approach:

- **Step 1: Data Loading**  
    - Created a function to read the CSV file and convert the dataset into a more usable format (i.e., a 2D matrix).

- **Step 2: Preprocessing**  
    - Various tasks are performed before training the data, such as:
        1. **Null value check:**  
           Fortunately, the dataset contains no null values, simplifying the task.
        2. **Feature selection:**  
           Identifying features with a significant impact on the label (price):
            - a. Generated a matrix containing the correlation values of every feature with every other feature.
            - b. Created a `correlated_features` array with indices of features having a correlation value greater than the default threshold (0.50) with the label (price).
            - c. The `split_data()` function divides the data into training and testing datasets (80:20 ratio by default), though this ratio can be changed by passing a different argument.

- **Step 3: Data Processing**  
    - Working with features that have a significant impact on the label (price):
        1. **Training the model:**  
           Using linear regression on the training data split by the `split_data()` function.
        2. **Prediction:**  
           Predicting the price using the data stored in the `y_test` matrix and storing the prediction in the `y_pred` array.

- **Step 4: Performance Evaluation**  
    - Check the performance of the regression model by analyzing three metrics:
        1. **Mean Absolute Error (MAE):**  
           Computes the difference between predictions (`y_pred`) and actual prices (`y_test`), then calculates the mean of those differences.
        2. **Mean Squared Error (MSE):**  
           Computes the square of the differences between predictions (`y_pred`) and actual prices (`y_test`), then calculates the mean of those squared differences.
        3. **R² Score:**  
           \( R^2 = 1 - \frac{RSS}{TSS} \)  
           Where R² represents the required R-squared value, RSS represents the residual sum of squares, and TSS represents the total sum of squares.

- **Step 5: User Input**  
    - The program takes input for the features present in the `correlated_features` array from the user, predicts the output based on this input, and displays the predicted price to the user.

---

### Important Notice:
Please ensure you run this application **exclusively in a Linux terminal environment**. Use the command `./run.sh` to execute the script, which will automatically perform all the necessary steps to build and run the application. Note that the commands in this script are specifically tailored for Linux systems and will not work on other operating systems. Running the script in a non-Linux environment may result in errors or unexpected behavior.

---

**END**
