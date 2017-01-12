#!/usr/bin/perl

my %hash_ = ();
while(my $line = <>)
{
	chomp $line;
	my @arr = split /\s+/, $line;
	for(my $i = 0; $i < @arr; $i++)
	{
		my $w = $arr[$i];
		if($w =~/^[0123456789��������������������\~\!\@\$\#\%\^\&\*\(\)\_\+\|\"\:\>\?\<\`\=\-\]\[\\\'\;\.\,\/\~\������%@#����&*��������\+\|\}\{����������\-\=�������������������ࣱ�������磥�ޣ��������ߣ������ݣۣܣ�����������������������������]+$/)
		{
			next;
		}
		if(not exists $hash_{$w})
		{
			print $w."\n";
			$hash_{$w}++;
		}
	}
}

