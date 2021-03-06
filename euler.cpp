#include <bits/stdc++.h>
using namespace std;
using VI = vector<int>;
using VII = vector<VI>;
using VD = vector<double>;
using VVD = vector<VD>;
using VS = vector<string>;
using VVS = vector<VS>;
using VB = vector<bool>;
using VVB = vector<VB>;
using PII = pair<int, int>;
using PDD = pair<double, double>;
constexpr double pi = 3.1415926535897932385;
constexpr double EPS = 1e-12;

struct Edge
{
  int next_vertex;
  list<Edge>::iterator reverse_edge;
  Edge(int next_vertex)
      : next_vertex(next_vertex)
  {
  }
};

int num_vertices;
vector<list<Edge>> adj; // adjacency list
vector<int> path;

void find_path(int v)
{
  while (adj[v].size() > 0)
  {
    int vn = adj[v].front().next_vertex;
    adj[vn].erase(adj[v].front().reverse_edge);
    adj[v].pop_front();
    find_path(vn);
  }
  path.push_back(v);
}

void add_edge(int a, int b)
{
  adj[a].push_front(Edge(b));
  auto ita = adj[a].begin();
  adj[b].push_front(Edge(a));
  auto itb = adj[b].begin();
  ita->reverse_edge = itb;
  itb->reverse_edge = ita;
}

int main(int argc, char const *argv[])
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  const int max_vertices = 3;
  adj = vector<list<Edge>>(max_vertices);
  return 0;
}
