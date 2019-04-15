#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NMATRIX_STRUCT
{
  size_t ndims;
  size_t count;
  size_t* shape;
  int* elements;
}nmatrix;

void matrix_print(nmatrix* mat) {
	printf("No. of dimensions: %d\n", (int)mat->ndims);
	if(mat->ndims == 0) {
		printf("%d\n", mat->elements[0]);
		return;
	}
	if(mat->ndims == 1) {
		printf("[");
		size_t ind = 0;
		for(size_t i = 0; i < mat->count; i++) {
			printf("%d", mat->elements[ind++]);
			if(i != mat->count - 1)
				printf(", ");
		}
		printf("]\n");
		return;
	}
	printf("[\n");
	size_t ind = 0;
	for(size_t i = 0; i < mat->shape[0]; i++) {
		printf("  [");
		for(size_t j = 0; j < mat->shape[1]; j++) {
			printf("%d", mat->elements[ind++]);
			if(j != mat->shape[1] - 1)
				printf(", ");
		}
		printf("]");
		if(i != mat->shape[0] - 1)
			printf(", \n");
		else
			printf("\n");
	}
	printf("]\n");
}

void get_stride(nmatrix* mat, size_t* stride) {
	size_t val = 1;
	for(int i = (mat->ndims)-1; i >= 0; i--) {
		stride[i] = val;
		val *= mat->shape[i];
	}
} 

size_t get_index(nmatrix* mat, int* indices) {
	size_t index = 0;
	size_t* stride = (size_t*)calloc(mat->ndims, sizeof(size_t));
	get_stride(mat, stride);
	for(size_t i = 0; i < mat->ndims; i++) {
		index += (indices[i] * stride[i]);
	}
	return index;
}

bool check_compatibility(nmatrix* mat1, nmatrix* mat2) {
	int ndims1 = mat1->ndims;
	int ndims2 = mat2->ndims;
	int least_dims = ndims1 <= ndims2 ? ndims1 : ndims2;

	int index1 = ndims1 - 1, index2 = ndims2 - 1;
	while(least_dims--) {
		if(mat1->shape[index1] > 1 && mat2->shape[index2] > 1
			&& mat1->shape[index1] != mat2->shape[index2])
		index1--, index2--;
	}
	return true;
}

void expand(nmatrix* mat, size_t* new_shape, int new_ndims) {
	int new_count = 1;
	for(size_t i = 0; i < new_ndims; i++)
		new_count *= (int)new_shape[i];
	int* new_elements = (int*)calloc(new_count, sizeof(int));
	for(size_t i = 0; i < mat->count; i++)
		new_elements[i] = mat->elements[i];
	if(new_ndims != mat->ndims) {
		int num = new_shape[0], coeff = new_shape[1];
		for(int i = 0; i < num; i++) {
			for(int j = 0; j < mat->count; j++) {
				int index = (i * coeff) + j;
				new_elements[index] = mat->elements[j];
			}
		}
		mat->count = new_count;
		mat->ndims = new_ndims;
		mat->shape = new_shape;
		mat->elements = new_elements;
	}
}

void broadcast(nmatrix* mat1, nmatrix* mat2) {
	int ndims1 = mat1->ndims;
	int ndims2 = mat2->ndims;
	int least_dims = ndims1 <= ndims2 ? ndims1 : ndims2;
	int max_dims = ndims1 >= ndims2 ? ndims1 : ndims2;

	int index1 = ndims1 - 1, index2 = ndims2 - 1, index = max_dims - 1;
	size_t* new_shape = (size_t*)calloc(least_dims, sizeof(size_t));
	if(ndims1 > ndims2) {
		for(size_t i = 0; i < ndims1; i++)
			new_shape[i] = mat1->shape[i];
	}
	else {
		for(size_t i = 0; i < ndims2; i++)
			new_shape[i] = mat2->shape[i];
	}
	while(least_dims--) {
		new_shape[index--] = mat1->shape[index1] >= mat2->shape[index2] ? mat1->shape[index1]: mat2->shape[index2];
	}
	expand(mat1, new_shape, max_dims);
	expand(mat2, new_shape, max_dims);
}

int main() {
	nmatrix* mat1 = malloc(sizeof(nmatrix));
	nmatrix* mat2 = malloc(sizeof(nmatrix));

	int ndims1;
	printf("Enter no. of dimensions: ");
	scanf("%d", &ndims1);
	if(ndims1 == 1) {
		int m1;	//dimensions from STDIN
		scanf("%d", &m1);

		mat1->ndims = 1;
		mat1->count = m1;
		mat1->shape = (size_t*)calloc(mat1->ndims, sizeof(size_t));
		mat1->shape[0] = m1;

		int* elements1 = (int*)calloc(mat1->count, sizeof(int));
		for(size_t index = 0; index < mat1->count; index++) {
			int curr_element;
			scanf("%d", &curr_element);	//elements from STDIN
			elements1[index] = curr_element;
		}
		mat1->elements = elements1;
	}
	else {
		int m1, n1;	//dimensions from STDIN
		scanf("%d%d", &m1, &n1);

		mat1->ndims = 2;
		mat1->count = (m1 * n1);
		mat1->shape = (size_t*)calloc(mat1->ndims, sizeof(size_t));
		mat1->shape[0] = m1, mat1->shape[1] = n1;

		int* elements1 = (int*)calloc(mat1->count, sizeof(int));
		for(size_t index = 0; index < mat1->count; index++) {
			int curr_element;
			scanf("%d", &curr_element);	//elements from STDIN
			elements1[index] = curr_element;
		}
		mat1->elements = elements1;
	}
	
	matrix_print(mat1);

	int ndims2;
	printf("Enter no. of dimensions: ");
	scanf("%d", &ndims2);
	if(ndims2 == 1) {
		int m2;	//dimensions from STDIN
		scanf("%d", &m2);

		mat2->ndims = 1;
		mat2->count = m2;
		mat2->shape = (size_t*)calloc(mat2->ndims, sizeof(size_t));
		mat2->shape[0] = m2;

		int* elements2 = (int*)calloc(mat2->count, sizeof(int));
		for(size_t index = 0; index < mat2->count; index++) {
			int curr_element;
			scanf("%d", &curr_element);	//elements from STDIN
			elements2[index] = curr_element;
		}
		mat2->elements = elements2;
	}
	else {
		int m2, n2;	//dimensions from STDIN
		scanf("%d%d", &m2, &n2);

		mat2->ndims = 2;
		mat2->count = (m2 * n2);
		mat2->shape = (size_t*)calloc(mat2->ndims, sizeof(size_t));
		mat2->shape[0] = m2, mat2->shape[1] = n2;

		int* elements2 = (int*)calloc(mat2->count, sizeof(int));
		for(size_t index = 0; index < mat2->count; index++) {
			int curr_element;
			scanf("%d", &curr_element);	//elements from STDIN
			elements2[index] = curr_element;
		}
		mat2->elements = elements2;
	}
	

	matrix_print(mat2);

	if(check_compatibility(mat1, mat2) == false) {
		printf("Matrices incompatible for broadcasting.\n");
		return 0;
	}

	broadcast(mat1, mat2);

	printf("Matrix 1 after broadcasting: \n");
	matrix_print(mat1);

	printf("Matrix 2 after broadcasting: \n");
	matrix_print(mat2);
	return 0;
}