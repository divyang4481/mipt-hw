#!/usr/bin/env python

import sys

n = 10
k = 5
data = []

def generate():
    for _ in xrange(0, k):
        data.append(5)
    for _ in xrange(0, n-k):
        data.append(7)

def main():
    print n, k
    generate()
    for elem in data:
        print elem

    data.sort()
    print>>sys.stderr, ''
    print>>sys.stderr, ('test02 answer=%d' % data[k])

if __name__ == '__main__':
    main()
