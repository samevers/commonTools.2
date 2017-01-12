#!/usr/bin/perl

while(my $line = <>)
{
	my @arr = split /\s+/, $line;
	if(@arr < 90)
	{
		next;
	}
	chomp $line;
	$line =~ s/ /\t/g;
	print $line."\n";
}
