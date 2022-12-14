#include <vector>
#include <iostream>
#include <fstream>
 
using namespace std;
 
#define WHITE 0
#define GRAY 1
#define BLACK -1
 
int n;
vector<vector<int>> adj_list;
vector<int> colors;
vector<int> sorted_graph;
int ind_to_put;
 
bool g_path_search()
{
    bool has_next;
    for (int i = 0; i < n - 1; ++i)
    {
        has_next = false;
        for (int j = 0; j < adj_list[sorted_graph[i]].size(); ++j)
        {
            if (adj_list[sorted_graph[i]][j] == sorted_graph[i + 1])
            {
                has_next = true;
            }
        }
        if (has_next == false)
            return false;
    }
    return true;
}
 
void depth_first_search(int vertex)
{
    colors[vertex] = GRAY;
 
    for (int i = 0; i < adj_list[vertex].size(); i++)
    {
        if (colors[adj_list[vertex][i]] == WHITE)
        {
            depth_first_search(adj_list[vertex][i]);
        }
    }
    colors[vertex] = BLACK;
    sorted_graph[ind_to_put] = vertex;
    ind_to_put--;
}
 
void topological_sort()
{
    ind_to_put = n - 1;
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
    int m;
    ifstream in("hamiltonian.in");
    ofstream out("hamiltonian.out");
    in >> n >> m;
    colors.resize(n, WHITE);
    adj_list.resize(n);
    sorted_graph.resize(n, -1);
 
    int a, b;
    for (int i = 0; i < m; i++)
    {
        in >> a >> b;
        adj_list[a - 1].push_back(b - 1);
    }
 
    topological_sort();
 
    bool has_g_path;
    has_g_path = g_path_search();
 
    if (has_g_path)
        out << "YES" << endl;
    else
        out << "NO" << endl;
}