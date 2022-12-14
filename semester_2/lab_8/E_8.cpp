#include <iostream>
#include <fstream>
#include <queue>
 
using namespace std;
 
#define WHITE 0
#define GRAY 1
#define BLACK -1
 
struct Vertice
{
 
    int color;
    int dist;
    int parent;
};
 
int n;
vector<vector<int>> adj_list;
vector<struct Vertice> vertices;
 
void breadth_first_search(int start)
{
    vertices[start].color = GRAY;
    vertices[start].dist = 0;
 
    queue<int> queue;
    queue.push(start);
    int pivot;
 
    while (!queue.empty())
    {
        pivot = queue.front();
        queue.pop();
 
        for (int i = 0; i < adj_list[pivot].size(); i++)
        {
            if (vertices[adj_list[pivot][i]].color == WHITE)
            {
                vertices[adj_list[pivot][i]].color = GRAY;
                vertices[adj_list[pivot][i]].dist = vertices[pivot].dist + 1;
                vertices[adj_list[pivot][i]].parent = pivot;
                queue.push(adj_list[pivot][i]);
            }
        }
 
        vertices[pivot].color = BLACK;
    }
}
 
int main()
{
    int m;
    ifstream in("pathbge1.in");
    ofstream out("pathbge1.out");
    in >> n >> m;
    vertices.resize(n);
    adj_list.resize(n);
 
    for (int i = 0; i < n; i++)
    {
        vertices[i].color = WHITE;
        vertices[i].dist = -1;
        vertices[i].parent = -1;
    }
 
    for (int i = 0; i < m; i++)
    {
        int a, b;
        in >> a >> b;
        adj_list[a - 1].push_back(b - 1);
        adj_list[b - 1].push_back(a - 1);
    }
 
    breadth_first_search(0);
 
    for (int i = 0; i < n; i++)
    {
        out << vertices[i].dist << " ";
    }
    out << endl;
}