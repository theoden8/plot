#include <cmath>

#include "Types.hpp"
#include "Functions.hpp"

complex_t zriemann(const complex_t &z, const size_t &n) {
	static const complex_t ONE(1.);
	complex_t sum(0., 0.);
	const complex_t N = (complex_t)n;
	for(int i = 1; i < n; ++i)
		sum += ONE / pow(N, z);
	return sum;
}
