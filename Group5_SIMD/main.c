// ---- GROUP 5 ---- //
// CAI, Edison       //
// DEQUICO, Beverly  //
// LA'O, Erin        //
// RELUCIO, Jan      //
// ----------------- //

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <windows.h>
#include <time.h>

extern void nonsimd_stencil();
extern void simdxmm_stencil();
extern void simdymm_stencil();

void c_stencil(size_t n, int32_t* x, int32_t** y) {
	int i;
	int index = 0;

	for (i = 0; i < n; i++) {
		// make sure all indeces are valid
		if ((i - 3 >= 0) && ((i + 3) <= (n - 1))) {
			*y[index] = x[i - 3] + x[i - 2] + x[i - 1] + x[i] + x[i + 1] + x[i + 2] + x[i + 3];
			index++;
		}
	}
}

int main(int argc, char* argv[]) {
	const size_t ARRAY_SIZE = 1 << 28; // change to 30 in final version
	const size_t ARRAY_BYTES = ARRAY_SIZE * sizeof(int32_t);
	int i;
	printf("Number of elements: %zd", ARRAY_SIZE);

	// update to queryperformancefrequency
	clock_t start, end;
	double time_taken;

	int32_t* x, y;
	x = (int32_t*)malloc(ARRAY_BYTES);
	y = (int32_t*)malloc(ARRAY_BYTES);

	//c_stencil(ARRAY_SIZE, x, &y);

	for (i = 0; i < ARRAY_SIZE; i++) {
		x[i] = 1.0;
	}

	for (i = 0; i < 30; i++) {
		start = clock();
		c_stencil(ARRAY_SIZE, x, &y);
		end = clock();
		time_taken = ((double)(end - start) * 1e3) / CLOCKS_PER_SEC;
		printf("Time in C = %f ms\n", time_taken);
	}

	return 0;
}