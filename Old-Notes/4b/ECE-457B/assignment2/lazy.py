# -*- coding: utf-8 -*-
# @Author: Lara Janecka
# @Date:   2017-03-03 22:32:54
# @Last Modified by:   Lara Janecka
# @Last Modified time: 2017-03-04 23:07:35
from decimal import Decimal

K=[0, 0.2, 0.5, 0.8, 1, 0.8, 0.2]
f=[0, 0, 0.2, 0.5, 1, 0.8, 0.2]

for j in f:
	for i in K:
		print(i*j, ' & ', end='')
	print('\\\\')
