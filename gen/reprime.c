#include <stdio.h>
#include <math.h>

// maps a list of prime numbers (stdin) into a list of
//	P(i) / (i / log(i)) - 1
main() {
	int i = 0, prime;
	while(scanf(" %d", &prime) != EOF) {
		++i;
		double nlogn = (double)i * log((double)i);
		printf("%lf\n", (double)prime / nlogn - 1.);
	}
}
