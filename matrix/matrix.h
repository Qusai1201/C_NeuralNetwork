#pragma once

typedef struct {
	double** entries;
	int rows;
	int cols;
} matrix;

matrix* matrix_create(int row, int col);
void matrix_fill(matrix *m, int n);
void matrix_free(matrix *m);
void matrix_print(matrix *m);
matrix* matrix_copy(matrix *m);
void matrix_save(matrix* m, char* file_string);
matrix* matrix_load(char* file_string);
void matrix_randomize(matrix* m, int n);
int matrix_argmax(matrix* m);
matrix* matrix_flatten(matrix* m, int axis);