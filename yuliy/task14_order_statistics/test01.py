#!/usr/bin/env python

import sys

n = 5
k = 3
data = []

def generate():
    for i in xrange(0, n):
        data.append(i)

def main():
    print n, k
    generate()
    for elem in data:
        print elem

    data.sort()
    print>>sys.stderr, ''
    print>>sys.stderr, ('test01 answer=%d' % data[k])

if __name__ == '__main__':
    main()
