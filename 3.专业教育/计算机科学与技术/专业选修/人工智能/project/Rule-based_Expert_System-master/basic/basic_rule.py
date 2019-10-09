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

id_count = 0


class Rule:
    """
    前项通过 与 连接
    """
    def __init__(self, ants, con, desc=None):
        self.id = None
        self.antecedent = ants
        self.consequent = con
        self.description = desc
        self.__calculate_id__()

    def __calculate_id__(self):
        global id_count
        self.id = id_count
        id_count += 1

    def __str__(self):
        s = ''
        s += ('Rule: #%d\n' % self.id)
        if self.description:
            s += ('Description: %s\n' % self.description)
        s += 'IF\t\t'
        for ant in self.antecedent:
            s += ('%s\n' % ant)
            if ant != self.antecedent[-1]:
                s += ('\tand\t')
        s += ('THEN\t%s\n' % self.consequent)
        return s

if __name__ == '__main__':
    # r = Rule(['两边之和大于第三边','我是测试'], '测试是三角形', '测试')
    # print(r)
    # rr = Rule(['对边平行','对边相等'], '测试是长方形', '又是测试')
    # print(rr)
    pass
