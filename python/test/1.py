#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def triangles(n):
    row = [1]
    for i in range(n):
        yield (row)
        row, rowR = row + [0], [0] + row
        for k in range(len(row)):
            row[k] += rowR[k]
    pass
for i in triangles(10):
    print(i)
