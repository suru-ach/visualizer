#
#   This file generates all templates for cpp file
#
#!/bin/bash

make
mkdir generated

for file in `ls *.txt`
do
    `./a.out  < $file`
done

for file in `ls *.h`
do
    `mv $file ./generated`
done
