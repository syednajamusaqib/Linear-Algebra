#include <stdio.h>
#define ROWS 3
#define COLS 3


void cofactor(double matrix[ROWS][COLS], int k);
void transpose(double matrix[ROWS][COLS], double cofactorMatrix[ROWS][COLS], int k);
double determinant(double matrix[][COLS],int k);
void printMatrix(double matrix[][COLS], int row, int col);

int main(void){


   double matrix[ROWS][COLS];

    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            printf("Enter the [%d,%d] element: ", i + 1, j + 1);
            scanf("%lf", &matrix[i][j]);
        }
    }
    puts("\nYour Matrix is: \n");
    printMatrix(matrix, ROWS, COLS);

    int deter = determinant(matrix, COLS);
    if(deter == 0){
        puts("Determinant is 0 So No Inverse Possible");
    }
    else
        cofactor(matrix,COLS);

    return 0;
}

double determinant(double matrix[ROWS][COLS],int k){   // Determinant through recursion
    double result = 0; // It will store result of determinant
    int sign = 1; // Sign which will be changed every time we change row and columns
    int mainRow; // first row which will be used to calculate determinant
    double smallMatrix[ROWS][COLS]; // Smaller matrix to get determinant
    int rowOfNewMatrix, colOfNewMatrix;

    // Base Case for recursive function
    if( k == 1){ 
        return matrix[0][0];
    }
    else{
        for(mainRow = 0; mainRow < k; mainRow++){ // Traversing first row of the matrix
            rowOfNewMatrix = 0;
            colOfNewMatrix = 0;
            for(int i = 0; i<k; i++){  // rows
                for(int j = 0; j<k; j++){ // columns
                    smallMatrix[i][j] = 0; // making smaller matrix zero so that we can add desired elements into it
                    if(i!=0 && j!=mainRow){ // Valid condition case
                        smallMatrix[rowOfNewMatrix][colOfNewMatrix] = matrix[i][j];
                        if(colOfNewMatrix < (k-2)){
                            colOfNewMatrix++;
                        }
                        else{
                            colOfNewMatrix = 0;
                            rowOfNewMatrix++;
                        }
                    }
                }
            }
            result = result + sign * (matrix[0][mainRow]* determinant(smallMatrix,k-1)); // Recursion
            sign = -1 * sign;
        }
    }
    return result;
}

void transpose(double matrix[ROWS][COLS], double cofactorMatrix[ROWS][COLS], int k){
    double transposedMatrix[ROWS][COLS];
    for(int row = 0; row < k; row++){
        for(int col = 0; col < k; col++){
            transposedMatrix[row][col] = cofactorMatrix[col][row];
        }
    }

    double deter = determinant(matrix,k);
    double inversedMatrix[ROWS][COLS];

    for(int row = 0; row < k; row++){
        for(int col = 0; col < k; col++){
            inversedMatrix[row][col] = transposedMatrix[row][col] / deter;
        }
    }

    printf("\nThe inverse of matrix: \n");
   for (int row = 0;row < k; row++)
    {
     for (int col = 0;col < k; col++)
       {
         printf("\t%.3lf", inversedMatrix[row][col]);
        }
    printf("\n");
     }


     printf("\nThe adjoint of matrix: \n");
   for (int row = 0;row < k; row++)
    {
     for (int col = 0;col < k; col++)
       {
         printf("\t%.3lf", transposedMatrix[row][col]);
        }
    printf("\n");
     }

}


void cofactor(double matrix[ROWS][COLS], int k){
    // Declaring varaibles and matrices we need
    double resultMatrix[ROWS][COLS]; // It will be our final cofactor Matrix
    double subMatrix[ROWS][COLS]; // It is the Matrix that will be extracted from original matrix
    int rowsOfResult, colsOfResult, rowsOfSub, colsOfSub;
    int sign = 1;

    for(rowsOfResult = 0; rowsOfResult < k ; rowsOfResult++){
        for(colsOfResult = 0; colsOfResult < k; colsOfResult++){
            rowsOfSub = 0; // Initializing rows
            colsOfSub = 0; // 
            for(int i = 0; i < k; i++){
                for(int j = 0; j < k; j++){
                    if(i != rowsOfResult && j != colsOfResult){
                        subMatrix[rowsOfSub][colsOfSub] = matrix[i][j]; // Populating Sub Matrix
                        if(colsOfSub < (k-2)){ 
                            colsOfSub++;
                        }
                        else{
                            colsOfSub = 0;
                            rowsOfSub++;
                        }
                    }
                }
            }
            resultMatrix[rowsOfResult][colsOfResult] = sign * determinant(subMatrix,k-1);
            sign = -1 * sign;
        }
    }
    transpose(matrix,resultMatrix, k);
}

void printMatrix(double matrix[][COLS], int row, int col) {
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            printf("%.1lf\t", matrix[i][j]);
        }
        printf("\n");
        
    }
}
