#!/usr/bin/python3

def solve(a, S, r, m, M):
    a = a
    S = S.split('$')[1:]
    r, m, M = int(r), int(m), int(M)

    len_a = len(a)
    len_S = list(map(len, S))
    total_len_S = sum(len_S)

    initial = a + a.join(S)

    ans = ''

    if len(S) == 1:
        total_len = len_a + total_len_S * r
        ans = ''
        
        for k in range(m, M+1):
            if k <= len_a:
                ans += a[k - 1]
            elif k <= total_len:
                ans += S[0][(k - len_a) % total_len_S - 1]
            else:
                ans += '-'

    else:
        cycle = []
        cycle.append(total_len_S + len_a * len(S))

        limit = M
        if r <= 30:
            total_len = total_len_S * (len(len_S) ** r - 1)/(len(len_S) - 1) + (len(len_S) ** r) * len_a
            limit = min(M, total_len)
        while cycle[-1] < limit:
            cycle.append(total_len_S + cycle[-1] * len(S))
        
        for k in range(m, M+1):
            temp = k

            if k > cycle[-1]:
                ans += '-'
                continue

            init_final = True
            for i in range(len(cycle)-1, -1, -1):
                j = 0
                while j < len(S):
                    if cycle[i] >= temp: # 첫번째 실행에 포함된 문자열
                        init_final = True
                        break
                    temp -= cycle[i]

                    if len_S[j] >= temp:
                        init_final = False
                        break
                    temp -= len_S[j]
                    j += 1
                
                if not init_final:
                    break

            if init_final:
                ans += initial[temp-1]
            else:
                ans += S[j][temp-1]
    return ans


if __name__ == '__main__' : 
    a = input()
    S = input()
    r = input()
    m, M = input().split()

    print(solve(a, S, r, m, M))