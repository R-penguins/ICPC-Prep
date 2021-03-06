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

int main(int argc, char const *argv[])
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  // Implementation of Dijkstra’s algorithm using adjacency lists
  // and priority queue for efficiency.
  //
  // Running time: O(|E| log |V|)
  int N, s, t;
  cin >> N >> s >> t;
  vector<vector<PII>> edges(N);
  for (int i = 0; i < N; i++)
  {
    int M;
    cin >> M;
    for (int j = 0; j < M; j++)
    {
      int vertex, dist;
      cin >> vertex >> dist;
      edges[i].push_back(make_pair(dist, vertex)); // note order of arguments here
    }
  }
  // use priority queue in which top element has the "smallest" priority
  priority_queue<PII, vector<PII>, greater<PII>> Q;
  vector<int> dist(N, numeric_limits<int>::infinity()), dad(N, -1);
  Q.push(make_pair(0, s));
  dist[s] = 0;
  while (!Q.empty())
  {
    PII p = Q.top();
    Q.pop();
    int here = p.second;
    if (here == t)
      break;
    if (dist[here] != p.first)
      continue;
    for (vector<PII>::iterator it = edges[here].begin(); it != edges[here].end(); it++)
    {
      if (dist[here] + it->first < dist[it->second])
      {
        dist[it->second] = dist[here] + it->first;
        dad[it->second] = here;
        Q.push(make_pair(dist[it->second], it->second));
      }
    }
  }
  cout << dist[t] << '\n';
  if (dist[t] < numeric_limits<int>::infinity())
    for (int i = t; i != -1; i = dad[i])
      cout << i << (i == s ? '\n' : ' ');

  return 0;
}
