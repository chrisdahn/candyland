#!/bin/sh

for csv in `ls *_???.csv`
do
    basename=`echo $csv | awk -F. '{print $1}'`
    outfile="${basename}_stats.csv"

    games=`cat $csv | wc -l`
    games=$((games+0))
    echo "Total,$games" > $outfile

    pl_1_wins=`grep "Player 1" $csv | wc -l`
    pl_2_wins=`grep "Player 2" $csv | wc -l`

    if [ $pl_1_wins -ge $pl_2_wins ]
    then
        diff=$((pl_1_wins-pl_2_wins))
        frac=`perl -e "print (($diff/$pl_1_wins)) . \"\n\""`
        echo "Player 1,${frac}" >> $outfile
    else
        diff=$((pl_2_wins-pl_1_wins))
        frac=`perl -e "print (($diff/$pl_2_wins)) . \"\n\""`
        echo "Player 2,${frac}" >> $outfile
    fi

    quickest_win=`awk -F, '{print $2}' $csv | sort -n | head -1`
    longest_win=`awk -F, '{print $2}' $csv | sort -nr | head -1`

    sum=0
    for count in `awk -F, '{print $2}' $csv`
    do
        sum=$((sum+count))
    done

    echo "Shortest,$quickest_win" >> $outfile
    echo "Longest,$longest_win" >> $outfile
    echo "Average,$((sum/games))" >> $outfile
done
