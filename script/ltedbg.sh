#! /bin/bash
rawdatapath=${1:-"../rawdata/lte"}
datapath=${2:-"../data/lte"}

for dir in `ls $rawdatapath`
do
	if test -f $datapath/$dir/lte_dbg_1.info
	then
		echo "$datapath/$dir is already done."
	else
		for file in `ls $rawdatapath/$dir`
		do
			echo "Processing $rawdatapath/$dir/$file..."
			mkdir -p $datapath/$dir
			../bin/ltedbg $rawdatapath/$dir/$file $datapath/$dir/$file
		done
	fi
done