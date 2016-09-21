#!/usr/bin/perl

while(my $line = <>)
{
	chomp $line;
	$line=~ s/Í¼Æ¬$|ÊÓÆµ$//;
	print $line."\n";
}
