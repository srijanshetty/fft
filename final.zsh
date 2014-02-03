#!/bin/zsh

for i in {18..$1};do
    lim=$(( 2**$i ))
    echo -n "$lim "
    ./create.zsh 1 $lim "$3" && "./$2" < "$3" 
done
