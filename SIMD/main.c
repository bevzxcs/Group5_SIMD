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
	size_t ARRAY_SIZE = 1 << 20; // change to 30 in final version. TO-DO: have diff ARRAY_SIZEs for 26 and 30 kernels
	size_t ARRAY_BYTES = ARRAY_SIZE * sizeof(int32_t);
	int i;
	printf("Number of elements: %zd\n", ARRAY_SIZE);

	// TO-DO: update to queryperformancefrequency
	clock_t start, end;
	double time_taken;
	double average_time = 0;

	int32_t* x, y;
	x = (int32_t*)malloc(ARRAY_BYTES);
	y = (int32_t*)malloc(ARRAY_BYTES);

	for (i = 0; i < ARRAY_SIZE; i++) {
		x[i] = rand();
	}

	// C VERSION
	for (i = 0; i <= 90; i++) {
		if (i <= 30) {
			start = clock();
			//c_stencil(ARRAY_SIZE, x, &y);
			end = clock();
			time_taken = ((double)(end - start) * 1e3) / CLOCKS_PER_SEC; //TO-DO: use a diff function for better accuracy
			average_time = average_time + time_taken;
			printf("Time in C = %f ms\n", time_taken);

			if (i == 30) {
				printf("Average Time in C (2^20): %f ms\n", average_time / 30);
				average_time = 0;
			}
		}

		else if (i > 30 && i <= 60) {
			if (i == 31) {
				ARRAY_SIZE = 1 << 26;
				ARRAY_BYTES = ARRAY_SIZE * sizeof(int32_t);
				printf("\nNumber of elements: %zd\n", ARRAY_SIZE);
			}

			// body. -30 indeces

			if (i == 60) {
				printf("Average Time in C (2^26): %f ms\n", average_time / 30);
				average_time = 0;
			}
		}

		else if (i > 60 && i <= 90) {
			if (i == 61) {
				ARRAY_SIZE = 1 << 30;
				ARRAY_BYTES = ARRAY_SIZE * sizeof(int32_t);
				printf("\nNumber of elements: %zd\n", ARRAY_SIZE);
			}

			// body. -60 indeces

			if (i == 90) {
				printf("Average Time in C (2^30): %f ms\n", average_time / 30);
				average_time = 0;
			}
		}
	}



	return 0;
}