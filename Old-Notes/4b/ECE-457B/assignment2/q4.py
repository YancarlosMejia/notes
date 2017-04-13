# Training data
x1 = [1, -2, 0, -1]
x2 = 0, 1.5, -0.5, -1
x3 = [-1, 1, 0.5, -1]
inputs = [x1, x2, x3]
# Labels for training data
t1 = -1
t2 = -1
t3 = 1
targets = [t1, t2, t3]
# Initial weights
weights = [1, -1, 0, 0.5]
# Learning rate
n = 0.1
# Maximum number of iterations
maxIterations = 50
# Thresholds for determining if a steady state has been achieved
threshold = 0.1

def calcR(i):
    r = 0
    for j in range(0, len(inputs[i])):
            r += inputs[i][j] * weights[j]
    return r

iters = 0
while iters < maxIterations: # loop for each epoch
    output = 0
    isSteady = True
    for i in range(0, len(inputs)): #loop for each piece of training data
        r = calcR(i)
        for data in range(0, len(weights)):
            # Calculate delta
            delta =  n * (targets[i] - r) * inputs[i][data]
            # Check if delta is close enough to 0
            isSteady = isSteady and (abs(delta) < threshold)
            # Update weights
            weights[data] = weights[data] + delta
    if isSteady: # stop looping if steady state has been achieved
        break
    iters += 1
if iters == maxIterations - 1:
    print 'Did not converge'
else:
    print 'Converged in {0} epochs'.format(iters)
    print weights
