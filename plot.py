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

    plt.annotate('$X$', xy=(1, 0), xytext=(10,-7.5), ha='left', va='top', xycoords='axes fraction', textcoords='offset points')
    plt.annotate('$U$', xy=(0, 1), xytext=(-35,2), ha='left', va='top', xycoords='axes fraction', textcoords='offset points')

    plt.title(f'N = {str(k)}', fontsize=30)
    plt.figtext(0.65,0.843,'Невязка: ' + parsed['discrepancy'], fontsize='small')
    
    plt.savefig('out/plot ' + k + '.png', transparent=True)

if __name__ == '__main__':
    if len (sys.argv) > 1:
        main(sys.argv[1])
    else:
        print("Некорректные входные аргументы :С")
