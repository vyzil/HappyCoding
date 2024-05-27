#!/usr/bin/python3
import random
import subprocess

def check_in_range(num1, num2, range_start, range_end):
    in_range_count = 0
    
    if range_start <= num1 <= range_end:
        in_range_count += 1
    if range_start <= num2 <= range_end:
        in_range_count += 1
    
    return in_range_count % 2

def solve(N):
    # 첫 번째 입력: "1 92"
    input_range = f"1 {N}"
    print(f"Sending initial input: {input_range}")
    
    # 1부터 92 사이의 서로 다른 두 숫자를 선택
    selected_numbers = random.sample(range(1, N+1), 2)
    num1, num2 = selected_numbers[0], selected_numbers[1]
    print(f"Selected numbers: {num1}, {num2}")

    # 실행 파일과의 상호작용
    process = subprocess.Popen("./a.out", stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    
    # 초기 입력 보내기
    process.stdin.write(f"{input_range}\n")
    process.stdin.flush()

    count = 0
    while True:
        output = process.stdout.readline().strip()
        print(f"Received from a.out: {output}")

        if output.startswith("AK"):
            count += 1
            _, start, end = output.split()
            start, end = int(start), int(end)
            if check_in_range(num1, num2, start, end):
                response = "O"
            else:
                response = "X"
            print(f"Sending response: {response}")
            process.stdin.write(f"{response}\n")
            process.stdin.flush()
        
        elif output.startswith("!"):
            _, guess1, guess2 = output.split()
            guess1, guess2 = int(guess1), int(guess2)
            if (guess1 == num1 and guess2 == num2) or (guess1 == num2 and guess2 == num1):
                result = "Correct!"
            else:
                result = "Incorrect!"
            print(f"Final result: {result}")
            break

    print("Count : ", count, "{", N, num1, num2 , "}")
    
    process.stdin.close()
    process.stdout.close()
    process.stderr.close()
    process.terminate()

    if result == "Incorrect!":
        return 0
    else:
        return 1

if __name__ == "__main__":
    while True:
        N = random.randint(2, 93)
        # N = 92
        if(solve(N) == 0):
            break