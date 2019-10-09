#!/usr/bin/python
# encoding:utf-8
# -*- Mode: Python -*-
# Author: Soros Liu <soros.liu1029@gmail.com>

# ==================================================================================================
# Copyright 2016 by Soros Liu
#
#                                                                          All Rights Reserved
"""

"""
import cv2
import math

__author__ = 'Soros Liu'


def calculate_line_length(l):
    return math.sqrt((l[0][0] - l[1][0]) ** 2 + (l[0][1] - l[1][1]) ** 2)


def calculate_line_angle(l):
    try:
        k = float((l[0][1] - l[1][1])) / float((l[0][0] - l[1][0]))
    except ZeroDivisionError:
        k = 100000
    finally:
        return math.degrees(math.atan(k))


class ContourLine:
    """

    """

    def __init__(self, point1, point2):
        self.point1 = point1
        self.point2 = point2
        self.length = calculate_line_length((point1, point2))
        self.angle = calculate_line_angle((point1, point2))

    def __str__(self):
        return '(%d, %d)-->(%d, %d): Length: %.2f, Angle:%.2f' % \
               (self.point1[0], self.point1[1], self.point2[0], self.point2[1], self.length, self.angle)


def get_contours(img):
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    ret, binary = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)
    contours, hierarchy = cv2.findContours(binary, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    for i in range(1, len(contours)):
        approx = cv2.approxPolyDP(contours[i], 0.01 * cv2.arcLength(contours[i], True), True)
        contours[i] = approx
    return contours


def generate_lines(contour):
    lines = []
    for i in range(len(contour) - 1):
        lines.append(ContourLine((contour[i][0][0], contour[i][0][1]), (contour[i + 1][0][0], contour[i + 1][0][1])))
    lines.append(ContourLine((contour[-1][0][0], contour[-1][0][1]), (contour[0][0][0], contour[0][0][1])))
    return lines


class Handler:
    """

    """

    def __init__(self, source):
        self.src = cv2.imread(source)
        self.contours = get_contours(self.src)[1:]  # contours are in clock-wise order
        self.contour_dict = {}

    def generate_contour_dict(self):
        for i in range(len(self.contours)):
            self.contour_dict[i] = generate_lines(self.contours[i])


class Fact:
    """

    """

    def __init__(self, fact, about):
        self.fact = fact
        self.about = about

    def __str__(self):
        s = '<\n' + self.fact + '\n'
        s += '\n'.join(list(map(str, self.about)))
        s += '\n>\n'
        return s


def close_enough(point1, point2):
    return ((point1[0] - point2[0]) ** 2 + (point1[1] - point2[1]) ** 2) < close_threshold


def average_point(point1, point2):
    return (point1[0] + point2[0]) / 2, (point1[1] + point2[1]) / 2


def get_meeting_point(line1, line2):
    if abs(line1.angle - line2.angle) < parallel_threshold:
        return 'parallel'
    else:
        for point1 in [line1.point1, line1.point2]:
            for point2 in [line2.point1, line2.point2]:
                if close_enough(point1, point2):
                    return average_point(point1, point2)
    return None


def get_vector(from_point, to_point):
    return (to_point[0] - from_point[0]), (to_point[1] - from_point[1])


def get_inner_product(vector1, vector2):
    return vector1[0] * vector2[0] + vector1[1] * vector2[1]


def get_included_angle(line1, line2):
    meeting_point = get_meeting_point(line1, line2)
    if not meeting_point:
        return None  # lines not met
    elif meeting_point == 'parallel':
        return 'parallel'  # parallel lines have no included angle
    else:
        middle_point1 = average_point(line1.point1, line1.point2)
        middle_point2 = average_point(line2.point1, line2.point2)
        vector1 = get_vector(meeting_point, middle_point1)
        vector2 = get_vector(meeting_point, middle_point2)
        inner_product = get_inner_product(vector1, vector2)
        cos_theta = inner_product / (math.sqrt(get_inner_product(vector1, vector1)) *
                                     math.sqrt(get_inner_product(vector2, vector2)))
        return math.degrees(math.acos(cos_theta))


def is_equal(line1, line2):
    return abs(line1.length - line2.length) < equal_threshold


def is_parallel(line1, line2):
    return True if get_included_angle(line1, line2) == 'parallel' else False


def is_vertical(line1, line2):
    included_angle = get_included_angle(line1, line2)
    return True if included_angle and abs(included_angle - 90.0) < vertical_threshold else False


def is_acute(line1, line2):
    included_angle = get_included_angle(line1, line2)
    return included_angle and included_angle < 90.0


def is_obtuse(line1, line2):
    included_angle = get_included_angle(line1, line2)
    return included_angle and included_angle > 90.0


def is_closure(lines):
    result = True
    for i in range(len(lines)-1):
        result = result and get_meeting_point(lines[i], lines[i+1])
    result = result and get_meeting_point(lines[-1], lines[0])
    return result


def lines_closure(facts, lines):
    if len(lines) == 3 and is_closure(lines):
        facts.append(Fact('3 closure lines', lines))
    elif len(lines) == 4 and is_closure(lines):
        facts.append(Fact('4 closure lines', lines))
    elif len(lines) == 5 and is_closure(lines):
        facts.append(Fact('5 closure lines', lines))
    elif len(lines) == 6 and is_closure(lines):
        facts.append(Fact('6 closure lines', lines))
    else:
        facts.append(Fact('no closure lines', lines))


def is_lines_all_equal(lines):
    result = True
    for i in range(len(lines)-1):
        result = result and is_equal(lines[i], lines[i+1])
    result = result and is_equal(lines[-1], lines[0])
    return result


def lines_all_equal(facts, lines):
    if is_lines_all_equal(lines):
        facts.append(Fact('lines are all equal', lines))


def parallel_line_pairs(facts):
    count = 0
    lines = []
    for fact in facts:
        if fact.fact == '2 lines are parallel':
            lines += fact.about
            count += 1
            facts.remove(fact)
    if count:
        facts.append(Fact(str(count) + ' pairs of parallel lines', lines))


def acute_angles_count(facts):
    count = 0
    angles = []
    for fact in facts:
        if fact.fact == '1 angle is acute angle':
            angles += fact.about
            count += 1
    if count:
        facts.append(Fact(str(count) + ' angles are acute angle', angles))


def right_angles_count(facts):
    count = 0
    angles = []
    for fact in facts:
        if fact.fact == '1 angle is right angle':
            angles += fact.about
            count += 1
    if count:
        facts.append(Fact(str(count) + ' angles are right angle', angles))


def about_angle(facts, line1, line2):
    if is_parallel(line1, line2):
        facts.append(Fact('2 lines are parallel', [line1, line2]))
    elif is_vertical(line1, line2):
        facts.append(Fact('1 angle is right angle', [line1, line2]))
    elif is_acute(line1, line2):
        facts.append(Fact('1 angle is acute angle', [line1, line2]))
    elif is_obtuse(line1, line2):
        facts.append(Fact('1 angle is obtuse angle', [line1, line2]))


def about_length(facts, line1, line2):
    if is_equal(line1, line2):
        facts.append(Fact('2 lines are equal', [line1, line2]))


def generate_contour_facts(lines):
    line_facts = []
    angle_facts = []
    for i in range(len(lines)):
        for j in range(i + 1, len(lines)):
            about_length(line_facts, lines[i], lines[j])
            about_angle(angle_facts, lines[i], lines[j])
    lines_closure(line_facts, lines)
    lines_all_equal(line_facts, lines)
    parallel_line_pairs(angle_facts)
    acute_angles_count(angle_facts)
    right_angles_count(angle_facts)
    return line_facts, angle_facts


class ContourFact:
    """

    """

    def __init__(self, line_num, line_facts, angle_facts):
        self.line_num = line_num
        self.line_facts = line_facts
        self.angle_facts = angle_facts

    def __str__(self):
        s = ('--About Lines-- %d lines\n' % self.line_num)
        for line in (list(map(str, self.line_facts))):
            s += line
        s += '--About Angles--\n'
        for line in (list(map(str, self.angle_facts))):
            s += line
        s += '}\n'
        return s


class FactGenerator:
    """

    """

    def __init__(self, contour_dict):
        self.contour_dict = contour_dict
        self.handled_facts = {}
        self.file = open('../facts/facts.txt', 'w+')

    def __del__(self):
        if self.file:
            self.file.close()

    def generate_fact(self):
        for i in range(len(self.contour_dict)):
            lines = self.contour_dict.get(i)
            line_facts, angle_facts = generate_contour_facts(lines)
            cnt_fact = ContourFact(len(lines), line_facts, angle_facts)
            self.handled_facts['Contour' + str(i)] = cnt_fact
            self.file.write('Contour #%d\n{\n' % i)
            self.file.write(str(cnt_fact))


close_threshold = 5
equal_threshold = 5
parallel_threshold = 5
vertical_threshold = 5
if __name__ == '__main__':
    handler = Handler('../test/test40.png')
    handler.generate_contour_dict()
    generator = FactGenerator(handler.contour_dict)
    generator.generate_fact()
