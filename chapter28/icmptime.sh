#!/bin/sh
if [ $# != 1 ];then
echo "Usage: $0 <dst-host>"
echo "e.g. $0 192.168.1.1"
exit 1
fi
dst_host=$1
sudo sleep 0  # 获取 sudo 权限
(sudo ./ip-recv.out $dst_host | ./icmptime-rcv.out; killall sleep)& 
sudo ./icmptime-snd.out -d $dst_host
sleep 3


