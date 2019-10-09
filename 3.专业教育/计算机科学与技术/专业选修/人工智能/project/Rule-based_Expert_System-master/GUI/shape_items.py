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
__author__ = 'Soros Liu'
tree1 = [
    ['三角形', [
        '锐角三角形',
        '直角三角形',
        '钝角三角形',
        ['等腰三角形', [
            '等腰直角三角形',
            '等腰锐角三角形',
            '等腰钝角三角形',
        ]],
        '等边三角形'
        ]],
    ['四边形', [
        '平行四边形', [
            '矩形', [
                '正方形',
            ]],
        '梯形', [
            '等腰梯形',
            '直角梯形',
            ]]],
    ['五边形', [
        '正五边形']],
    ['六边形', [
        '正六边形']],
    ]

tree = [
    ['triangle', [
        'acute triangle',
        'right triangle',
        'obtuse triangle',
        ['isosceles triangle', [
            'right and isosceles triangle',
            'acute and isosceles triangle',
            'obtuse and isosceles triangle',
        ]],
        'equilateral triangle'
        ]],
    ['quadrilateral', [
        ['parallelogram', [
            ['rectangle', [
                'square',
            ]],
            'rhombus',
        ]],
        ['trapezoid', [
            'isosceles trapezoid',
            'right trapezoid',
            ]]]],
    ['pentagon', [
        'regular pentagon']],
    ['hexagon', [
        'regular hexagon']],
    ]
