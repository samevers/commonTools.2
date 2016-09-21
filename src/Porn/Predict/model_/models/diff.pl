#!/usr/bin/perl

print $ARGV[0]."\t".$ARGV[1]."\n";
open(fin1, $ARGV[0]) || die "error: argv[0] is null\n";
open(fin2, $ARGV[1])|| die "error: argv[1] is null\n";

while(my $line1 = <fin1>)
{
	chomp $line1;
	$hash1{$line1} ++;
}
fin1.close();


while(my $line1 = <fin2>)
{
	chomp $line1;
	$hash2{$line1} ++;
}
fin2.close();


### diff
foreach my $k (keys %hash2)
{
	if(not exists $hash1{$k})
	{
		print $k."\t-----------\n";
	}
}
### diff
foreach my $k (keys %hash1)
{
	if(not exists $hash2{$k})
	{
		print $k."\t============\n";
	}
}
