#!/usr/bin/perl

my $num = 1;
while(my $line  = <>)
{
	chomp $line;
	if($num++ < 6387335)
	{
		next;
	}else
	{
		print $line."\n";
		exit();
	}
}
