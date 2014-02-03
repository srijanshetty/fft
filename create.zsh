#!/bin/zsh

touch "$3"
echo -n "$1"  > $3

for j in {1..$1}; do
    echo "\n$2" >> $3;
    for i in {0..$2}; do
        echo -n "1 " >> $3;
    done
    echo "" >> $3;
    for i in {0..$2}; do
        echo -n "1 " >> $3;
    done
done



