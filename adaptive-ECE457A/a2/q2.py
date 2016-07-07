from copy import copy, deepcopy
from random import randint, shuffle

BOARD_SIZE 	= 4
DEPTH_LIMIT	= 3
UP 			= "up"
DOWN 		= "down"
LEFT 		= "left"
RIGHT 		= "right"
UPLEFT 		= "upleft"
UPRIGHT 	= "upright"
DOWNLEFT 	= "downleft"
DOWNRIGHT 	= "downright"
DIRECTIONS	= [UP, DOWN, LEFT, RIGHT, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT]
RATIONAL 	= "rational agent"
RANDOM 		= "random agent"


class Cell:
	def __init__(self, stones=0, user=None):
		self.stones = stones
		self.user = user
	def __str__(self):
		if self.user == RATIONAL:  return "A:" + str(self.stones)
		elif self.user == RANDOM:  return "B:" + str(self.stones)
		else: return "N:" + str(self.stones)
	def isAvailable(self, user):
		return self.stones == 0 or self.user == user
	def empty(self):
		self.stones = 0
		self.user = ""


def moveX(direction, x, value):
	if("left" in direction): return x - value
	if("right" in direction): return x + value
	return x

def moveY(direction, y, value):
	if("up" in direction): return y - value
	if("down" in direction): return y + value
	return y

def move(user, direction, board, x, y):
	stonesLeft = board[y][x].stones
	temp = None
	newX1 = moveX(direction, x, 1)
	newY1 = moveY(direction, y, 1)
	if(0 <= newX1 < BOARD_SIZE and 0 <= newY1 < BOARD_SIZE and board[newY1][newX1].isAvailable(user)):
		temp = deepcopy(board)
		temp[y][x].empty()
		temp[newY1][newX1].stones += 1
		temp[newY1][newX1].user = user
		stonesLeft -= 1
	else: return None

	newX2 = moveX(direction, x, 2)
	newY2 = moveY(direction, y, 2)
	if(0 <= newX2 < BOARD_SIZE and 0 <= newY2 < BOARD_SIZE and board[newY2][newX2].isAvailable(user)):
		toAdd = min(stonesLeft, 2)
		temp[newY2][newX2].stones += toAdd
		temp[newY2][newX2].user = user
		stonesLeft -= toAdd
	else:
		temp[newY1][newX1].stones += stonesLeft
		return temp

	newX3 = moveX(direction, x, 3)
	newY3 = moveY(direction, y, 3)
	if(0 <= newX3 < BOARD_SIZE and 0 <= newY3 < BOARD_SIZE and board[newY3][newX3].isAvailable(user)):
		temp[newY3][newX3].stones += stonesLeft
		temp[newY3][newX3].user = user
	else:
		temp[newY2][newX2].stones += stonesLeft

	return temp

def getChildren(board, user):
	moves = []
	for y in range(0,BOARD_SIZE):
		for x in range(0,BOARD_SIZE):
			if(board[y][x].user != user): continue
			for direction in DIRECTIONS:
				moves.append(move(user, direction, board, x, y))

	ret = [x for x in moves if x is not None]

	shuffle(ret)
	return ret

def getNumberOfChildren(board, user):
	total = 0
	for y in range(0,BOARD_SIZE):
		for x in range(0,BOARD_SIZE):
			if(board[y][x].user != user): continue
			for direction in DIRECTIONS:
				newX = moveX(direction, x, 1)
				newY = moveY(direction, y, 1)
				if(0 <= newX < BOARD_SIZE and 0 <= newY < BOARD_SIZE and board[newY][newX].isAvailable(user)): total += 1
	return total

def rationalMove(board, isRational, alpha, beta, depth):
	rationalChildren = getNumberOfChildren(board, RATIONAL)
	randomChildren = getNumberOfChildren(board, RANDOM)

	if(isRational and (randomChildren == 0 or depth == DEPTH_LIMIT)): 
		return rationalChildren - randomChildren
	if(not isRational and (rationalChildren == 0 or depth == DEPTH_LIMIT)): 
		return rationalChildren - randomChildren

	children = getChildren(board, RATIONAL) if isRational else getChildren(board, RANDOM)

	for child in children:
		if(isRational):
			childVal = rationalMove(child, not isRational, alpha, beta, depth + 1)
			if alpha == None: alpha = childVal
			alpha = max(alpha, childVal) 
			if(beta != None and childVal > beta): 
				return alpha
		else:
			childVal = rationalMove(child, not isRational, alpha, beta, depth + 1)
			if beta == None: beta = childVal
			beta = min(beta, childVal)
			if(alpha != None and childVal < alpha): 
				return beta
	return alpha if isRational else beta

def randomAgent(board):
	children = getChildren(board, RANDOM)
	return children[randint(0, len(children) - 1)]

def rationalAgent(board):
	score = None
	bestMove = None
	for child in getChildren(board, RATIONAL):
		childVal = rationalMove(child, False, None, None, 0)
		if(score == None or childVal < score):
			score = childVal
			bestMove = child

	return bestMove

def printBoard(board):
	print("Board")
	for y in range(0,BOARD_SIZE):
		for x in range(0,BOARD_SIZE):
			print(board[y][x], " ",  end="")
		print("")


if __name__ == '__main__':
	board = []

	for y in range(0,BOARD_SIZE):
		row = []
		for x in range(0,BOARD_SIZE):
			row.append(Cell())
		board.append(row)

	board[0][0].user = RATIONAL
	board[0][0].stones = 10
	board[BOARD_SIZE-1][BOARD_SIZE-1].user = RANDOM
	board[BOARD_SIZE-1][BOARD_SIZE-1].stones = 10

	for i in range(0,10):
		while True:
			if(len(getChildren(board, RATIONAL)) > 0):
				print("Rational player turn")
				board = rationalAgent(board)
				printBoard(board)
			else:
				print("Random player wins")
				printBoard(board)
				break
			if(len(getChildren(board, RANDOM)) > 0):
				print("Random player turn")
				board = randomAgent(board)
				printBoard(board)
			else:
				print("Rational player wins")
				printBoard(board)
				break


