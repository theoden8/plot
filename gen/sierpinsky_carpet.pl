#!/usr/bin/env perl

use strict;
use warnings;

die if scalar @ARGV != 1;

my ($max_iters) = @ARGV;


sub pixel_is_filled {
	my($x, $y) = @_;

	while($x > 0 || $y > 0) {
		if($x % 3 == 1 && $y % 3 == 1) {
			return 1;
		}
		$x = int($x / 3);
		$y = int($y / 3);
	}
	return 0;
}


for(my $X = 0; $X < $max_iters; ++$X) {
	for(my $Y = 0; $Y < $max_iters; ++$Y) {
		print "$X $Y\n" if pixel_is_filled $X, $Y;
	}
}
