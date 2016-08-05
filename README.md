# Plot

## Authors

Created by Kirill Rodriguez somewhen between 2014-2015.

## Program

### Purpose

Tiny plotting utilities that are handy for visualising numbers and exploring mathematical functions.

### Description

#### plot_fractal

Plots a fractal. Use `hjkl-=mM` to scale the view and the fractal itself.

Below is obtained illustration of mandelbrot set:

![fractal](./screenshots/mandelbrot.png)

#### illustrator

![illustrator_prime_number_theorem](./screenshots/illustrator.png)

Plots a sequence of points from **stdin** (above: prime number theorem illustration: `(pi(x) / (x / log(x)) - 1`, squeezed in width).

#### complex_in

Plots a sequence of set numbers (from **stdin**) on complex plane.

#### graph

![graph](./screenshots/graph.png)

Plots a hardcoded function (above: `log(n)`)

#### graph_i

Plots **f(z)** on complex plane where **z** is a complex number. It might behave weirdly because $$f(z) \in{G} \not\rightarrow z \in{G}$$ where **G** is the grid. 

#### gen/

The gen/ folder contains various generators, such as of some kinds of fractals, prime numbers etc. Those are to be piped to `illustrator` or `complex_in` programs for plotting as they are written to produce input following the necessary format.

### Bugs / Errors

For problems on compilation or runtime stage you are always welcome to raise an issue.

### Contribution

In case you have a good suggestion, you are always welcome to make a pull request.

## Installation

### Prerequisites

* cmake
* make
* gcc/clang
* GLUT

### Compiling

	cmake . && make

## Usage

	./bin/illustrator # ( < file | <<EOF | <<< command ) stdin
	
----

	$EDITOR graph.cpp # edit calc function and char *function (function name) variable
	make
	./bin/graph

## Note

Use at own risk. Speed and convenience are the first priorities.