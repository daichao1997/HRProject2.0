#! /bin/bash

# Usage: bash checkpcap.sh [rawdatapath logpath]

rawdatapath=${1:-"../rawdata/tcpdump"}
logpath=${2:-"../stat/tcpdump/error.txt"}

if test -f $logpath
then
	echo "Log $logpath already exists."
else
	for dir in `ls $rawdatapath`
	do
		for file in `ls $rawdatapath/$dir`
		do
			echo "Checking $rawdatapath/$dir/$file..."
			(capinfos -t $rawdatapath/$dir/$file) 2>> $logpath > /dev/null
		done
	done
fi