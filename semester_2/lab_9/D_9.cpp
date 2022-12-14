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
    int time;
    Vertice(int color_ = WHITE, int time_ = -1)
        : color(color_), time(time_)
    {
    }
};
 
int n;
int color;
int time;
int ind_to_put;
vector<vector<int>> adj_list;
vector<vector<int>> reverse_edj_list;
vector<Vertice> vertices;
vector<int> sorted_graph;
 
void depth_first_search(int ind, int color)
{
    int index = -1;
    vertices[sorted_graph[ind]].color = color;
 
    for (int i = 0; i < reverse_edj_list[sorted_graph[ind]].size(); i++)
    {
        if (vertices[reverse_edj_list[sorted_graph[ind]][i]].color == BLACK)
        {
            for (int k = 0; k < sorted_graph.size(); ++k)
            {
                if (sorted_graph[k] == reverse_edj_list[sorted_graph[ind]][i])
                {
                    index = k;
                    break;
                }
            }
            depth_first_search(index, color);
        }
    }
}
 
void depth_first_search_sort(int vertex)
{
    time++;
    vertices[vertex].color = GRAY;
 
    for (int i = 0; i < adj_list[vertex].size(); i++)
    {
        if (vertices[adj_list[vertex][i]].color == WHITE)
        {
            depth_first_search_sort(adj_list[vertex][i]);
        }
    }
    vertices[vertex].color = BLACK;
    time++;
    vertices[vertex].time = time;
    sorted_graph[ind_to_put] = vertex;
    ind_to_put--;
}
 
void topological_sort()
{
    ind_to_put = n - 1;
    time = 0;
    for (int i = 0; i < n; i++)
    {
        if (vertices[i].color == WHITE)
        {
            depth_first_search_sort(i);
        }
    }
}
 
void condensation()
{
    topological_sort();
 
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < adj_list[i].size(); ++j)
        {
            reverse_edj_list[adj_list[i][j]].push_back(i);
        }
    }
 
    color = 1;
    for (int i = 0; i < n; i++)
    {
        if (vertices[sorted_graph[i]].color == BLACK)
        {
            depth_first_search(i, color);
            color++;
        }
    }
}
 
int main()
{
    int m;
    ifstream in("cond.in");
    ofstream out("cond.out");
    in >> n >> m;
    vertices.resize(n);
    adj_list.resize(n);
    sorted_graph.resize(n);
    reverse_edj_list.resize(n);
 
    int a, b;
    for (int i = 0; i < m; i++)
    {
        in >> a >> b;
        adj_list[a - 1].push_back(b - 1);
    }
 
    condensation();
 
    out << --color << endl;
    for (int i = 0; i < n; i++)
    {
        out << vertices[i].color << " ";
    }
 
    out << endl;
}