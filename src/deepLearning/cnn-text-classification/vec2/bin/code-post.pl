#!/usr/bin/perl

use Encode;

while(my $line = <>)
{
	chomp $line;
	my @array = split/\s+/, $line;
	foreach my $chunk(@array)
	{
		my $tmp = decode("gbk", $chunk);
		my @arr = split//, $tmp;
		foreach my $w(@arr)
		{
			if($w =~ /^[0-9a-zA-Z\p{Han}]+$/)
			{
				print encode("gbk", $w);
			}
		}
		print " ";
	}
	print "\n";
}
