#include <stdio.h>
#include <math.h>

main() {
	int i = 0, prime;
	while(scanf(" %d", &prime) != EOF) {
		++i;
		double nlogn = (double)i * log((double)i);
		printf("%lf\n", (double)prime / nlogn - 1.);
	}
}
