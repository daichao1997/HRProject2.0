#! /bin/bash
rawdatapath="../rawdata/gps"
datapath="../data/gps"
for file in `ls $rawdatapath`
do
	echo $file
	../bin/gnrmc $rawdatapath/$file $datapath/$file
done