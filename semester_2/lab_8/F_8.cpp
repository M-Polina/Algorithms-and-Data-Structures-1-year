#include <iostream>
#include <fstream>
#include <queue>
 
using namespace std;
 
#define WHITE 0
#define GRAY 1
#define BLACK -1
#define START 1
#define FINISH 2
#define PATH 0
#define FENCE -1
 
struct Point
{
    int x;
    int y;
};
 
struct Vertice
{
    int key;
    int color;
    int dist;
    string path;
};
 
int n;
int m;
vector<vector<struct Vertice>> matrix;
 
void breadth_first_search(struct Point start)
{
    matrix[start.x][start.y].color = GRAY;
    matrix[start.x][start.y].dist = 0;
 
    queue<struct Point> queue;
    queue.push(start);
    struct Point pivot;
 
    while (!queue.empty())
    {
        pivot = queue.front();
        queue.pop();
 
        if (pivot.x - 1 >= 0)
        {
            if (matrix[pivot.x - 1][pivot.y].color == WHITE)
            {
                struct Point vertice = {pivot.x - 1, pivot.y};
                matrix[vertice.x][vertice.y].color = GRAY;
                matrix[vertice.x][vertice.y].dist = matrix[pivot.x][pivot.y].dist + 1;
                matrix[vertice.x][vertice.y].path = matrix[pivot.x][pivot.y].path + "U";
                queue.push(vertice);
            }
        }
 
        if (pivot.x + 1 < n)
        {
            if (matrix[pivot.x + 1][pivot.y].color == WHITE)
            {
                struct Point vertice = {pivot.x + 1, pivot.y};
                matrix[vertice.x][vertice.y].color = GRAY;
                matrix[vertice.x][vertice.y].dist = matrix[pivot.x][pivot.y].dist + 1;
                matrix[vertice.x][vertice.y].path = matrix[pivot.x][pivot.y].path + "D";
                queue.push(vertice);
            }
        }
 
        if (pivot.y - 1 >= 0)
        {
            if (matrix[pivot.x][pivot.y - 1].color == WHITE)
            {
                struct Point vertice = {pivot.x, pivot.y - 1};
                matrix[vertice.x][vertice.y].color = GRAY;
                matrix[vertice.x][vertice.y].dist = matrix[pivot.x][pivot.y].dist + 1;
                matrix[vertice.x][vertice.y].path = matrix[pivot.x][pivot.y].path + "L";
                queue.push(vertice);
            }
        }
 
        if (pivot.y + 1 < m)
        {
            if (matrix[pivot.x][pivot.y + 1].color == WHITE)
            {
                struct Point vertice = {pivot.x, pivot.y + 1};
                matrix[vertice.x][vertice.y].color = GRAY;
                matrix[vertice.x][vertice.y].dist = matrix[pivot.x][pivot.y].dist + 1;
                matrix[vertice.x][vertice.y].path = matrix[pivot.x][pivot.y].path + "R";
                queue.push(vertice);
            }
        }
 
        matrix[pivot.x][pivot.y].color = BLACK;
    }
}
 
int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    in >> n >> m;
 
    matrix.resize(n);
 
    char a;
    struct Point start = {0, 0};
    struct Point finish = {0, 0};
 
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            in >> a;
            struct Vertice vertice;
            vertice.color = WHITE;
            vertice.dist = -1;
            vertice.path = "";
 
            switch (a)
            {
            case '.':
                vertice.key = PATH;
                break;
            case 'S':
                vertice.key = START;
                start.x = i;
                start.y = j;
                break;
            case 'T':
                vertice.key = FINISH;
                finish.x = i;
                finish.y = j;
                break;
            case '#':
                vertice.key = FENCE;
                vertice.color = BLACK;
                break;
            }
 
            matrix[i].push_back(vertice);
        }
    }
 
    breadth_first_search(start);
 
    out << matrix[finish.x][finish.y].dist << endl;
    out << matrix[finish.x][finish.y].path << endl;
}