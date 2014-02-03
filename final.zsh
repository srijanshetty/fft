#!/bin/zsh

for i in {1..$1};do
    lim=$(( 2**$i ))
    echo -n "$lim "
    ./create.zsh 10 $lim "$3" && "./$2" < "$3" 
done
