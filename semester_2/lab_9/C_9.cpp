#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
 
using namespace std;
 
#define WHITE 0
#define GRAY 1
#define BLACK -1
 
class Vertice
{
public:
    int color;
    int part;
    Vertice(int color_ = WHITE, int part_ = -1)
        : color(color_), part(part_)
    {
    }
};
 
int n;
bool is_bipartite = true;
vector<vector<int>> adj_list;
vector<Vertice> vertices;
 
void breadth_first_search(int start)
{
    vertices[start].color = GRAY;
    vertices[start].part = 0;
 
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
                vertices[adj_list[pivot][i]].part = (vertices[pivot].part + 1) % 2;
                queue.push(adj_list[pivot][i]);
            }
            else
            {
                if (vertices[adj_list[pivot][i]].part == vertices[pivot].part)
                {
                    is_bipartite = false;
                    return;
                }
            }
        }
 
        vertices[pivot].color = BLACK;
    }
}
 
void graph_is_bipartite()
{
    for (int i = 0; i < n; i++)
    {
        if (vertices[i].color == WHITE)
        {
            breadth_first_search(i);
        }
        if (is_bipartite == false)
        {
            return;
        }
    }
}
 
int main()
{
    int m;
    ifstream in("bipartite.in");
    ofstream out("bipartite.out");
    in >> n >> m;
    vertices.resize(n);
    adj_list.resize(n);
 
    for (int i = 0; i < m; i++)
    {
        int a, b;
        in >> a >> b;
        adj_list[a - 1].push_back(b - 1);
        adj_list[b - 1].push_back(a - 1);
    }
 
    graph_is_bipartite();
 
    if (is_bipartite == false)
    {
        out << "NO";
    }
    else
    {
        out << "YES";
    }
    out << endl;
}