#pragma once

#include "Fractal.hpp"

#define LINEAR(NAME) class NAME : public FractalIterLine
FRACTAL(FractalIterLine) {
protected:
	typedef std::pair <complex_t, complex_t> line_t;
	std::vector <line_t> lines_ = {};
	int last_level = 0;
	real_t last_size = -1;

protected:
	real_t size() const;
	virtual void reset() = 0;
	virtual void increase_level() = 0;
	virtual void decrease_level() = 0;
};


LINEAR(KochsFlake) {
	static size_t no_lines(int level);
	void reset();
	void increase_level();
	void decrease_level();
public:
	void Draw();
};
