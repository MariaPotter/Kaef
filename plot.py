#!/usr/bin/env python3

import json

import sys

import numpy as np

import matplotlib
import matplotlib.pyplot as plt

plt.rcParams.update({'font.size': 30})

def main(k):
    fd = open('tmp/points.json', 'r')
    text = fd.read()
    fd.close()

    parsed = json.loads(text)


    plt.figure(figsize=(15, 10), dpi=300)

    plt.plot(parsed['x'], parsed['y_count'], color='black')
    plt.plot(parsed['x'], parsed['y_anal'], color='orange')

    plt.xlabel('x')
    plt.ylabel('u')

    plt.savefig('plot ' + k + '.png')

if __name__ == '__main__':
    if len (sys.argv) > 1:
        main(sys.argv[1])
    else:
        main({100})
