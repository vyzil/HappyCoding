problem_num="$1"

if [ -z "$problem_num" ]; then
    echo "usage : $0 <problem_number>"
    exit 1
fi

mkdir "$problem_num"
cd "$problem_num" || exit
touch 0001.c note.txt input.txt
code 0001.c note.txt input.txt
echo "Lets Coding!"