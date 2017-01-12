#!/usr/bin/perl


my %hash_ = ();
my $num = 0;
my %hash_w = ();
my %hash_vr = ();
while(my $line = <>)
{
	chomp $line;
	#$line =~ s/\t/ /;## transfer oriquery to be a word, too.
	if ($line =~ /^(.*?)\t/)
	{
		$line = $1;
	}
	my @arr = split /\s+/, $line;
	my $vr = $arr[0];
	for(my $i = 1; $i < @arr; $i++)
	{
		my $w = $arr[$i];
		if($w =~ /^[£º£»¡¾¡¿\{\}£¨£©\(\)\,\.\?\!\@\#\$\%\^\&\*\_\+\=\-\~]+$/)
		{
			next;
		}
		if($i == $#arr)
		{
			if($w =~ /^(.*?)\t/)
			{
				$w = $1;
			}
		}
		$hash_{$w}{$vr}++;
		$hash_w{$w}++;
	}
	$hash_vr{$vr}++;
	if($num++ % 50000 == 0)
	{
		print $num."\n";
	}
}

## get the min and max vrnumber of hash_vr
my @arr = sort{$a <=> $b} values %hash_vr;
my $min = $arr[0];
my $max = $arr[$#arr];

my %hash_stop = ();
open(stopword, "./data_/stopword.punc") || die "error : fail to open stopword file !\n";
while(my $line = <stopword>)
{
	chomp $line;
	$hash_stop{$line}++;
}
close stopword;


open(fout,">model/word.weight.bin");
foreach my $w(keys %hash_)
{
	if (exists $hash_stop{$w})
	{
		next;
	}
	foreach my $vr(keys % {$hash_{$w}})
	{
		#my $weight = ($hash_{$w}{$vr}*100000)/($hash_w{$w}*$hash_vr{$vr});## make a penalty on low frequent but high probability words.
		my $weight = ($hash_{$w}{$vr})*$max/($hash_w{$w}*$hash_vr{$vr});## make a penalty on low frequent but high probability words.
		#my $weight = ($hash_{$w}{$vr})/($hash_w{$w});## make a penalty on low frequent but high probability words.
		my $wvr = $hash_{$w}{$vr};
		my $vrnum = $hash_w{$w};
		print fout $w."\t".$vr."\t".$wvr."\t".$vrnum."\t".$weight."\n";
	}
}
close fout;
