#!/usr/bin/env python

import random
import sys

def main():
    for _ in xrange(0, 100):
        print random.randint(-1e6, 1e6)

if __name__ == '__main__':
    main()
