#!/usr/bin/env python

import requests
import base64

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




def main():
    dummy = "O1AyAVAannl/Q0k0jiUsEwtz7aOrJ0CFkNYWC1895ujMZmI4WWym3d4Ij19G0o5k8yPOy8Rx01i5pfgncBPqqA=="
    cookieFull =  base64.b64decode(dummy)
    cookies = [bytearray(cookieFull[i:i+16]) for i in range(0, len(cookieFull), 16)]

    plaintext = ""
    for i in range(len(cookies)-1):
        decrypted = decryptByte(cookies[i][:16], cookies[i+1][:16])
        plaintext += ''.join(chr(x) for x in decrypted)


    print plaintext
    # print (bytearray(plaintext))

if __name__ == '__main__':
    main()