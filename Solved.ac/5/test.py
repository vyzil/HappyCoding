#!/usr/bin/python3

key = "TSFHHABP"
hint = "\\BD_OBNZ"

prv = 0
for i in range(0, 8):
    res_prv = ord(key[i]) - ord('A')
    low_bit = ((prv << 1) & 31) ^ res_prv
    for j in range(ord('A'), ord('Z') + 1):
        if(j & 31 == low_bit):
            print((chr(j)))
            break
    prv = res_prv

print(chr(0x41), chr(0x4E), chr(0x41), chr(0x47))
print(chr(0x45), chr(0x4D), chr(0x45), chr(0x4E))
print(chr(0x54))