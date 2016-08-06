#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 10000000
#define INTERVAL (1 << 16)

#define RAND mod((double)abs(rand()), sqrt(INTERVAL))
#define FUNC (abs((int)(RAND * RAND)))

double mod(double val, double div) {
	/* printf("%lf %lf %lf\n", val, div, val - ((int)(val / div) * div)); */
	return val - ((int)(val / div) * div);
}

main() {
	srand(time(NULL));
	int *count = malloc(sizeof(int) * INTERVAL);
	memset(count, 0, sizeof(int) * INTERVAL);
	assert(count != NULL);
	for(size_t i = 0; i < N; ++i) {
		const val = FUNC % INTERVAL;
		++count[val];
	}
	for(int i = 0; i < INTERVAL; ++i) {
		printf("%d\n", count[i]);
	}
	free(count);
}
