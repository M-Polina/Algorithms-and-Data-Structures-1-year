fin = open("input.txt", "r")
fout = open("output.txt", "w")
n = int(fin.readline())
matrix = [[0] * n for i in range(n)]
 
for i in range(n):
    matrix[i] = list(map(int, fin.readline().split()))
 
is_matrix = True
for i in range(n):
    for j in range(n):
        if ((matrix[i][j] != matrix[j][i]) or (i == j and matrix[i][j] == 1)):
            is_matrix = False
            break
 
answer = "YES" if is_matrix else "NO"
print(answer, end='', file=fout)
 
fout.close()