from numpy import linalg
import unittest
import numpy as np
from distance_constraint import *
from matplotlib import pyplot as plt

class DistanceConstraintTest(unittest.TestCase):

    def test_proto(self):
        triangle = np.array([
            [  0.0, 1.0 ],
            [  0.6, 0.0 ],
            [ -0.6, 0.0 ]
        ])
        d1_2 = linalg.norm(triangle[0] - triangle[1])
        d1_3 = linalg.norm(triangle[0] - triangle[2])
        d2_3 = linalg.norm(triangle[1] - triangle[2])
        eTriangle = np.array([
            [  0.0, 1.0 ],
            [  0.6, 0.0 ],
            [ -0.6, -2.0 ]
        ])
        #x, y = zip(*triangle)
        vertices = [ Vertex(p[0], p[1], 1.0 / 2.0) for p in triangle ]
        eVertices = [ Vertex(p[0], p[1], 1.0 / 2.0) for p in eTriangle ]
        constraints = []
        stiffness = 0.5
        iterations = 10

        #constraints.append(AnchorConstraint(0, [ 0.0, 1.0 ]))
        #constraints.append(AnchorConstraint(1, [ 0.6, 0.0 ]))

        for i in range(len(triangle)):
            for j in range(i + 1, len(triangle)):
                p1 = vertices[i].p
                p2 = vertices[j].p
                distance = np.linalg.norm(p1 - p2)
                constraints.append(DistanceConstraint(i, j, distance, stiffness))

        e1 = []
        e2 = []
        e3 = []
        for i in range(iterations):
            for constraint in constraints:
                x = [ v.getX() for v in eVertices ]
                y = [ v.getY() for v in eVertices ]
                plt.scatter(x, y)
                constraint.solve(eVertices, iterations)
               
            e1.append([i, linalg.norm(eVertices[0].p - eVertices[1].p)])
            e2.append([i, linalg.norm(eVertices[0].p - eVertices[2].p)])
            e3.append([i, linalg.norm(eVertices[1].p - eVertices[2].p)])
        plt.show()
        #plt.plot([ x for x, y in e1], [ y for x, y in e1])
        #plt.plot([ x for x, y in e2], [ y for x, y in e2])
        #plt.plot([ x for x, y in e3], [ y for x, y in e3])


        #plt.scatter(x, y)
        #plt.show()
