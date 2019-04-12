#include <stdio.h>
#include <stdlib.h>

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
			printf("%d\n", mat->elements[ind++]);
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

int main() {
	int m, n;	//dimensions from STDIN
	scanf("%d%d", &m, &n);

	nmatrix* mat = malloc(sizeof(nmatrix));

	mat->ndims = 2;
	mat->count = (m * n);
	mat->shape = (size_t*)calloc(mat->ndims, sizeof(size_t));
	mat->shape[0] = m, mat->shape[1] = n;

	int* elements = (int*)calloc(mat->count, sizeof(int));
	for(size_t index = 0; index < mat->count; index++) {
		int curr_element;
		scanf("%d", &curr_element);	//elements from STDIN
		elements[index] = curr_element;
	}
	mat->elements = elements;

	matrix_print(mat);
	
	int* indices = (int*)calloc(mat->ndims, sizeof(int));
	scanf("%d%d", &indices[0], &indices[1]);	//index from STDIN

	size_t index_in_flat_list = get_index(mat, indices);
	printf("index: %d\n", (int)index_in_flat_list);

	printf("value: %d\n", mat->elements[index_in_flat_list]);
	return 0;
}