#!/usr/bin/perl

## README: To delete illegual query that in file "video.query.*"

while(my $line = <>)
{
	chomp $line;
	$line =~ s/\s+$//;
	my $illegual = 1;
	my @arr = split /\s+/, $line;
	foreach my $key(@arr)
	{
		#print $key."\t".length($key)."\n";
		if(length($key) != 2)
		{
			$illegual = 0;
			break;
		}
	}
	if ($line =~ /��$/ and length($line) < 10 or
			$illegual == 1
			#$line =~ /�|��|�|��|��|��|��|��|��|��|�|��|��|�|��|�|��|��|�|��|�|��|��|��|��|��|�|��/
			#$line =~ /�|�|��|��|�|��|��|��|�|��|��|�|Կ|��|��|�|�|��|��/
			)
	{
		next;
		#print $line."\n";
	}else
	{
		print $line."\n";
	}
}
#
