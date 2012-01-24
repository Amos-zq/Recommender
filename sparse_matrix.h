/*-
* Copyright (c) 2012 Hamrouni Ghassen.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
* 1. Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
* OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
* OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
* SUCH DAMAGE.
*/

/************************************************************************/
/*          Sparse matrix data structure (Yale format)                  */
/************************************************************************/

#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

/* Coordinate list (COO) */
typedef struct coo_entry
{
	float		value;
	unsigned	int row_i;
	unsigned	int column_j;
} coo_entry_t;

/* coo_matrix is used to initialize a sparse matrix */
typedef struct coo_matrix
{
	coo_entry_t*     entries;
	unsigned int     current_size;
	unsigned int     size;
} coo_matrix_t;

/* Allocate space for a COO matrix */
coo_matrix_t*
init_coo_matrix(unsigned int max_size);

/* delete the COO matrix */ 
void
free_coo_matrix(coo_matrix_t* matrix);

/* insert an element into the COO matrix */
void
insert_coo_matrix(float val, unsigned int row_i, unsigned int column_j, coo_matrix_t* matrix);

/* sort the COO matrix left-to-right top-to-bottom (row-major) order */
void
sort_coo_matrix(coo_matrix_t* matrix);

/* Sparse matrix structure (yale format) */
typedef struct sparse_matrix
{
	unsigned int	column_nb;

	unsigned int	row_nb;

	unsigned int	nonzero_entries_nb; /* NNZ */

	float*			values;             /* A */

	unsigned int*	row_index;          /* IA */

	unsigned int*	column_index;       /* JA */

} sparse_matrix_t;

/* Allocate space for the sparse matrix */
sparse_matrix_t* 
init_sparse_matrix(coo_matrix_t* c_matrix, unsigned int row_nb, unsigned int column_nb);

/* Delete the sparse matrix */
void
free_sparse_matrix(sparse_matrix_t* matrix);

/* Check the matrix contains an element */
int
element_exists(unsigned int row_i, unsigned int column_j, sparse_matrix_t* matrix);

/* Get an element from the matrix */
float 
get_element(unsigned int row_i, unsigned int column_j, sparse_matrix_t* matrix);

/* Get the average of row i (sum of filled values / number of filled values) */
float
row_values_average(unsigned int row_i, sparse_matrix_t* matrix);

/* Get the average of column j (sum of filled values / number of filled values) */
float
column_values_average(unsigned int column_j, sparse_matrix_t* matrix);

#endif //SPARSE_MATRIX_H

