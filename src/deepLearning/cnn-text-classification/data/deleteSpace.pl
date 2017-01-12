#!/usr/bin/perl

while(my $line = <>)
{
	chomp $line;
	$line =~ s/\s+//g;
	$line =~ s/\x{A3}(.)/chr(ord($1) - 128)/eg;
	print $line."\n";
}

