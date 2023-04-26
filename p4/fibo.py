from multiprocessing import Pool

def fibonacci_formula(n):
    golden_ratio = (1 + 5 ** 0.5) / 2
    fib_n = int((golden_ratio ** n - (1 - golden_ratio) ** n) / 5 ** 0.5)
    return fib_n


if __name__ == '__main__':
    n = 1000
    num_procesadores = 4
    pool = Pool(processes=num_procesadores)
    results = pool.map(fibonacci_formula, range(n+1))
    for data in results:
      print(data)
