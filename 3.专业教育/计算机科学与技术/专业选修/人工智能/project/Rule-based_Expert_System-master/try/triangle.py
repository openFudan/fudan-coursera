"""

"""
from figure import Figure
from point import Point
from line import Line

__author__ = 'liuyang'


class Triangle(Figure):
    def __init__(self, points):
        Figure.__init__(self)
        self.point1 = points[0]
        self.point2 = points[1]
        self.point3 = points[2]
        self.line1 = Line(points[0], points[1])
        self.line2 = Line(points[1], points[2])
        self.line3 = Line(points[0], points[2])

    def isTriangle(self):
        lines_length = [self.line1.length,
                        self.line2.length,
                        self.line3.length]
        if sum(lines_length) - max(lines_length) > max(lines_length):
            return True
        else:
            return False
