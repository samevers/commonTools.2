#! /usr/bin/perl -w
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
my $query;
while(my $line = <>)
{
  chomp $line;
  if($line =~ /imageid/ or $line eq "")
  {
    next;
  }
  if($line =~ /imageScore = \', (.*?)\)/)
  {
    $imageScore = $1;
    next;
  }
  if($line =~ /webScore = \', (.*?)\)/)
  {
    $webScore = $1;
    next;
  }
  if($line =~ /^(.*?)\t(IMIAGE|WEB)$/)
  {
     $query = $1;
  }

  my $thres = $imageScore/($webScore+$imageScore);
  print $query."\t".$thres."\n";
}
