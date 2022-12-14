fin = open("input.txt", "r")
fout = open("output.txt", "w")
n, m = list(map(int, fin.readline().split()))
matrix = [[0] * n for i in range(n)]
 
has_par = False
for i in range(m):
    l, r = list(map(int, fin.readline().split()))
    if (matrix[l - 1][r - 1] == 1):
        has_par = True
    matrix[l - 1][r - 1] = 1
 
for i in range(n):
    for j in range(n):
        if ((matrix[i][j] == 1) and (matrix[j][i] == 1) and (i != j)):
            has_par = True
            break
 
answer = "YES" if has_par else "NO"
print(answer, file=fout)
 
fout.close()