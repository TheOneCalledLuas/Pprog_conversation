#!/bin/bash

# Error handling
if [ "$#" -ne 2 ]; then
    echo "Use: $0 file1 file2"
    exit 1
fi

file1="$1"
file2="$2"

# Searches the files
if [ ! -f "$file1" ]; then
    echo "File '$file1' inexistent."
    exit 1
fi

if [ ! -f "$file2" ]; then
    echo "File '$file2' inexistent."
    exit 1
fi

# Compares the files for the test.
if cmp -s "$file1" "$file2"; then
    echo "Test passed."
else
    echo "Test Failed."
fi