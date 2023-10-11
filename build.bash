#!/bin/bash

if [ $# -ne 0 ]; then
    if [[ "$1" == "all" ]]; then
        buildMakefile
        make clean
    fi
    if [[ "$1" == "clean" ]]; then
        make clean
    fi
fi

make
if [ $? -eq 0 ]
then
    bin/civilisation $@
else
    echo "erreur de compilation(s)"
fi