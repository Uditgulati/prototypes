#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void get_slice(nmatrix* mat, nmatrix* slice, int dims_count, size_t* indices) {
	slice->ndims = dims_count;
	slice->count = 1;
	slice->shape = (size_t*)calloc(slice->ndims, sizeof(size_t));
	size_t i = 0;
	for(size_t ind = 0; ind < mat->ndims; ind++) {
		size_t diff = (indices[2*ind + 1] - indices[2*ind] + 1);
		if(diff == 1)
			continue;
		slice->shape[i++] = diff, slice->count *= diff;
	}
	int* elements = (int*)calloc(slice->count, sizeof(int));
	size_t ind = 0;
	for(int i = indices[0]; i <= indices[1]; i++) {
		for(int j = indices[2]; j <= indices[3]; j++) {
			int* element_indices = (int*)calloc(mat->ndims, sizeof(int));
			element_indices[0] = i, element_indices[1] = j;
			elements[ind++] = mat->elements[get_index(mat, element_indices)];
		}
	}
	slice->elements = elements;
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

	char range1[20], range2[20];

	scanf("%s", range1);
	scanf("%s", range2);

	int dims_count = 0;

	size_t* ranges = (size_t*)calloc(2 * mat->ndims, sizeof(size_t));

	if(strchr(range1, ':') != NULL) {
		ranges[0] = 0;
		ranges[1] = mat->shape[0] - 1;
		char part1[20], part2[20];
		size_t i = 0, ind;
		for(ind = 0; i < 20; i++) {
			if(range1[i] == ':')
				break;
			part1[ind++] = range1[i];
		}
		part1[ind] = '\0';
		i++;
		for(ind = 0; i < 20; i++) {
			if(range1[i] == '\0')
				break;
			part2[ind++] = range1[i];
		}
		part2[ind] = '\0';
		if(part1[0] != '\0')
			ranges[0] = atoi(part1);
		if(part2[0] != '\0')
			ranges[1] = atoi(part2);
		dims_count++;
	}
	else {
		ranges[0] = ranges[1] = atoi(range1);
	}

	if(strchr(range2, ':') != NULL) {
		ranges[2] = 0;
		ranges[3] = mat->shape[1] - 1;
		char part1[20], part2[20];
		size_t i = 0, ind;
		for(ind = 0; i < 20; i++) {
			if(range2[i] == ':')
				break;
			part1[ind++] = range2[i];
		}
		part1[ind] = '\0';
		i++;
		for(ind = 0; i < 20; i++) {
			if(range2[i] == '\0')
				break;
			part2[ind++] = range2[i];
		}
		part2[ind] = '\0';
		if(part1[0] != '\0')
			ranges[2] = atoi(part1);
		if(part2[0] != '\0')
			ranges[3] = atoi(part2);
		dims_count++;
	}
	else {
		ranges[2] = ranges[3] = atoi(range2);
	}

	nmatrix* slice = (nmatrix*)malloc(sizeof(nmatrix));;
	get_slice(mat, slice, dims_count, ranges);

	printf("Slice is:\n");
	matrix_print(slice);
	return 0;
}