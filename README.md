# Plot

![Logo](./screenshots/screenshot.png)

## Authors

Created by Kirill Rodriguez somewhen between 2014-2015.

## Program

### Purpose

Tiny plotting utilities that are handy for visualising numbers and exploring mathematical functions.

### Description

#### illustrator

Plots a sequence of points from **stdin**.

#### complex_in

Plots a sequence of set numbers (from **stdin**) on complex plane.

#### graph

Plots a hardcoded function.

#### graph_i

Plots **f(z)** on complex plane where **z** is a complex number. It might behave weirdly because $$f(z) \in{G} \not\rightarrow z \in{G}$$ where **G** is the grid. 

#### plot_fractal

Plots a fractal. Use `hjkl-=mM` to scale the view and the fractal itself.

#### gen/

The gen/ folder contains various generators, such as of mandelbrot set, prime numbers etc. Those are to be piped to `illustrator` or `complex_in` programs for plotting as they are written to produce input following the necessary format.

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