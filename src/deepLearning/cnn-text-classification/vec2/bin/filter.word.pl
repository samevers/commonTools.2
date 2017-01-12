#!/usr/bin/perl

while(my $line = <>)
{
	chomp $line;
	my @arr = split /\s+/, $line;
	for(my $i = 0; $i < @arr; $i++)
	{
		if($arr[$i] =~ /^[£±£²£³£´£µ£¶£·£¸£¹£°0123456789\!\~\@\#\$\%\^\&\*\(\)\_\+\|\"\:\>\<\?\`\-\=\]\[\\\;\'\/\.\,]+$/)
		{
			print $arr[$i]."----\n";
			next;
		}
		print $arr[$i]." ";
	}
	print "\n";
}
