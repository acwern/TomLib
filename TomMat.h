#ifndef STDIO
#include<stdio.h>
#endif

#ifndef STDLIB
#include<stdlib.h>
#endif

/* Defines a matrix structure. It contains the number of rows, the number of columns, and a pointer to a 1D array */
typedef struct
{
	int row;
	int col;
	float *mat;
} matrix;

/* Creates a matrix, given number of rows r, number of columns c, and a 1D array el */
matrix *createMatr(int r,int c, float el[])
{
	matrix *M = (matrix *) malloc(sizeof(matrix));
		
	M->row = r;
	M->col = c;

	M->mat = (float *) malloc(sizeof(float)*r*c);

	int i;
	for(i = 0; i < r*c; i++)
			{
				M->mat[i] = el[i];
			}	

	return M;
}

/* Frees the memory allocated to a matrix */
void freeMatr(matrix *M)
{
	free(M->mat);
	free(M);
	return;
}

/* Prints a matrix to the screen. Breaks it up into its rows and prints them separately. */
void printMatr(matrix *M)
{
	int i, j, k;
	k = 0;

	for(i = 0; i < M->row; i++)
	{
		printf("{");
		for(j = 0; j < M->col; j++)
		{
			printf("%f", M->mat[k]);
			k++;
			if( j != M->col - 1)
			{
				printf(", ");
			}
		}
		printf("}\n");
	}

}

/* Adds matrices together. If the matrices cannot be added, tells the user this and just returns the first matrix */
matrix *addMatr(matrix *A, matrix *B)
{

	
	if((A->row != B->row) || (A->col != B->col))
	{
		printf("Error: Incompatible matrices for addition! Returning your first matrix.\n");
		return A;
	}
	matrix *M = (matrix *) malloc(sizeof(matrix));
	M->row = A->row;
	M->col = A->col;
	M->mat = (float *) malloc(sizeof(float)*(M->row)*(M->col));	
	int i;
	
	for(i = 0; i < (M->row) * (M->col); i++)
	{
			M->mat[i] = A->mat[i] + B->mat[i]; 		
			i++;
	}

	return M;

}

/* Subtracts matrices. If the matrices cannnot be subtracted, tells the user this and returns the first matrix */
matrix *subMatr(matrix *A, matrix *B)
{

	
	if((A->row != B->row) || (A->col != B->col))
	{
		printf("Error: Incompatible matrices for subtraction! Returning your first matrix.\n");
		return A;
	}
	matrix *M = (matrix *) malloc(sizeof(matrix));
	M->row = A->row;
	M->col = A->col;
	M->mat = (float *) malloc(sizeof(float)*(M->row)*(M->col));	
	int i;
	
	for(i = 0; i < (M->row) * (M->col); i++)
	{
			M->mat[i] = A->mat[i] - B->mat[i]; 		
			i++;
	}

	return M;
}

/* Multiplies matrices together. If the matrices cannot be multiplied, tells the user this and returns the first matrix */
matrix *prodMatr(matrix *A, matrix *B)
{
	if(A->col != B->row)
	{
		printf("Error: Incompatible matrices for multiplication! Returning your first matrix.\n");
		return A;
	}
	matrix *M = (matrix *) malloc(sizeof(matrix));
	M->row = A->row;
	M->col = B->col;
	M->mat = (float *) malloc(sizeof(float)*(M->row)*(M->col));

	int i, k;
	float sum;
	int r = 1;
        int c = 1;

	/* modulus is found with % */
	/* M[k] goes in -> direction before downwards */
	for(k = 0 ; k < (M->row) * (M->col); k++)
	{
		sum = 0;
		
		for(i = 0; i < A->col; i++)
		{ 

				sum += A->mat[(r-1)*(A->col) + i] * B->mat[(c-1) + (B->col)*i];
		}
		M->mat[k] = sum;
		if(c == M->col)
		{
			c = 1;
			r += 1;
		}
		
		else
		{
			c++;
		}
	}
	
	return M;
}

/* Scalar multiplication of matrices */
matrix * scalMat(float k, matrix *M)
{
	int i;
	for(i = 0; i < M->row * M->col; i++)
	{
		M->mat[i] = k*(M->mat[i]);
	}

	return M;
}

matrix *getCol(int k, matrix *M)
{
	
	if(k > M->col || k < 0)
	{
		printf("Invalid index.\n");
		return 0;
	}

	matrix *col = (matrix *) malloc(sizeof(matrix));
        col->row = M->row;
	col->col = 1;	
	col->mat = (float *) malloc(sizeof(float)*(M->row));


	int i;
	for(i = 0; i < M->row; i++)
	{
		col->mat[i] = M->mat[k+i*(M->col)];
	}

	return col;
}

matrix *getRow(int k, matrix *M)
{
	
	if(k > M->col || k < 0)
	{
		printf("Invalid index.\n");
		return 0;
	}

	matrix *row = (matrix *) malloc(sizeof(matrix));
        row->row = 1;
	row->col = M->col;	
	row->mat = (float *) malloc(sizeof(float)*(M->col));


	int i;
	for(i = 0; i < M->row; i++)
	{
		row->mat[i] = M->mat[k+i*(M->col)];
	}

	return row;
}


matrix *rrefMatr(matrix *M)
{
	/* Draft 1: Assume in right order, just have to do row operations etc. */
	int i;
	matrix *rref = (matrix *) malloc(sizeof(matrix));
	rref->row = M->row;
	rref->col = M->col;
	rref->mat = (float *) malloc(sizeof(M->mat));
	/* Setting the two equal. As they're pointers, I can't do arithmetic directly on M without it changing elsewhere */
	for(i = 0; i< M->row * M->col; i++)
	{
		rref->mat[i] = M->mat[i];
	}

	int r = 1; /*row counter*/
	int c = 1; /*col counter*/

	float multiple;
	int j, k, r2, c2;
	int pivotfound = 0;

	for(k = 0; k < rref->row * rref->col; k++)
	{
		if(c == rref->col)
		{
			c = 1;
			r += 1;
			pivotfound =0;
			continue;
		}

		if( rref->mat[k] == 0 || pivotfound == 1)
		{
			c++;
			continue;
		}
	        
		pivotfound = 1;
		multiple = rref->mat[k];
		/* So now, k is a pivot. First row: */
		for(j = 0; j < rref->col - (c-1) ; j++)
		{
			rref->mat[k+j] = rref->mat[k+j] / multiple;
		}


		/* i is rows, j is columns */
		for(r2 = 1; r2 <= rref->row; r2++)
		{
			if(r2 != r)
			{
				multiple = rref->mat[(r2-1)*rref->col + (c-1)];
					
				for(c2 = 1; (c2-1) < rref->col; c2++)
				{
					rref->mat[(r2-1)*rref->col+(c2-1)] = ( rref->mat[(r2-1)*rref->col+(c2-1)] ) - multiple *rref->mat[(r-1)*rref->col + (c2-1)];
				}
			}
			
		}
	
		c++;
	}

	return rref;
}
