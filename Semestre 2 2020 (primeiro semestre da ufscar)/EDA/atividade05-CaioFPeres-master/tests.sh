#!/bin/bash
for f in *.in; do 
    ./main < $f > out.tmp;
    if ! diff ${f%.*}.out out.tmp >/dev/null 2>&1
    then
        return 1;
    fi
done
return 0;