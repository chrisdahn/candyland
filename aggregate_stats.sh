#!/bin/sh

for dir in `ls`
do
    pushd $dir

    echo "Game,Total,Winner,Margin,Shortest,Longest,Average" > stats.csv

    count=1
    for file in `ls *_stats.csv`
    do
        total=`grep "Total" $file | awk -F, '{print $2}'`
        winner=`grep "Player" $file | awk -F, '{print $1}'`
        margin=`grep "Player" $file | awk -F, '{print $2}'`
        short=`grep "Shortest" $file | awk -F, '{print $2}'`
        long=`grep "Longest" $file | awk -F, '{print $2}'`
        avg=`grep "Average" $file | awk -F, '{print $2}'`
        echo "$count,$total,$winner,$margin,$short,$long,$avg" >> stats.csv
        count=$((count+1))
    done

    popd
done
