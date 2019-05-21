#!/bin/bash

Command=""
for depth in `seq 50 10 2890`
do
	radius=`echo 6371-${depth} | bc -l`
    Command="${Command} -r ${radius}"
done

./a3d_dist.x ${Command} -d 1

exit 0
