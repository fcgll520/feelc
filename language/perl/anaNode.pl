#!/usr/bin/perl -w

use JSON;
use Data::Dumper;
use Encode;

sub analyse
{
    my ($infos) = @_;

    my $result = {};

    my $nodes = $infos->{"nodes"};

    foreach my $item ( @$nodes ) {
        analyse_isp_and_province_dist($result, $item);
    }
    #print Dumper($result) . "\n";
    print_isp_and_province_dist($result);
}

sub analyse_isp_and_province_dist
{
    my ($result, $item) = @_;

    unless (exists $result->{"isp_and_province_dist"}) { $result->{"isp_and_province_dist"} = {}; }

    my $tmp_result = $result->{"isp_and_province_dist"};
    my $isp = $item->{"isp"};
    my $province = $item->{"province"};

    unless (exists $tmp_result->{$isp}) { $tmp_result->{$isp} = {}; }
    unless (exists $tmp_result->{$isp}->{$province}) { $tmp_result->{$isp}->{$province} = 0; }
    $tmp_result->{$isp}->{$province} += 1;
}

sub print_isp_and_province_dist
{
    my ($result) = @_;

    my $tmp_result = $result->{"isp_and_province_dist"};
    my $dianxin = decode("utf8", "电信");
    my $liantong = decode("utf8", "联通");
    my $yidong = decode("utf8", "移动");

    foreach my $isp ( ($dianxin, $liantong, $yidong) ) {
        my $all_province = $tmp_result->{$isp};
        foreach my $province ( keys %$all_province ) {
            my $num = $all_province->{$province};
            printf("%s %s: %d\n", encode("utf8", $isp), encode("utf8", $province), $num);
        }
    }
}

sub main
{
    my ($file_name) = @_;

    my $file_path = $file_name;
    open(FILE_HANDLER, "<", $file_path) or die "open file failed, err: $!";
    my @lines = <FILE_HANDLER>;
    my $contents = join("", @lines);
    my $infos = decode_json($contents);
    #print Dumper($infos);
    analyse($infos);
}

my $file_name = "nodes.json";
if  (scalar(@ARGV) != 0) {
    $file_name = $ARGV[0];    
}
main($file_name);

