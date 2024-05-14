#!/bin/bash
check_if_numeric() {
    if [[ ! $filename =~ ^[0-9]+$ ]]; then
        return 1
    fi
}

main() {
    if [ -z "$1" ]; then     
        echo "usage : $0 <problem_number>"   
        return 1
    fi

    file_name=$(basename "$1")

    check_if_numeric "$filename"

    if [ $# -ne 1 ]; then
        echo "usage : $0 <problem_number>"
        return 1
    fi
 

    if [ -d $file_name ]; then
        mv "$file_name" "../solved/"
    else
        echo "No $file_name directory found"
    fi
}

main "$1"