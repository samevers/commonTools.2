#!/usr/bin/perl

while(my $line = <>){
	chomp $line;
	my @arr = split /\t/, $line;
	my $total = 0;
	my $big = 0;
	my $small = 0;
	for(my $i = 0; $i < @arr; $i++)
	{
		#$total = $total + $arr[$i];
		if($big < $arr[$i])
		{
			$big = $arr[$i];
		}
		if($small > $arr[$i])
		{
			$small = $arr[$i];
		}
	}
	print "²î:",($big-$small)."\tsmall:$small\tbig:$big\n";
}
