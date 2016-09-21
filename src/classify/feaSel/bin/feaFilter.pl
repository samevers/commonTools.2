#!/usr/bin/perl

while(my $line = <>)
{
	chomp $line;
	my @arr = split /\t/, $line;
	my $tmp = $arr[0];
	$tmp =~ s/\x{A3}(.)/chr(ord($1) - 128)/eg;
	$tmp =~ s/^\s+|\s+$//g;
	if($tmp !~ /^[\+_\.\-0-9a-zA-Z]+$/ and length($tmp) < 20)
	{
		print $line."\n";
	}
}
