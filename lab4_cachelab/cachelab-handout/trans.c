//2019007892 박준성
/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
	int blockRow, blockCol, row, col, tempRow, tempVal;
    //if input is 32 X 32 array, divide into 8 elements in row and col, do transpose when row != col
    //if row == col, there must be memory eviction, so should handle it by local variable exceptionally
    if (N == 32) {
        for (blockCol = 0; blockCol < M; blockCol += 8) {
            for (blockRow = 0; blockRow < N; blockRow += 8) {
                for (row = blockRow; row < blockRow + 8; row++) {
                    for (col = blockCol; col < blockCol + 8; col++) {
                        if (row != col) {
                            B[col][row] = A[row][col];
                        } else {
			    tempVal = A[row][col];
			    tempRow = row;
		        }
                    }
                    if (blockRow == blockCol) {
			B[tempRow][tempRow] = tempVal;
            	    }
           	}
       	     }
        } 
   } else {	//if input is 61 X 67 array, divde into maximum at 16 elements in row and col
	   	//transpose when row != col
		//if row == col, there must be memory eviction, so should handle it by local variable exceptionally
        for (blockCol = 0; blockCol < M; blockCol += 16) {
            for (blockRow = 0; blockRow < N; blockRow += 16) {
                for (row = blockRow; (row < N) && (row < blockRow + 16); row++){
                    for (col = blockCol; (col < M) && (col < blockCol + 16); col++) {
                        if (row != col) {
                            B[col][row] = A[row][col];
                        } else {
                            tempVal = A[row][col];
                            tempRow = row;
                        }
                    }
                    if (blockRow == blockCol) {
                        B[tempRow][tempRow] = tempVal;
                    }
                }
            }
        }
    }
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

