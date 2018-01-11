#! /bin/bash
rawdatapath="../rawdata/gps"
datapath="../data/gps"
for file in `ls $rawdatapath`
do
	echo $file
	../bin/gnrmc $rawdatapath/$file $datapath/$file.tmp
	python ../src/gps_neat.py $datapath/$file.tmp $datapath/$file.csv
	#rm $datapath/$file.tmp
done