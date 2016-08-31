/*
 * matrix_operations.cpp
 *
 *  Created on: Aug 20, 2016
 *      Author: umba
 */

// function that allocate a double array (matrix)
// input: no of rows, no of columns
// output: address of the double array (pointer)
double** zeros(int nrow, int ncol)
{
	double** M;
	M = new double*[nrow]; // dynamic array of pointers: number of rows specified first
	for (int i=0; i<nrow; i++) {
		M[i] = new double[ncol];
		// set each entry equal to 0
		for (int j=0; j<ncol; j++)
			M[i][j] = 0.0;
	}

	return M;
}


// function that allocate a single array (vector)
// input: no of entries
// output: address of the single array (pointer)
double* zeros(int nentries)
{
	double* v;
	v = new double[nentries];
	for (int i=0; i<nentries; i++) {
		// set each entry equal to 0
		v[i]=0.0;
	}

		return v;
}
