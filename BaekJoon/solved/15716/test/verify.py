import subprocess
import random
import string

def generate_random_word(length):
    return ''.join(random.choice(string.ascii_lowercase) for _ in range(length))

def generate_input(n, b, word, X, words):
    input_data = f"{n} {b}\n{word} {X}\n{' '.join(words)}\n"
    return input_data

def main():
    # 입력 생성
    while(True):
        # n = random.randint(1, 200000)
        # b = random.randint(n, 10**12)
        # word = 'A'
        # X = random.randint(1, 10**12)

        n = random.randint(1, 3)
        b = random.randint(n, 10)

        word = 'A'
        X = random.randint(1, 10)
        
        # words 리스트 생성
        words = []
        for _ in range(n):
            # 50% 확률로 주어진 단어와 같은 단어 추가
            if random.random() > 0.5:
                words.append('A')
            else:
                # 다른 단어 생성
                words.append('K')

        if word not in words:
            words.append(word)
            n += 1
            b += 1

        input_data = generate_input(n, b, word, X, words)
        
        # 입력 데이터 파일에 저장
        with open('input.txt', 'w') as f:
            f.write(input_data)

        # C 프로그램 실행
        result1 = subprocess.run(['./a.out'], input=input_data, text=True, capture_output=True)    
        result2 = subprocess.run(['./b.out'], input=input_data, text=True, capture_output=True)

        # 출력 결과 파일에 저장
        with open('output1.txt', 'w') as f:
            f.write(result1.stdout)
            
        with open('output2.txt', 'w') as f:
            f.write(result2.stdout)

        # 입력과 출력 결과 출력
        print("Output1:")
        print(result1.stdout)
        print("Output2:")
        print(result2.stdout)

        if result1.stdout != result2.stdout:
            break

if __name__ == "__main__":
    main()