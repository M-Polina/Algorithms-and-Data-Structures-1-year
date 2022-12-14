fin = open("input.txt", "r")
fout = open("output.txt", "w")
n, m = list(map(int, fin.readline().split()))
matrix = [[0] * n for i in range(n)]
 
for i in range(m):
    l, r = list(map(int, fin.readline().split()))
    matrix[l - 1][r - 1] = 1
 
for i in range(n):
    for j in range(n):
        print(matrix[i][j], end=' ', file=fout)
    print("\n", end='', file=fout)
 
fout.close()