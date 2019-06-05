# !/bin/bash

rm -rf output.txt

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../libs


if ! [ -f "input.txt" ]
then 
    echo "ERROR: No input file found"
    exit 1
fi

cd ..
./bin/tsin &> /dev/null
cd - &> /dev/null

echo -n "Testing tsin .... "
if [ -f "output.txt" ]
then
    diff output.txt golden.out > diff
    if [ -s diff ]
    then
        echo "FAIL"
        cat diff
    else
        echo "PASS"
    fi
else
    echo "FAIL (No output file found)"
fi
