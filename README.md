# Plot

## Authors

Created by Kirill Rodriguez somewhen between 2014-2015.

## Program

### Purpose

Visualization (tiny tool useful for mathematics / statistics).

### Description

#### illustrator

Takes a sequence of points from **stdin** and plots on a graph.

#### graph

Generates a sequence of points from a hardcoded function and plots on a graph.

### State

The two repositories, because they are made one from another, still share many common lines of code, which is a bad programming practice.

### Bugs / Errors

For problems on compilation or runtime stage you are always welcome to raise an issue.

## Installation

### Prerequisites

* cmake
* make
* gcc/clang
* glut

### Compiling

	cmake .
	make

## Usage

	./_illustrator # (< file|<<EOF|<<<$(command)) stdin
	
----
	
	$EDITOR graph.cpp # edit calc functino and char *function (function name)
	make
	./_graph

## Disclaimer

Written in a quick-and-dirty way. Use at own risk.