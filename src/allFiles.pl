#!/usr/bin/perl

my $subdir;
while(my $line = <>)
{
	chomp $line;
	$line =~ s/\s+/ /g;

	#print $line."\n";
	if ($line =~ /^\.\/(.*?):$/)
	{
		$subdir = $1;
		#print "dir: ".$subdir."\n";
	}

	my @arr = split /\s+/, $line;
	my $filename;
	if(@arr == 9)
	{
		$filename = $arr[8];
		if($filename !~ /\.c|\.h|\.hpp|\.py|\.pl|\.sh|Makefile.am|\.java|\.jar/)
		{
			#print "file: ".$filename."\n";
			next;
		}
	}

	my $path;
	if($filename ne "" and $subdir ne "")
	{
		$path = $subdir."/".$filename;
		print $path."\n";
	}

	if($path ne "")
	{
		print $path."\n";
	}
}
