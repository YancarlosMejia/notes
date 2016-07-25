#!/usr/bin/env python

import requests
import base64

url = 'http://localhost:4555'


def test(cookie):
	encode = base64.b64encode(cookie)

	print encode
	r = requests.get(url, cookies={"user": encode})

	if r.status_code == 200: print "Kill me now"
	return r.status_code != 500

def getPlain(padLen, i):
	if i == 0:
		return padLen

	return i+1

def getCookie():
	r = requests.get(url)
	cookie = r.cookies["user"]
	decode = base64.b64decode(cookie)
	return bytearray(decode)

def decryptByte(cookie):
	iv = bytearray(16)

	for plainTextPlace in range(15, -1, -1):
		prefix = bytearray(16)

		for i in range(plainTextPlace + 1, 16):
			paddingVal = getPlain(16-plainTextPlace, i)
			prefix[i] = paddingVal ^ iv[i]

		for i in range(256):
			prefix[plainTextPlace] = i
			if(test(prefix + cookie)):
				break;

		iv[plainTextPlace] = prefix[plainTextPlace] ^ (plainTextPlace - 1)

	print iv

	return iv ^ cookie[:16]



def main():
	cookie = getCookie()
	plaintext = decryptByte(cookie[16:])

	print plaintext

if __name__ == '__main__':
    main()