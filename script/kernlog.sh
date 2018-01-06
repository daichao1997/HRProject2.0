#! /bin/bash

rawdatapath=${1:-"../rawdata/log"}
datapath=${2:-"../data/log"}

for dir in `ls $rawdatapath`
do
	if test -f $datapath/$dir.log
	then
		echo "$datapath/$dir.log already exists."
	else
		echo "Merging into $datapath/$dir.log..."
		for file in `ls $rawdatapath/$dir`
		do
			cat $rawdatapath/$dir/$file >> $datapath/$dir.tmp
		done
		../bin/kernlog $datapath/$dir.tmp $datapath/$dir.log $datapath/$dir.err
		rm $datapath/$dir.tmp
	fi
done
