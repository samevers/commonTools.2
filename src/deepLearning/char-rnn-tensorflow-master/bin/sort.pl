#! /usr/bin/perl 
############################################
#
# Author: 
# Create time: 2016 12ÔÂ 22 15Ê±59·Ö55Ãë
# E-Mail: @sogou-inc.com
# version 1.0
#
############################################
my %hash_ = ();
my %hash_pv = ();
while(my $line = <>)
{
  chomp $line;
  my @arr = split /\t/, $line;
  if($arr[1] =~ /e-/)
  {
    next;
  }
  $hash_{$arr[0]} = $arr[1];
  $hash_pv{$arr[0]} ++;
}

my $size = keys %hash_;
print "unit key size = ".$size."\n";

foreach my $key(sort{$hash_{$b} <=> $hash_{$a}} keys %hash_)
{
  my $pv = $hash_pv{$key};
  for(my $i = 0; $i < $pv; $i++)
  {
    print $key."\t".$hash_{$key}."\n";
  }
}
