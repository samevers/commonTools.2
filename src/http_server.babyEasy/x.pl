#!/usr/bin/perl


while(my $line = <>)
{
	chomp $line;
	my @arr = split /\\t/, $line;
	for(my $i = 0;$i <@arr; $i++)
	{
		if($arr[$i] == "0")
		{
			next;
		}else
		{
			print $arr[$i],"\\t";
		}
	}

}
print "\n";
