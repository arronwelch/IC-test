#!/pkg/qct/bin/perl

use File::Basename;
use Getopt::Long qw/:config pass_through/;

GetOptions(
           'help|?|h'     => \$help_flag,
           "i|t|l=s"      => \$input,
          );

if ($help_flag) {
  print "\n  countfix.pl fixes the character count of the timing and levels file compatible with Smartest\n";
  print "\tUsage: %countfix.pl -i <timing_file>\n";
  print "\tUsage: %countfix.pl -i <levels_file>\n";
  print "\n		-i : for character count fixing timing and levels files";
  print "\n 		-h : for help\n\n";
  exit;
}
die "Cannot find input '$input' to count fix.\nExiting...\n" if ($input eq "" or !-e "$input");

system("cp $input $input.bak") == 0 or die "Cannot back up input '$input'\n";
open my $IN, "$input.bak" or die "Cannot open input '$input' for reading.\n";
open my $OUT, ">$input" or die "Cannot open input '$input' for writing.\n";
print STDOUT "Countfixing '$input'\n";
while (<$IN>) {
  if (/EQSP\s+\S+\,\S+\,#\d+/ .. /^\@/) {
    if (/EQSP\s+(\S+\,\S+)\,#\d+/) {
      $sec_type = $1;
      s/EQSP\s+\S+\,\S+\,#\d+//;
      $str = $_;
    }
    elsif (/^\@/) {
      my $length = sprintf "9%09d",length($str)+1;
      print $OUT "EQSP $sec_type,#$length$str@\n";
    }
    else {
      $str .= $_;
    }
  }
  else {
    print $OUT $_;
  }
}
close($IN);
close($OUT);
print STDOUT "Countfix done\n";
