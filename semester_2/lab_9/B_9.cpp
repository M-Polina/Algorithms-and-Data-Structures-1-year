#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
#define GRAY 1
#define WHITE 0
#define BLACK -1
 
int n;
int cycle_start = -1;
bool is_acyclic = true;
bool cycle_started = false;
vector<vector<int>> adj_list;
vector<int> colors;
vector<int> cycle = {};
 
void depth_first_search(int vertex)
{
    colors[vertex] = GRAY;
 
    for (int i = 0; i < adj_list[vertex].size(); i++)
    {
        if (is_acyclic == true)
        {
            if (colors[adj_list[vertex][i]] == WHITE)
            {
                depth_first_search(adj_list[vertex][i]);
            }
            if (colors[adj_list[vertex][i]] == GRAY)
            {
                cycle_start = adj_list[vertex][i];
                is_acyclic = false;
                cycle_started = true;
            }
        }
    }
 
    if (cycle_started)
    {
        cycle.push_back(vertex);
    }
    if (vertex == cycle_start)
    {
        cycle_started = false;
    }
    colors[vertex] = BLACK;
}
 
void cycle_find()
{
    for (int i = 0; i < n; i++)
    {
        if (colors[i] == WHITE)
        {
            depth_first_search(i);
        }
        if (is_acyclic == false)
        {
            return;
        }
    }
}
 
int main()
{
    ifstream in("cycle.in");
    ofstream out("cycle.out");
    int m;
    in >> n >> m;
    colors.resize(n, WHITE);
    adj_list.resize(n);
 
    int a, b;
    for (int i = 0; i < m; ++i)
    {
        in >> a >> b;
        adj_list[a - 1].push_back(b - 1);
    }
 
    cycle_find();
 
    if (is_acyclic)
    {
        out << "NO";
    }
    else
    {
        out << "YES" << endl;
        for (int i = cycle.size() - 1; i >= 0; --i)
        {
            out << cycle[i] + 1 << " ";
        }
    }
 
    out << endl;
}