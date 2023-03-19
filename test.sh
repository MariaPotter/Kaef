#!/bin/bash

make

echo  -e "N = 6:"
./main 6
./solve_with_python.py

./plot.py 6

echo -e "\nN = 10:"
./main 10
./solve_with_python.py

./plot.py 10

echo -e "\nN = 20:" ## 20
./main 20
./solve_with_python.py

./plot.py 20

echo -e "\nN = 50:"
./main 50
./solve_with_python.py

./plot.py 50

echo -e "\nN = 100:"
./main 100
./solve_with_python.py

./plot.py 100

echo -e "\nN = 200:"
./main 200
./solve_with_python.py

./plot.py 200

echo -e "\nN = 400:"
./main 400
./solve_with_python.py

./plot.py 400

make clean
