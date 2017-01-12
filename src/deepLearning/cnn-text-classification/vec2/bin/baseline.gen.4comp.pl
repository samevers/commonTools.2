#!/usr/bin/perl
# input : 10w.txt.out.new.1112
open(orifile, "../10w.txt") || die "error : fail to open file <10w.txt> !\n";
open(vrqo, $ARGV[0]) || die "error : fail to open file $ARGV[0]!\n";
#open(vrqo, "../10w.txt.model.baseline") || die "error : fail to open file <10w.txt.out.new.1112> !\n";
#open(vrqo, "../10w.txt.out.new.1112") || die "error : fail to open file <10w.txt.out.new.1112> !\n";
while(my $line = <vrqo>)
{
	chomp $line;
#print $line."\n";
	my @arr = ($line =~ /classTag=\"(.*?)\"/g);
	my $classtag = "";
	if (@arr > 0)
	{
		for(my $i = 0; $i < @arr; $i++)
		{
			if($arr[$i] =~ /EXTERNAL/)
			{
				next;
			}
			if($arr[$i] =~ /INTERNAL\.(.*?)\./)## Ö»¿¼ÂÇÄÚ²¿vr
			{
				$classtag .= $1." ";
			}
		}
	}
	my $oriline = <orifile>;
	chomp $oriline;
	print $oriline."\t".$classtag."\n";

}
close vrqo;
close oriline;
