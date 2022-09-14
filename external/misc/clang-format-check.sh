#!/bin/bash

clangFormatTargets=$(find . -type f ! -path './external/*' ! -path './build*'  -type f -regex '.*\.\(cpp\|hpp\|h\|cc\|cxx|c\)')

for inputFile in $clangFormatTargets
do
    clang-format-10 -style=file $inputFile > $inputFile-formatted
    diff $inputFile $inputFile-formatted
    if [ $? != 0 ] ; then
        exit 1
    else
        rm $inputFile-formatted
    fi
done
