#!/usr/bin/perl

while(my $line = <>)
{
	chomp $line;
	my @arr = split /\s+/, $line;
	$line =~ s/^(.*?)\s+//;
	print $line."\n";
}
