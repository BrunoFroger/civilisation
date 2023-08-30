#!/bin/bash
buildMakefile
make clean
make
if [ $? -eq 0 ]
then
    bin/civilisation $@
else
    echo "erreur de compilation(s)"
fi