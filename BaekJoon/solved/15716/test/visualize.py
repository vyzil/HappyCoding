#!/usr/bin/python3
def read_input(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()
        n, b = map(int, lines[0].strip().split())
        word, X = lines[1].strip().split()
        X = int(X)
        words = lines[2].strip().split()
    return n, b, word, X, words

def main():
    # 파일에서 입력 읽기
    input_file = 'input.txt'
    n, b, word, X, words = read_input(input_file)

    # C 프로그램 로직을 Python으로 구현
    S = words
    if b == 1:
        print(S[0])  # 1-based index in C code is equivalent to 0-based index in Python
    else:
        for i in range(1, 100):
            print(i, ': ', end='')
            if (i - 1) % (2 * (b - 1)) + 1 < b:
                for j in range(1, (i - 1) % (b - 1) + 2):
                    print(S[(j - 1) % n], end=' ')
            else:
                for j in range(1, b - ((i - 1) % (b - 1)) + 1):
                    print(S[(j - 1) % n], end=' ')
            print()  # for newline after each iteration

if __name__ == "__main__":
    main()