#!/bin/sh
(sudo ./ip-recv.out foolishflyfox.xyz | ./icmptime-rcv.out)& 
./icmptime-snd.out -d foolishflyfox.xyz | sudo ./ip-send.out


