#!/bin/perl
use Encode;


open(stopfin, "data_/stopword.ter");
my %stop_ = ();
while(my $line = <stopfin>)
{
	chomp $line;
	$stop_{$line}++;
}
close stopfin;



open(baseline, $ARGV[0]); # "data_/10w.txt.out.new.1112.4comp");
open(sams, $ARGV[1]); #"withExtend/sams_out");

open(outadd,">tmp_/add.out");
open(outreduce,">tmp_/reduce.out");

my $num = 1;
###########################################################################
my %hash_baseline = ();
while(my $line = <baseline>)
{
	chomp $line;
	my $classtag;
	my $query;
	if($line =~ /^(.*?)\t(.*?)$/)
	{
		$query = $1;
		$classtag = $2;
	}
	if($query ne "" and $classtag ne "")
	{
		$hash_baseline{$query} = $classtag;
	}
}
close baseline;
##################################
my %hash_new = ();
while(	my $line1 = <sams>)
{
	chomp $line1;
	#i################################ judge chinese
	my $tmp = decode("gbk",$line1);
	if($tmp !~ /\p{han}+/)
	{
		next;
	}
	my @arr = split /:\s+/,$line1;
	my $pre = $arr[0];
	my $sub = $arr[1];
	my $query;
	if($pre =~ /\<(.*?)\>/)
	{
		$query = $1;
	}else
	{
		print "INFO : no query abtained !\n";
		next;
	}
	my $vrsam = $sub;
	$vrsam =~ s/[\.0-9]//g;
	$vrsam =~ s/\t+/ /g;
	$vrsam = uc($vrsam);
	# limit query too short
	if(length($query) < 4)
	{
		next;
	}
	my $classtag;
	if(exists $hash_baseline{$query})
	{
		$classtag = $hash_baseline{$query};
	}
	if ($vrsam !~ /NONE/)
	{
		$hash_new{$query} = $line1;  ## record new output
		if(not exists $hash_baseline{$query})
		{
				print outadd "query: ".$query."\n";
				print outadd "baseline: "." <none>\n";
				print outadd "new: add<all> ".$line1."------0\n\n";
				next;	## continue
		}
		my @vrs = split/\s+/, $vrsam;
		foreach my $vr(@vrs)
		{
			if ($classtag !~ /$vr/ and $vr ne "")
			{
				print outadd "query: ".$query."\n";
				print outadd "baseline: ".$classtag."-------1\n";
				print outadd "new: add<$vr> ".$line1."-------2\n\n";
			}
		}
	}
	my @base_vr = split /\s+/, $classtag;
	foreach my $vr(@base_vr)
	{
		if($vrsam !~ /$vr/ and $vr ne "")
			{
				print outreduce "query: ".$query."\n";
				print outreduce "baseline: ".$classtag."------3\n";
				print outreduce "new: reduce<$vr> ".$line1."------4\n\n";
			}
	}
	$num++;
}

## make an addition of baseline adding vrs.
foreach my $q(keys %hash_baseline)
{
	if(not exists $hash_new{$q})
	{
		print outreduce "query: ".$q."\n";
		print outreduce "baseline: ".$hash_baseline{$q}."----5\n";
		print outreduce "new: reduce<none> "."-------6\n\n";
	}
}
close sams;
close outadd;
close outreduce;
