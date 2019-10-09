"""

"""
import math
from point import Point

__author__ = 'liuyang'


def line_length(point1, point2):
        return math.sqrt((point1.x - point2.x) ** 2 + (point1.y - point2.y) ** 2)


class Line:
    def __init__(self, point1, point2):
        self.point1 = point1
        self.point2 = point2
        self.length = line_length(point1, point2)

    def __str__(self):
        return 'from (%.2f,%.2f) to (%.2f,%.2f), length: %2f' % \
               (self.point1.x, self.point1.y, self.point2.x, self.point2.y, self.length)