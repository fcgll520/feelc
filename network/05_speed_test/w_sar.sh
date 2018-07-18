#!/bin/sh
#

#br-lan
#eth0
#eth0.1
#eth0.2
#pppoe-wan
#lo
#
while [[ true ]]; do
    brlan_start_tx_bytes=`ifconfig  br-lan | grep "TX bytes" | awk '{print $6}'  |awk -F':' '{print $2}'`
    sleep 1
    brlan_end_tx_bytes=`ifconfig  br-lan | grep "TX bytes" | awk '{print $6}'  |awk -F':' '{print $2}'`
    let brlan_speed=${brlan_end_tx_bytes}-${brlan_start_tx_bytes}
    let brlan_speed=brlan_speed/1048576
    echo "br-lan ${brlan_speed} MBps"
    done
d