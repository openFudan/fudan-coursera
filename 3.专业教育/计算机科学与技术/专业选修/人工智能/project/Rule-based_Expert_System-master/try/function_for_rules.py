from line import Line
from point import Point

__author__ = 'liuyang'


def line_collect(lines):
    if not lines:
        return None
    line_num = {}
    lines = sorted(lines, cmp=lambda x, y: cmp(x.length, y.length))
    cur_line = lines[0]
    line_num[cur_line.length] = 1
    idx = 1
    while idx < len(lines):
        if abs(lines[idx].length - cur_line.length) <= 0:
            line_num[cur_line.length] += 1
        else:
            cur_line = lines[idx]
            line_num[cur_line.length] = 1
        idx += 1
    return line_num


def line_equal(line_num):
    for (length, number) in line_num.items():
        if number == 1:
            line_num.pop(length)
    return line_num


def line_equal_number(line_num):
    line_num = sorted(line_num.itervalues(), reverse=True)
    return line_num[0]


lines = []
lines.append(Line(Point(0,0), Point(0,3)))
lines.append((Line(Point(0,0), Point(3,0))))
lines.append((Line(Point(0,0), Point(-3,0))))
lines.append((Line(Point(0,0), Point(0,-3))))
lines.append((Line(Point(0,0), Point(2.5,0))))
lines.append((Line(Point(0,0), Point(5,0))))
lines.append((Line(Point(0,0), Point(0,0.1))))

# for line in lines:
#     print(line)
result = line_collect(lines)
print(result)
result = line_equal(result)
print(result)
result = line_equal_number(result)
print(result)