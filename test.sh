#!/bin/bash

solute(){
    if [ $# -eq 1 ]
    then
        echo ""
    fi
    echo "N = $1"
    ./main $1
    ./solve.py
    ./plot.py $1
}

if (make 1> /dev/null); 
then
    solute 2 1
    solute 6
    solute 10
    solute 20
    solute 50
    solute 100
    solute 200
    solute 400

    make clean 1> /dev/null
fi
