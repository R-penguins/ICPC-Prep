#include <bits/stdc++.h>
using namespace std;
using VI = vector<int>;
using VVI = vector<VI>;
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
  int e, nxt;
};

int V, E;
vector<Edge> e, er;
VI sp, spr;
int group_cnt;
VI group_num;
VB v;
VI stk;

void fill_forward(int x)
{
  int i;
  v[x] = true;
  for (i = sp[x]; i; i = e[i].nxt)
    if (!v[e[i].e])
      fill_forward(e[i].e);
  stk[++stk[0]] = x;
}

void fill_backward(int x)
{
  int i;
  v[x] = false;
  group_num[x] = group_cnt;
  for (i = spr[x]; i; i = er[i].nxt)
    if (v[er[i].e])
      fill_backward(er[i].e);
}

void add_edge(int v1, int v2) //add edge v1->v2
{
  e[++E].e = v2;
  e[E].nxt = sp[v1];
  sp[v1] = E;
  er[E].e = v1;
  er[E].nxt = spr[v2];
  spr[v2] = E;
}

void SCC()
{
  int i;
  stk[0] = 0;
  fill(v.begin(), v.end(), false);
  for (i = 1; i <= V; i++)
    if (!v[i])
      fill_forward(i);
  group_cnt = 0;
  for (i = stk[0]; i >= 1; i--)
    if (v[stk[i]])
    {
      group_cnt++;
      fill_backward(stk[i]);
    }
}

int main(int argc, char const *argv[])
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int maxe, maxv;
  e = vector<Edge>(maxe);
  er = vector<Edge>(maxe);
  sp = VI(maxv);
  spr = VI(maxv);
  group_num = VI(maxv);
  v = VB(maxv);
  stk = VI(maxv);
  return 0;
}
