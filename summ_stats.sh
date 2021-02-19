#!/bin/sh

echo "Game Length,Player 1 Wins,Player 1 Margin,Player 2 Margin,Shortest Average,Longest Average, Average Average"

for csv in `ls */stats.csv`
do
    games=`cat $csv | wc -l`
    # Account for header line
    games=$((games-1))
    length=`grep "Player" $csv | head -1 | awk -F, '{print $2}'`
    play1_wins=`grep "Player 1" $csv | wc -l`
    play1_wins=$((play1_wins+0))
    play2_wins=$((games-play1_wins))
    play1_perc=`perl -e "print ($play1_wins/$games) . \"\n\""`

    play1_marg=0
    play2_marg=0

    math=""
    for num in `grep "Player 1" $csv | awk -F, '{print $4}'`
    do
        if [ -z "$math" ]
        then
            math="$num"
        else
            math="${math}+${num}"
        fi
    done
    if [ -n "$math" ]; then play1_marg=`perl -e "print (($math)/$play1_wins) . \"\n\""`; fi

    math=""
    for num in `grep "Player 2" $csv | awk -F, '{print $4}'`
    do
        if [ -z "$math" ]
        then
            math="$num"
        else
            math="${math}+${num}"
        fi
    done
    if [ -n "$math" ]; then play2_marg=`perl -e "print (($math)/$play2_wins) . \"\n\""`; fi

    math=""
    for num in `grep -v "Game" $csv | awk -F, '{print $5}'`
    do
        if [ -z "$math" ]
        then
            math="$num"
        else
            math="${math}+${num}"
        fi
    done
    if [ -n "$math" ]; then shortest=`perl -e "print (($math)/$games) . \"\n\""`; fi

    math=""
    for num in `grep -v "Game" $csv | awk -F, '{print $6}'`
    do
        if [ -z "$math" ]
        then
            math="$num"
        else
            math="${math}+${num}"
        fi
    done
    if [ -n "$math" ]; then longest=`perl -e "print (($math)/$games) . \"\n\""`; fi

    math=""
    for num in `grep -v "Game" $csv | awk -F, '{print $7}'`
    do
        if [ -z "$math" ]
        then
            math="$num"
        else
            math="${math}+${num}"
        fi
    done
    if [ -n "$math" ]; then average=`perl -e "print (($math)/$games) . \"\n\""`; fi

    echo "$length,$play1_perc,$play1_marg,$play2_marg,$shortest,$longest,$average"
done
