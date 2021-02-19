#!/bin/sh

low=$1
step=$2
high=$3
runs=$4

if [ -z "$low" -o -z "$step" -o -z "$high" -o -z "$runs" ]
then
    echo "Usage"
    echo "  $0 low step high runs_per_step"
    exit 1
fi

for games in `seq -w $low $step $high`
do
    outdir="data_3/${games}"
    mkdir -p $outdir
    echo "Doing $games set"
    date
    start=`date +%s`
    for count in `seq -w 1 $runs`
    do
        lstart=`date +%s`
        ./candyland -c $games > ${outdir}/${games}_${count}.csv
        lstop=`date +%s`
        if [ $((lstop-lstart)) -eq 0 ]
        then
            echo "Sleeping 1 to allow for next run to randomize"
            sleep 1
        fi
    done
    echo "Done with $games set"
    date
    stop=`date +%s`
    echo "Duration $((stop-start)) seconds" > $outdir/log
done
