import numpy as np

class Vertex(): 
    
    def __init__(self, x, y, w):
        self.x = np.array([ x, y ])
        self.p = np.array([ x, y ])
        # inverse mass
        self.w = w

    def getX(self):
        return self.p[0]

    def getY(self):
        return self.p[1]

class DistanceConstraint():

    def __init__(self, i1, i2, distance, stiffness):
        self.i1 = i1
        self.i2 = i2
        self.distance = distance
        self.stiffness = stiffness

    def solve(self, vertices, iterations):
        RHS = np.zeros((2, 2))
        coefficients = np.zeros((2, 2))

        w1 = vertices[self.i1].w
        w2 = vertices[self.i2].w
        p1 = vertices[self.i1].p
        p2 = vertices[self.i2].p
 
        coefficients[0][0] = 1.0 / (w1 / (w1 + w2))
        coefficients[1][1] = 1.0 / (w2 / (w1 + w2))

        distance_constraint = np.linalg.norm(p1 - p2) - self.distance

        # 0.1 = epsilon
        n = (p1 - p2) / (np.linalg.norm(p1 - p2) + 0.1)
        d1 = -distance_constraint * n
        d2 = distance_constraint * n
        RHS = np.array([d1, d2])

        cholesky = np.linalg.cholesky(coefficients)
        corrections = np.linalg.solve(cholesky, RHS)

        k = 1.0 - np.power(1.0 - self.stiffness, 1.0 / iterations)
        vertices[self.i1].p += k * corrections[:, 0]
        vertices[self.i2].p += k * corrections[:, 0]

class AnchorConstraint():

    def __init__(self, i, fixed):
        self.i = i
        self.fixed = fixed

    def solve(self, vertices, ignored):
        vertices[self.i].p = np.array(self.fixed)