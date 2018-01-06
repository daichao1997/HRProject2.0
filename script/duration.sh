#! /bin/bash

rawdatapath="../rawdata/tcpdump"
datapath="../data/tcpdump"
logpath="../rawdata/duration.txt"

rm $logpath
for dir in `ls $rawdatapath`
do
	for file in `ls $rawdatapath/$dir`
	do
		echo "Checking $rawdatapath/$dir/$file"
		(capinfos -ae $rawdatapath/$dir/$file) >> $logpath
	done
done