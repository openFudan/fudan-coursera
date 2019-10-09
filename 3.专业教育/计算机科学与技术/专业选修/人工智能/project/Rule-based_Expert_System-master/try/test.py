"""

"""
from point import Point
from line import Line
from triangle import Triangle
__author__ = 'liuyang'


if __name__ == '__main__':
    points = []
    with open('test_case.txt') as f:
        ps = map(float, filter(str.isdigit, map(str.strip, f.readlines())))

    for i in range(0, len(ps), 2):
        points.append(Point(ps[i], ps[i+1]))

    ps = points[9:12]
    for point in ps:
        print(point)
    triangle = Triangle(ps)
    print(triangle.isTriangle())

