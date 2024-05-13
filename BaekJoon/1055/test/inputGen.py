#!/usr/bin/python3
import random
import string

if __name__ == '__main__':

    input1 = ''.join(random.choice(string.ascii_lowercase) for _ in range(random.randint(1,50)))
    input2 = '$' + ''.join(random.choice(string.ascii_lowercase+'$') for _ in range(random.randint(1,49)))
    input3 = random.randint(1, 1000000000)
    input4 = random.randint(1, 1000000000)
    input5 = input4 + random.randint(0, 99)

    print(input1)
    print(input2)
    print(input3)
    print(input4, input5)