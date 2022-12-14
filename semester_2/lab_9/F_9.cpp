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
    int person;
    int wins;
    Vertice(int color_ = WHITE, int person_ = -1, int wins_ = -1)
        : color(color_), person(person_), wins(wins_) {}
};
 
int n;
int ind_to_put;
vector<vector<int>> adj_list;
vector<Vertice> vertices;
vector<int> sorted_graph;
 
void breadth_first_search(int start)
{
    vertices[start].color = GRAY;
    vertices[start].person = 0;
 
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
                vertices[adj_list[pivot][i]].person = (vertices[pivot].person + 1) % 2;
                queue.push(adj_list[pivot][i]);
            }
        }
 
        vertices[pivot].color = BLACK;
    }
}
 
void depth_first_search_sort(int vertex)
{
    vertices[vertex].color = GRAY;
 
    for (int i = 0; i < adj_list[vertex].size(); i++)
    {
        if (vertices[adj_list[vertex][i]].color == WHITE)
        {
            depth_first_search_sort(adj_list[vertex][i]);
        }
    }
    vertices[vertex].color = BLACK;
    sorted_graph[ind_to_put] = vertex;
    ind_to_put--;
}
 
void topological_sort()
{
    ind_to_put = n - 1;
    for (int i = 0; i < n; i++)
    {
        if (vertices[i].color == WHITE)
        {
            depth_first_search_sort(i);
        }
    }
}
 
int find_winner()
{
    for (int i = n - 1; i >= 0; --i)
    {
        if (adj_list[sorted_graph[i]].size() == 0)
        {
            vertices[sorted_graph[i]].wins = (vertices[sorted_graph[i]].person + 1) % 2;
        }
        else
        {
            int this_wins = false;
 
            for (int j = 0; j < adj_list[sorted_graph[i]].size(); j++)
            {
                if (vertices[adj_list[sorted_graph[i]][j]].wins == vertices[sorted_graph[i]].person)
                    this_wins = true;
            }
            if (this_wins)
                vertices[sorted_graph[i]].wins = vertices[sorted_graph[i]].person;
            else
                vertices[sorted_graph[i]].wins = (vertices[sorted_graph[i]].person + 1) % 2;
        }
    }
    return 0;
}
 
int main()
{
    int m;
    int start;
    ifstream in("game.in");
    ofstream out("game.out");
    in >> n >> m >> start;
    start--;
    vertices.resize(n);
    adj_list.resize(n);
    sorted_graph.resize(n);
 
    for (int i = 0; i < m; i++)
    {
        int a, b;
        in >> a >> b;
        adj_list[a - 1].push_back(b - 1);
    }
 
    breadth_first_search(start);
 
    for (int i = 0; i < n; i++)
    {
        vertices[i].color = WHITE;
    }
 
    topological_sort();
    find_winner();
 
    if (vertices[start].wins == 0)
        out << "First player wins" << endl;
    else
        out << "Second player wins" << endl;
}