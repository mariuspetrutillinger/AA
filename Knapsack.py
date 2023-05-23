def max_sum(knapsack, objects):
    total = 0
    values = {0}

    for obj in objects:
        for val in list(values):
            if (val + obj <= knapsack):
                total = max(total, val + obj)
                values.add(val + obj)
    print (values)
    return total

def max_sum_aprox(input_file):
    total = 0
    k = int(input_file.readline().strip())
    line = input_file.readline().strip()

    while (line):
        x = int(line)
        if (x + total <= k):
            total += x
        elif (total < x):
            total = x
        line = input_file.readline().strip()
    
    return total


S = [3, 4, 5, 2]
K = 10
f = open("knapsack.txt", "r")

suma_maxima = max_sum(K, S)
suma_maxima_aprox = max_sum_aprox(f)
print("Suma maxima este:", suma_maxima)
print("Suma maxima aproximata este:", suma_maxima_aprox)


def matrix():
    n = len(S)
    matrix = [[0 for i in range(K + 1)] for j in range(len(S) + 1)]
    for i in range(1, n + 1):
        for j in range(K + 1):
            if (j < S[i - 1]):
                matrix[i][j] = matrix[i - 1][j]
            else:
                matrix[i][j] = max(matrix[i - 1][j], matrix[i - 1][j - S[i - 1]] + S[i - 1])
        
    for row in matrix:
        print(row)


matrix()