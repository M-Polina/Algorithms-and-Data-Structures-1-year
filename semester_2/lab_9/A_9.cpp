#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
#define GRAY 1
#define WHITE 0
#define BLACK -1
 
int n;
int time;
int ind_to_put;
bool is_acyclic = true;
vector<vector<int>> adj_list;
vector<int> colors;
vector<int> time_list;
vector<int> sorted_graph;
 
void depth_first_search(int vertex)
{
    time++;
    colors[vertex] = GRAY;
 
    for (int i = 0; i < adj_list[vertex].size(); i++)
    {
        if (colors[adj_list[vertex][i]] == WHITE)
        {
            depth_first_search(adj_list[vertex][i]);
        }
        if (colors[adj_list[vertex][i]] == GRAY)
        {
            is_acyclic = false;
        }
    }
    colors[vertex] = BLACK;
    time++;
    time_list[vertex] = time;
    sorted_graph[ind_to_put] = vertex;
    ind_to_put--;
}
 
void topological_sort()
{
    ind_to_put = n - 1;
    time = 0;
    for (int i = 0; i < n; i++)
    {
        if (colors[i] == WHITE)
        {
            depth_first_search(i);
        }
    }
}
 
int main()
{
    ifstream in("topsort.in");
    ofstream out("topsort.out");
    int m;
    in >> n >> m;
    colors.resize(n, WHITE);
    time_list.resize(n, -1);
    adj_list.resize(n);
    sorted_graph.resize(n, -1);
 
    int a, b;
    for (int i = 0; i < m; ++i)
    {
        in >> a >> b;
        adj_list[a - 1].push_back(b - 1);
    }
 
    topological_sort();
 
    if (is_acyclic)
        for (int i = 0; i < n; i++)
        {
            out << sorted_graph[i] + 1 << " ";
        }
    else
        out << -1 << " ";
         
    out << endl;
}