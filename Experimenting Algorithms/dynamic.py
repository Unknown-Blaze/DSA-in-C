def fib(n):
    if n == 1: 
        return 1
    if n == 2:
        return 1
    return fib(n-1) + fib(n-2)

def better_fib(n, m = None):
    if m is None or len(m) < n + 1:
        m = [-1] * (n + 1)
    if n == 1:
        return 1
    if n == 2:
        return 1
    m[0] = 1
    m[1] = 1
    if m[n] == -1:
        m[n] = better_fib(n-1, m)+better_fib(n-2, m)
    return m[n]


def q(n, m = None):
    
    if m is None or len(m) < n + 1:
        m = [-1] * (n + 1)
    # if (n == 1):
    #     return 1
    # if (n == 2):
    #     return 2
    # if (n == 3):
    #     return 2
    # if (n == 4):
    #     return 3
    # if (n == 5):
    #     return 5
    m[0] = 1
    m[1] = 2
    m[2] = 2
    m[3] = 3
    m[4] = 5
    if m[n] == -1:
        m[n] = q(n-1, m) + q(n-3, m) + q(n-5, m)
    return m[n]
    
        
# 1 3 5, n
# 1 1 1 1 1, 1 1 3, 1 3 1, 3 1 1, 5

for i in range(6):
    print(str(i+1) + ": ", q(i))