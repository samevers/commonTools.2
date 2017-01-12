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
	if ($line =~ /Íø$/ and length($line) < 10 or
			$illegual == 1
			#$line =~ /ç”|µå|ç¾|Žå|›½|ãÖ|Ÿé|ãÇ|’æ|˜¥|ç›|‘ç|‹±|é£|º‘|ä¹|°‘|Š¯|ç”|µå|ç¾|Žå|›½|ãÖ|Ÿé|êÇ|å®|‰å/
			#$line =~ /ä¸|å|»å|®š|æƒ|ãÓ|™ç|ˆ±|å|ç|”·|å­|Ô¿|ç|”·|å­|æ¨|»¿|”±/
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
