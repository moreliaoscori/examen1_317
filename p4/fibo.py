import multiprocessing

def fibonacci_formula(n):
    golden_ratio = (1 + 5 ** 0.5) / 2
    fib_n = int((golden_ratio ** n - (1 - golden_ratio) ** n) / 5 ** 0.5)
    return fib_n

def fibonacci_multiprocessing():
    with multiprocessing.Pool() as pool:
        results = pool.map(fibonacci_formula, range(1001))
    return results

if __name__ == '__main__':
    print(fibonacci_multiprocessing())

