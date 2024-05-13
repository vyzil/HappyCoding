
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
 
    if [ ! -e $file_name ]; then
        mkdir "$file_name"
    fi

    if [ -e "$file_name" ]; then
        cd "$file_name"
        touch 0001.c note.txt input.txt
        code 0001.c note.txt input.txt
        echo "Happy Coding!"
    fi
}

main "$1"