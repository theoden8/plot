#!/usr/bin/env perl

sub getarg { return scalar @ARGV ? shift @ARGV : shift; }

$a = getarg 0;
$b = getarg 0;
$diff = getarg 1000;
$step = getarg .1;

for(0..((2*$diff)/$step)) {
  $x = $step*($_-$diff);
  $r = $x**3 + $x*$a + $b;
  if($r >= 0) {
    $y = sqrt($r);
    print "$x $y\n$x -$y\n";
  }
}
