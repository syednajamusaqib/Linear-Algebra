#include <stdio.h>

#define ROWS 4
#define COLS 4

int determinant(double matrix[][COLS],int k){   // Determinant through recursion
    int result = 0; // It will store result of determinant
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
            for(int i = 0; i<k; i++){ 
                for(int j = 0; j<k; j++){
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


int main(void){

    double matrix[ROWS][COLS] = {
        {6, 4, 3, 1},
        {-4,3, 6, 2},
        {6, 1, 9, 2},
        {-8,7, 2, 5}
    };

    int res = determinant(matrix,4);
    printf("%d",res);

    return 0;
}