
from sklearn.neural_network import MLPClassifier
from numpy.random import random_sample
from random import random
from math import sin,pi,exp,cos
from numpy import transpose,matrix,array,append,arctan
import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import matplotlib.pyplot as plt


def doTheThing(numNodes):
	dataSize = 500
	X = []
	Y = []

	print("TEST")
	for i in range(0, dataSize):
		x1 = 2 * random() - 1
		x2 = 8 * random() - 4
		X.append([x1, x2])
		Y.append(sin(2*pi*x1)*cos(0.5*pi*x2)*exp(-x1**2))

	fig = plt.figure()
	ax = fig.gca(projection='3d')
	x1 = array(X)
	ax.plot(x1[...,0], x1[...,1], Y, label='parametric curve')
	ax.legend()
	plt.savefig('data.png')

	trainingSize = int(dataSize*0.7)
	mlp = MLPClassifier(hidden_layer_sizes=[numNodes], activation='logistic', solver='sgd', max_iter=1000 )

	print(len(array(X[:trainingSize]).T))
	print(len(array(X[:trainingSize]).T[0]))
	print(len(Y[:trainingSize]))
	mlp.fit(array(X[:trainingSize]).T, array(Y[:trainingSize], dtype="|S6"))

	values = mlp.predict(array([X[trainingSize:]]).T)

	fig = plt.figure()
	ax = fig.gca(projection='3d')
	x1 = array(X)
	ax.plot(x1[...,0], x1[...,1], values, label='parametric curve')
	ax.legend()
	plt.savefig('results.png')
	# return values
	# error = 0
	# for i in range(0, dataSize-trainingSize):
	# 	error += abs(float(values[i]) - Y[i+trainingSize])

	# return error/(dataSize - trainingSize)

doTheThing(4)
# errors = []
# for i in range(1, 100):
# 	val = doTheThing(i)
# 	print(str(i) + ": " + str(val))
# 	errors.append(val)

# print(errors.index(min(errors)))

