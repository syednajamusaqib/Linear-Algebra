#include <stdio.h>

/*

There are basically four steps in this approach
Step 1: Check for Non Zero Row
Step 2: Swap Rows
Step 3: Make Pivot element of Pivot Row "1"
Step 4: Eliminate elements below pivots to get Row-Echelon Form  
Step 5: Once you achieved row echelon form traverse matrix in reverse condition and make entries above 1 as 0
*/



#define ROWS 3
#define COLS 4

int findNonZeroRow(double matrix[][COLS], int pivot_row, int col){
    for(int row = pivot_row; row < ROWS; row++){
        if(matrix[row][col] != 0){
            return row;
        }
    }
    return -1;
}

void swapRows(double matrix[][COLS], int row1, int row2){
    double temp[COLS];

    for(int i=0;i<COLS;i++){
        temp[i] = matrix[row1][i];
        matrix[row1][i] = matrix[row2][i];
        matrix[row2][i] = temp[i];
    }
}

void makePivotOne(double matrix[][COLS], int pivot_row, int col){
    double pivot_element = matrix[pivot_row][col];
    for(int i=0; i < COLS; i++){
        matrix[pivot_row][i] /= pivot_element;
    }
}

void eliminate_below(double matrix[][COLS], int pivot_row, int col){
    double pivot_element = matrix[pivot_row][col];
    for(int row = pivot_row+1; row < ROWS; row++){
        double factor = matrix[row][col];
        for(int i=0; i < COLS; i++){

        matrix[row][i] -= factor * matrix[pivot_row][i];
        }
    }
}

void rowEchelonForm(double matrix[][COLS]){
    int pivot_row = 0;
    for(int col = 0; col < COLS; col++){
        int non_zero_row = findNonZeroRow(matrix,pivot_row,col);
        if(non_zero_row != -1){
            swapRows(matrix,pivot_row,non_zero_row);
            makePivotOne(matrix,pivot_row,col);
            eliminate_below(matrix,pivot_row,col);
            pivot_row++;
        }
    }
}

void printMatrix(double matrix[][COLS], int row, int col) {
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            printf("%.1lf\t", matrix[i][j]);
        }
        printf("\n");
        
    }
}


void eliminateAbove(double matrix[][COLS], int row, int col) {
    for (int i = 0; i < row; i++) {
        matrix[i][col] = 0;
    }
}

void reducedREF(double matrix[][COLS]){
    for(int col = 0 ; col < COLS; col++){
        int rowWithOne = -1;
        for(int row = ROWS-1; row >=0 ;row--){
            if(matrix[row][col] == 1.0){
                rowWithOne = row;
                break;
            }
        }
        if(rowWithOne != -1){
            eliminateAbove(matrix, rowWithOne, col);
        }
    }
}


int main(void){

    double matrix[ROWS][COLS];

    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            printf("Enter the [%d,%d] element: ", i + 1, j + 1);
            scanf("%lf", &matrix[i][j]);
        }
    }

    puts("Your Matrix is:");
    printMatrix(matrix , ROWS, COLS);

    rowEchelonForm(matrix);

    puts("\nREF Form is \n");
    printMatrix(matrix, ROWS, COLS);

    reducedREF(matrix);

    puts("\nReduced REF Form is \n");
    printMatrix(matrix,ROWS,COLS);



    return 0;
}