#! /bin/bash

# Usage: bash mergepcap.sh [rawdatapath datapath logpath]

# Requirements:
# 1. 'logpath' must be generated by `checkpcap.sh
# 2. 'rawdatapath' must contain only directories that contain a series of PCAP files
rawdatapath=${1:-"../rawdata/tcpdump"}
datapath=${2:-"../data/tcpdump"}
logpath=${3:-"../stat/tcpdump/error.txt"}

if test -f $logpath
then
	:
else
	echo "Please run checkpcap.sh to generate a log before proceeding."
fi

for dir in `ls $rawdatapath`
do
	err=`grep "$dir" $logpath`
	if test -z "$err"
	then
		if test -f $datapath/$dir.pcap
		then
			echo "$datapath/$dir.pcap already exists."
		else
			echo "Merging into $datapath/$dir.pcap"
			mergecap -w $datapath/$dir.pcap $rawdatapath/$dir/*
		fi
	else echo "$dir has error."
	fi
done