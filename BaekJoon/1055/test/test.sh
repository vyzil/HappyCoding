./inputGen.py > input.txt
./others.py < input.txt > verify.txt
./a.out < input.txt > check.txt
diff check.txt verify.txt