#!/usr/bin/perl -w

use JSON;
use Data::Dumper;

sub analyse
{
    my ($infos) = @_;

    my $result = {};
    $result->{"err_num"} = 0;

    foreach my $item ( @$infos ) {
        analyse_lan_upload_bw_dist($result, $item);
        analyse_wlan_upload_bw_dist($result, $item);
        analyse_upload_bw_dist($result, $item);
        analyse_bw_and_num($result, $item);
        analyse_peer_to_peer_network($result, $item);  #对等网络
    }

    #print Dumper($result);
    
    print_err($result);
    print_lan_upload_bw_dist($result);
    print_wlan_upload_bw_dist($result);
    print_upload_bw_dist($result);
    print_bw_and_num($result);
    print_peer_to_peer_network($result);
}

sub analyse_peer_to_peer_network
{
    my ($result, $item) = @_;

    if ($item->{"upload_bw"} < 0) { $result->{"err_num"} += 1; return ; }
    if ($item->{"download_bw"} < 0) { $result->{"err_num"} += 1; return ; }

    unless (exists $result->{"p2p_netwprk_num"}) { $result->{"p2p_netwprk_num"} = 0; }

    my $upload_bw = $item->{"upload_bw"};
    my $download_bw = $item->{"download_bw"};

    if (0 == $upload_bw || 0 == $download_bw) { return ; }
    if ($download_bw < 100 || $upload_bw < 80) { return ; }

    $result->{"p2p_netwprk_num"} += 1;
    if ($item->{tcp}) { $result->{"wlan_p2p_netwprk_num"} += 1; }
    unless ($item->{tcp}) { $result->{"lan_p2p_netwprk_num"} += 1; }
}

sub print_peer_to_peer_network
{
    my ($result) = @_;
    printf("peer-to-peer network num: %d, wlan: %d, lan: %d\n",
        $result->{"p2p_netwprk_num"},
        $result->{"wlan_p2p_netwprk_num"},
        $result->{"lan_p2p_netwprk_num"});
}

sub analyse_bw_and_num
{
    my ($result, $item) = @_;

    if ($item->{"upload_bw"} < 0) { $result->{"err_num"} += 1; }
    if ($item->{"download_bw"} < 0) { $result->{"err_num"} += 1; }

    unless (exists $result->{"total_upload_bw"}) { $result->{"total_upload_bw"} = 0; }
    unless (exists $result->{"total_download_bw"}) { $result->{"total_download_bw"} = 0; }
    unless (exists $result->{"total_wlan_upload_bw"}) { $result->{"total_wlan_upload_bw"} = 0; }
    unless (exists $result->{"total_wlan_download_bw"}) { $result->{"total_wlan_download_bw"} = 0; }
    unless (exists $result->{"total_lan_upload_bw"}) { $result->{"total_lan_upload_bw"} = 0; }
    unless (exists $result->{"total_lan_download_bw"}) { $result->{"total_lan_download_bw"} = 0; }
    unless (exists $result->{"all_num"}) { $result->{"all_num"} = 0; }
    unless (exists $result->{"all_wlan_num"}) { $result->{"all_wlan_num"} = 0; }
    unless (exists $result->{"all_lan_num"}) { $result->{"all_lan_num"} = 0; }

    my $download_bw = $item->{"download_bw"};
    my $upload_bw = $item->{"upload_bw"};

    $result->{"all_num"} += 1;
    if ($item->{tcp}) { $result->{"all_wlan_num"} += 1; }
    unless ($item->{tcp}) { $result->{"all_lan_num"} += 1; }

    if ($item->{"upload_bw"} > 0) {
        if ($item->{tcp}) { $result->{"total_wlan_upload_bw"} += $upload_bw; }
        unless ($item->{tcp}) { $result->{"total_lan_upload_bw"} += $upload_bw; }
        $result->{"total_upload_bw"} += $upload_bw;
    }
    if ($item->{"download_bw"} > 0) {
        if ($item->{tcp}) { $result->{"total_wlan_download_bw"} += $download_bw; }
        unless ($item->{tcp}) { $result->{"total_lan_download_bw"} += $download_bw; }
        $result->{"total_download_bw"} += $download_bw;
    }
}

sub print_bw_and_num
{
    my ($result) = @_;
    printf("all_num: %d, download_bw: %dGbps, upload_bw: %dGbps\n",
        $result->{"all_num"},
        $result->{"total_download_bw"}/1024,
        $result->{"total_upload_bw"}/1024);
    printf("all_wlan_num: %d, download_bw: %dGbps, upload_bw: %dGbps\n",
        $result->{"all_wlan_num"},
        $result->{"total_wlan_download_bw"}/1024,
        $result->{"total_wlan_upload_bw"}/1024);
    printf("all_lan_num: %d, download_bw: %dGbps, upload_bw: %dGbps\n",
        $result->{"all_lan_num"},
        $result->{"total_lan_download_bw"}/1024,
        $result->{"total_lan_upload_bw"}/1024);
}

sub upload_bw_dist_internal
{
    my ($tmp_result, $upload_bw) = @_;

    if ($upload_bw == 0) {
        $tmp_result->{"0"} += 1;
    }
    elsif ($upload_bw > 0 && $upload_bw < 4) {
        $tmp_result->{"(0-4)"} += 1;
    }
    elsif ($upload_bw >= 4 && $upload_bw < 8) {
        $tmp_result->{"[4-8)"} += 1;
    }
    elsif ($upload_bw >= 8 && $upload_bw < 20) {
        $tmp_result->{"[8-20)"} += 1;
    }
    elsif ($upload_bw >= 20 && $upload_bw < 30) {
        $tmp_result->{"[20-30)"} += 1;   
    }
    elsif ($upload_bw >= 30 && $upload_bw < 50) {
        $tmp_result->{"[30-50)"} += 1;
    }
    elsif ($upload_bw >= 50) {
        $tmp_result->{"[50+)"} += 1;
    }
}

sub print_upload_bw_dist_interval
{
    my ($result, $key) = @_;

    my $tmp_result = $result->{"$key"}->{"dist"};
    my $all_num = $result->{"$key"}->{"all_num"};

    printf("%s: \n", $key);
    foreach my $range ( ("0","(0-4)","[4-8)","[8-20)","[20-30)","[30-50)","[50+)") ) {
        my $num = $tmp_result->{$range};
        my $percent = $num * 100 / $all_num;
        printf("              %s upload_bw  %s : %.2f%s %d\n", $key, $range, $percent, "%", $num);
    }
}

sub analyse_upload_bw_dist
{
    my ($result, $item) = @_;

    if ($item->{"upload_bw"} < 0) {
        $result->{"err_num"} += 1;
        return ;
    }
    unless (exists $result->{"upload_bw_dist"}) {
        $result->{"upload_bw_dist"}->{"all_num"} = 0;
        $result->{"upload_bw_dist"}->{"dist"} = {
            "0"         => 0,
            "(0-4)"     => 0,
            "[4-8)"     => 0,
            "[8-20)"    => 0,
            "[20-30)"   => 0,
            "[30-50)"   => 0,
            "[50+)"     => 0,
        }
    }
    $result->{"upload_bw_dist"}->{"all_num"} += 1;
    my $tmp_result = $result->{"upload_bw_dist"}->{"dist"};
    my $upload_bw = $item->{"upload_bw"};
    upload_bw_dist_internal($tmp_result, $upload_bw);
}

sub print_upload_bw_dist
{
    my ($result) = @_;
    print_upload_bw_dist_interval($result, "upload_bw_dist");
}

sub analyse_wlan_upload_bw_dist
{
    my ($result, $item) = @_;

    unless ($item->{tcp}) {
        return ;
    }
    if ($item->{"upload_bw"} < 0) {
        $result->{"err_num"} += 1;
        return ;
    }
    #printf Dumper($item) . "\n";
    unless (exists $result->{"wlan_upload_bw_dist"}) {
        $result->{"wlan_upload_bw_dist"}->{"all_num"} = 0;
        $result->{"wlan_upload_bw_dist"}->{"dist"} = {
            "0"         => 0,
            "(0-4)"     => 0,
            "[4-8)"     => 0,
            "[8-20)"    => 0,
            "[20-30)"   => 0,
            "[30-50)"   => 0,
            "[50+)"     => 0,
        }
    }
    $result->{"wlan_upload_bw_dist"}->{"all_num"} += 1;
    my $tmp_result = $result->{"wlan_upload_bw_dist"}->{"dist"};
    my $upload_bw = $item->{"upload_bw"};
    upload_bw_dist_internal($tmp_result, $upload_bw);
}

sub print_wlan_upload_bw_dist
{
    my ($result) = @_;
    print_upload_bw_dist_interval($result, "wlan_upload_bw_dist");
}

sub analyse_lan_upload_bw_dist
{
    my ($result, $item) = @_;

    if ($item->{tcp}) {
        return ;
    }
    if ($item->{"upload_bw"} < 0) {
        $result->{"err_num"} += 1;
        return ;
    }
    #printf Dumper($item) . "\n";
    unless (exists $result->{"lan_upload_bw_dist"}) {
        $result->{"lan_upload_bw_dist"}->{"all_num"} = 0;
        $result->{"lan_upload_bw_dist"}->{"dist"} = {
            "0"         => 0,
            "(0-4)"     => 0,
            "[4-8)"     => 0,
            "[8-20)"    => 0,
            "[20-30)"   => 0,
            "[30-50)"   => 0,
            "[50+)"     => 0,
        }
    }
    $result->{"lan_upload_bw_dist"}->{"all_num"} += 1;
    my $tmp_result = $result->{"lan_upload_bw_dist"}->{"dist"};
    my $upload_bw = $item->{"upload_bw"};
    upload_bw_dist_internal($tmp_result, $upload_bw);
}

sub print_lan_upload_bw_dist
{
    my ($result) = @_;
    print_upload_bw_dist_interval($result, "lan_upload_bw_dist");
}

sub print_err
{
    my ($result) = @_;
    printf("err_num: %d\n", $result->{"err_num"});
}
sub main
{
    my ($file_name) = @_;

    my $file_path = "/worker/" . $file_name;
    #my $file_path = "/worker/NewWifi/0307/" . $file_name;
    open(FILE_HANDLER, "<", $file_path) or die "open file failed, err: $!";
    my @lines = <FILE_HANDLER>;
    my $contents = join("", @lines);
    my $infos = decode_json($contents);
    #print Dumper($infos);
    analyse($infos);
}

my $file_name = "12.json";
if  (scalar(@ARGV) != 0) {
    $file_name = $ARGV[0];    
}
main($file_name);
printf $file_name . "\n";
