#! /usr/bin/perl
############################################
#
# Author: 
# Create time: 2016 12ÔÂ 22 14Ê±36·Ö12Ãë
# E-Mail: @sogou-inc.com
# version 1.0
#
############################################
my $imageScore;
my $webScore;
my $thres;
my $query;
while(my $line = <>)
{
  chomp $line;
  if($line =~ /\tIMAGE|\tWEB/)
  {
    if($line =~ /^(.*?)\t/)
    {
      $query = $1;
    }
    next;
  }
  if($line =~ /imageScore= (.*?) webScore= (.*?) thres= (.*?)$/)
  {
    $imageScore = $1;
    $webScore = $2;
    $thres = $3;
    print $query."\t".$imageScore."\t".$webScore."\t".$thres."\n";
  }
}
