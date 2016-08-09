#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Thanks to Codereview community and, especially, to JS1, for helping with the
// implementation, which features a wheel (built-in optimisation) of 2 and 3.
//
// http://codereview.stackexchange.com/questions/112901/eratosthenes-sieve-optimized-in-c

#define N 1000000

typedef struct _int_it {
	int
		bit_number,
		index,
		bit;
} int_it;


#define ITER(i) i##_it

#define BIT_NUMBER(i) ITER(i).bit_number
#define IDX(i) ITER(i).index
#define BIT(i) ITER(i).bit

#define SET_ITER(i) \
	{ \
		BIT_NUMBER(i) = i / 3 - 1; \
		IDX(i) = BIT_NUMBER(i) >> 5; \
		BIT(i) = 1 << (BIT_NUMBER(i) & 0x1f); \
	}

#define INIT_INT_IT(iter) int_it ITER(iter); SET_ITER(iter)


#define ARRAY primes
#define INDEX(i) ARRAY[IDX(i)]

main(int argc, char *argv[]) {
	static int size_of_array = (N / 24 + 1);
	uint32_t *ARRAY = malloc(size_of_array);

	// The bits in ARRAY follow this pattern:
	//
	// Bit 0 = 5, bit 1 = 7, bit 2 = 11, bit 3 = 13, bit 4 = 17, etc.
	//
	// foreven bits, bit n represents 5 + 6*n
	// forodd  bits, bit n represents 1 + 6*n
	memset(ARRAY , 0xFF, size_of_array);

	const int sqrt_N = sqrt(N);
	for(int i = 5; i <= sqrt_N; i += 4) {
		INIT_INT_IT(i);
		if(INDEX(i) & BIT(i)) {
			const int increment = 2 * i;
			for(int j = i * i; i < N; j += increment) {
				INIT_INT_IT(j);
				INDEX(j) &= ~BIT(j);

				j += increment;
				if(j >= N)
					break;

				SET_ITER(j);
				INDEX(j) &= ~BIT(j);

				// Skip multiple of 3.
				j += 1 * increment;
			}
		}
		i += 2;
		BIT(i) <<= 1;
		if(INDEX(i) & BIT(i)) {
			const int increment = 2 * i;
			for(int j = i * i; i < N; j += increment) {
				INIT_INT_IT(j);
				INDEX(j) &= ~BIT(j);

				// Skip multiple of 3.
				j += 2 * increment;
				if(j >= N)
					break;

				SET_ITER(j);

				INDEX(j) &= ~BIT(j);
			}
		}
	}

	// Initial count includes 2, 3.
	printf("2\n3\n");
	/* int count = 2; */
	for(int i = 5; i < N; i += 6) {
		INIT_INT_IT(i);
		if(INDEX(i) & BIT(i)) {
			printf("%d\n", (BIT_NUMBER(i) + 1) * 3 + 2);
			/* ++count; */
		}
		++BIT_NUMBER(i);
		BIT(i) <<= 1;
		if(INDEX(i) & BIT(i)) {
			printf("%d\n", (BIT_NUMBER(i) + 1) * 3 + 1);
			/* ++count; */
		}
	}
	/* printf("\n%d\n", count); */

	free(ARRAY);
}
