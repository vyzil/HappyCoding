#!/usr/bin/python3

list_input = [6, 12, 12, 16, 10, 4, 8, 8, 14]

for a in range(0, 9, 1):
    for b in range(0, a, 1):
        for c in range(0, b, 1):
            copy_input = list_input.copy()
            copy_input[a] = 0
            copy_input[b] = 0
            copy_input[c] = 0

            for j in range(0, 3, 1):
                for k in range(0, 3, 1):
                    print(copy_input[j*3+k], end= ' ')
                print("")
            print("-----------")
