#! /usr/bin/perl
use Encode;
############################################
#
# Author: 
# Create time: 2016 12�� 21 17ʱ33��12��
# E-Mail: @sogou-inc.com
# version 1.0
#
############################################
while(my $line = <>)
{
  chomp $line;
  print decode("gbk", $line)."\n";
  next;
  if($line =~ /^V|^sV/)
  {
    $line =~ s/^sV//;
    $line =~ s/^V//;
    print encode("gbk",$line)."\n";
  }
}
