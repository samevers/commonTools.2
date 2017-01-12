#!/usr/bin/perl
## This code is no use.
def Build_file($vrtype){
	my $Handl = $vrtype."FIN";
	my $OutfileName = $vrtype.".predict";
	open($Handl,">".$OutfileName) || die "ERROR : fail to build $vrtype file !\n";
}

def print_($vrchunk){
	my $vrterm = $$vrchunk;
	if($vrterm =~ /image/)
	{
	}
}
def main(){

	while(my $line = <>)
	{
		chomp $line;
		my $query;
		if($line !~ /outcome\]/)
		{
			next;
		}

		if($line =~ /\<(.*?)\>/)
		{
			$query = $1;
			if($line =~ /:\s+(.*)$/)
			{
				my $vrchunk = $1;
				#my @arr = split /\t/, $vrchunk;
				print_(\$vrchunk);
			}
		}else
		{
			next;
		}
	}
}
