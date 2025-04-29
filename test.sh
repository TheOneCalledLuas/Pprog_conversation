#!/bin/bash

# Checks the arguments passed to the script.
if [ $# -gt 2 -a $# -eq 0 ]; then
    echo "Usage: $0 [mode] [file:optional]"
    exit 0
elif [ $# -eq 1 ]; then
    # Runs all the tests with the determined mode.
    echo "running all test files in specified mode."
    if [ $1 = 0 ]; then 
        make do_all_test
    else
        make check_all_test
    fi
else 
    # Runs the specified test file with the determined mode.
    echo "running test file $2 in specified mode."
    if [ $1 = 0 ]; then 
        make do_$2
    else
        make check_$2
    fi
fi
