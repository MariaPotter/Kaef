#!/usr/bin/env python3

import json

import numpy as np
import pentapy as pp

TO_BE_PRINTED = True

def big_f(i, n, x):
    left = max(0, (i - 1) / n)
    right = min(1, (i + 1) / n)

    if x < left or x > right:
        return 0
    else:
        return -(n * (x - i / n)) ** 2 + 1

def small_f(i, n, x):
    left = max(0, i / n)
    right = min(1, (i + 1) / n)

    if x < left or x > right:
        return 0
    else:
        return -(2 * n * (x - (i + 0.5) / n)) ** 2 + 1

def counted_result(x, sol):
    N = sol.shape[0] // 2

    val = 0
    for j in range(N + 1):
        val += big_f(j, N, x) * sol[2 * j]
    for j in range(N):
        val += small_f(j, N, x) * sol[2 * j + 1]

    return val

def derivative(vals, h):
    ret = [None for i in range(len(vals))]

    ret[0] = (vals[1] - vals[0]) / h
    for i in range(1, len(vals) - 1): 
        ret[i] = (vals[i + 1] - vals[i - 1]) / (2 * h)
    ret[-1] = (vals[-1] - vals[-2]) / h

    return ret

def second_derivative(vals, h):
    ret = [None for i in range(len(vals))]

    ret[0] = (vals[2] - 2 * vals[1] + vals[0]) / (h * h)
    for i in range(1, len(vals) - 1): 
        ret[i] = (vals[i + 1] - 2 * vals[i] + vals[i - 1]) / (h * h)
    ret[-1] = (vals[-1] - 2 * vals[-2] + vals[-3]) / (h * h)

    return ret

def read_vec(path):
    fd = open(path, 'r')
    vec = np.array(list(map(np.double, fd.read().split('\n')[:-1])), dtype = np.double)
    fd.close()

    return vec

def progonka():
    a = np.concatenate([read_vec('tmp/a.txt'), [0, 0]], axis=0)
    b = np.concatenate([read_vec('tmp/b.txt'), [0]], axis = 0)
    c = read_vec('tmp/c.txt')
    d = np.concatenate([[0], read_vec('tmp/d.txt')], axis=0)
    e = np.concatenate([[0, 0], read_vec('tmp/e.txt')], axis=0)

    N = c.shape[0] // 2

    f = read_vec('tmp/f.txt')

    M = np.stack([a, b, c, d, e], axis = 0)

    sol = pp.solve(M, f, is_flat=True, solver=1)

    return sol, N

def transform(s):
    return np.array(list(map(float, s.split(' '))))

def anal_solution(x):
    if x <= 0.5:
        return (0.7730691888029851/pow(2.71828182845904523536028747135,1.*x) - 0.5*pow(2.71828182845904523536028747135,x) + 1.*x)
    else:
        return (0.8338518903489248/pow(2.71828182845904523536028747135,0.816496580927726032732428024902*x) - 0.6048653425704819*pow(2.71828182845904523536028747135,0.816496580927726032732428024902*x) + 1.*x)

def main():
    sol, N = progonka()

    result = []
    errors = []

    for i in range(N + 1):
        x = i / N

        result.append(counted_result(x, sol))
        errors.append(np.abs(counted_result(x, sol) - anal_solution(x)))
    
    print('Невязка: ', "{:10.4e}".format(np.amax(errors)))
    # print('Значение в 0.5: ', np.amax(result[int(N/2)]))

    json_to_write = json.dumps({
        'x' : [i / N for i in range(N + 1)],
        'y_count': list(result),
        'y_anal' : [anal_solution(i / N) for i in range(N + 1)]
    })

    fd = open('tmp/points.json', 'w')
    fd.write(json_to_write)
    fd.close()

if __name__ == '__main__':
    main()