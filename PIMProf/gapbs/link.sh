#!/bin/bash
PATH=/staff/shaojiemike
for i in {16..26}
do
    cmd="/usr/bin/ln $PATH/github/gapbs/kron-$i.sg ./benchmark"
    echo "Executing: $cmd"
    $cmd
    cmd="/usr/bin/ln $PATH/github/gapbs/kron-$i.wsg ./benchmark"
    echo "Executing: $cmd"
    $cmd
done
