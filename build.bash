#!/bin/bash

if [ $# -ne 0 ]; then
    if [[ "$1" == "all" ]]; then
        shift 1
        buildMakefile
        make clean
    fi
    if [[ "$1" == "clean" ]]; then
        shift 1
        make clean
    fi
fi

make
if [ $? -eq 0 ]
then
    bin/civilisation $@
else
    echo "erreur(s) de compilation(s)"
fi