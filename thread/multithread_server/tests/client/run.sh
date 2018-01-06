#!/bin/bash

for (( i = 0; i < 1000; i++ )); do
    echo $i
    for (( j = 0; j < 100; j++ )); do
        ./client &
    done
    sleep 0.1
done

