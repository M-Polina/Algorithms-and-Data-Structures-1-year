#include <iostream>
#include <fstream>
#include <queue>
 
using namespace std;
 
#define BLACK -1
 
int n;
vector<vector<int>> adj_list;
vector<int> colors;
 
void depth_first_search(int vertex, int color)
{
    colors[vertex] = color;
 
    for (int i = 0; i < adj_list[vertex].size(); i++)
    {
        if (colors[adj_list[vertex][i]] == BLACK)
        {
            depth_first_search(adj_list[vertex][i], color);
        }
    }
}
 
int main()
{
    ifstream in("components.in");
    ofstream out("components.out");
    int m;
    in >> n >> m;
    colors.resize(n, BLACK);
    adj_list.resize(n);
 
    for (int i = 0; i < m; i++)
    {
        int a, b;
        in >> a >> b;
        adj_list[a - 1].push_back(b - 1);
        adj_list[b - 1].push_back(a - 1);
    }
 
    int color = 1;
    for (int i = 0; i < n; i++)
    {
        if (colors[i] == BLACK)
        {
            depth_first_search(i, color);
            color++;
        }
    }
 
    out << --color << endl;
 
    for (int i = 0; i < n; i++)
    {
        out << colors[i] << " ";
    }
     
    out << endl;
}