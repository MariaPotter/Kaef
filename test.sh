#!/bin/bash

solute(){
    if [ $# -eq 1 ]
    then
        echo ""
    fi
    echo "N = $1"
    ./main $1
    ./solve_with_python.py
    ./plot.py $1
}

if (make 1> /dev/null); 
then
    solute 6 1
    solute 10
    solute 20
    solute 50
    solute 100
    solute 200
    solute 400

    make clean 1> /dev/null
fi
