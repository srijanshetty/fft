#!/bin/zsh

for i in {1..$1};do
    lim=$(( 2**$i ))
    echo -n "$lim "
    ./create.zsh 10 $lim "test" && ./a.out < "test"
done
