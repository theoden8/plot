#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Thanks to Codereview community and, especially, to JS1, for helping with the
// implementation, which features a wheel (built-in optimisation) of 2 and 3.
//
// http://codereview.stackexchange.com/questions/112901/eratosthenes-sieve-optimized-in-c

#define N 1000000000

typedef struct _int_it {
	int bit_number, index_i, bit_i;
} int_it;

main(int argc, char *argv[]) {
	int	size_of_array = (N / 24 + 1);
	uint32_t *primes = malloc(size_of_array);

	// The bits in primes follow this pattern:
	//
	// Bit 0 = 5, bit 1 = 7, bit 2 = 11, bit 3 = 13, bit 4 = 17, etc.
	//
	// foreven bits, bit n represents 5 + 6*n
	// forodd  bits, bit n represents 1 + 6*n
	memset(primes , 0xff, size_of_array);

	int sqrt_N = sqrt(N);
	for(int i = 5; i <= sqrt_N; i += 4) {
		int
			bit_number_i = i / 3 - 1,
			index_i = bit_number_i >> 5,
			bit_i   = 1 << (bit_number_i & 0x1f);
		if(primes[index_i] & bit_i) {
			const int increment = 2 * i;
			for(int j = i * i; j < N; j += increment) {
				int
					bit_number_j = j / 3 - 1,
					index_j = bit_number_j >> 5,
					bit_j   = 1 << (bit_number_j & 0x1f);

				primes[index_j] &= ~bit_j;

				j += increment;
				if(j >= N)
					break;

				bit_number_j = j / 3 - 1;
				index_j = bit_number_j >> 5;
				bit_j   = 1 << (bit_number_j & 0x1f);

				primes[index_j] &= ~bit_j;

				// Skip multiple of 3.
				j += 1 * increment;
			}
		}
		i += 2;
		bit_i <<= 1;
		if(primes[index_i] & bit_i) {
			const int increment = 2 * i;
			for(int j = i * i; j < N; j += increment) {
				int
					bit_number_j = j / 3 - 1,
					index_j = bit_number_j >> 5,
					bit_j = 1 << (bit_number_j & 0x1f);

				primes[index_j] &= ~bit_j;

				// Skip multiple of 3.
				j += 2 * increment;
				if(j >= N)
					break;

				bit_number_j = j / 3 - 1;
				index_j = bit_number_j >> 5;
				bit_j = 1 << (bit_number_j & 0x1f);

				primes[index_j] &= ~bit_j;
			}
		}
	}

	// Initial count includes 2, 3.
	printf("2\n3\n");
	/* int count = 2; */
	for(int i = 5; i < N; i += 6) {
		int
			bit_number_i = i / 3 - 1,
			index_i = bit_number_i >> 5,
			bit_i = 1 << (bit_number_i & 0x1f);
		if(primes[index_i] & bit_i) {
			printf("%d\n", (bit_number_i + 1) * 3 + 2);
			/* ++count; */
		}
		++bit_number_i;
		bit_i <<= 1;
		if(primes[index_i] & bit_i) {
			printf("%d\n", (bit_number_i + 1) * 3 + 1);
			/* ++count; */
		}
	}
	/* printf("\n%d\n", count); */

	free(primes);
}
