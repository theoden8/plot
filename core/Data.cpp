#include "Data.hpp"


void read_data(std::vector <real_t> &data) {
	static real_t value;
	while(scanf(" %lf", &value) != EOF)
		data.push_back(value);
}


void read_data(std::vector <complex_t> &data) {
	static real_t re, im;
	while(scanf(" %lf %lf", &re, &im) != EOF)
		data.push_back(complex_t(re, im));
}
