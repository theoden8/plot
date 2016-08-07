#include <cassert>
#include <cmath>
#include <cstdlib>

#include "FractalIterLine.hpp"

real_t FractalIterLine::size() const {
	return std::min(width, height);
}
