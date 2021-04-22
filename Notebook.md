# ICPC Notebook

Assuming g++ compiler with -std=gnu++17 (Kattis setting)

## C++ Language

### Limits

```C++
INT_MAX
numeric_limits<double>::max()
-INFINITY // -∞, for floating point only
NAN // for floating point only
isnan()
```

`int`: [-2<sup>31</sup>, 2<sup>31</sup> - 1] = [-2147483648, 2147483647], about 2 * 10<sup>9</sup>

`long long`: [-2<sup>63</sup>, 2<sup>63</sup> - 1] = [-9223372036854775808, 9223372036854775807], about 9 * 10<sup>18</sup>

`__int128`: [-2<sup>127</sup>, 2<sup>127</sup> - 1] = [-170141183460469231731687303715884105728, 170141183460469231731687303715884105727], about 10<sup>38</sup> ❗ GCC specific

```C++
ostream &operator<<(ostream &os, const __int128 &x)
{
  static const __int128 MOD = 1e19;
  if (x < 0)
    os << '-';
  if (x / MOD)
    os << static_cast<unsigned long long>(x < 0 ? -1 * (x / MOD) : x / MOD)
        << setfill('0') << setw(19) << static_cast<unsigned long long>(x < 0 ? -1 * (x % MOD) : x % MOD) << setfill(' ');
  else
    os << static_cast<unsigned long long>(x < 0 ? -1 * x : x);
  return os;
}
```

`double`: +-2<sup>52</sup> about 4.5 * 10<sup>15</sup> precision

### I/O

- Framework

Read `k` times

```C++
int k;
cin >> k;
while (k--)
{

}
```

Read until 0

```C++
int n;
while ((cin >> n) && n)
{

}
```

Read every line

```C++
string line;
while (getline(cin, line))
{

}
```

Fill a known-size vector

```C++
vector<int> arr(n);
for (int& i : arr)
    cin >> i;
```

- Floating point

```C++
cout << setprecision(12);  // rounded, total 12 digits. Default 6.
cout << fixed << setprecision(12); // 12 digits after .
cout << showpoint << 10.0 << noshowpoint; // 10.0000
```

- Base

```C++
cout << oct << 27 << ' ' << hex << 27 << ' ' << dec << 27; // 33 1b 27
cout << showbase << oct << 27 << ' ' << hex << 27 << noshowbase; // 033 0x1b
cout << showbase << uppercase << hex << 27 << nouppercase; // 0X1B
```

- Padding

```C++
cout << setw(6) << setfill('0') << 3; // 000003
cout << setw(6) << left << setfill('#') << -3; // -3####
```

### String

- Numeric conversion

```C++
string str = to_string(42); // "42"
stoi(str); // 42
stoi(str, 0, 8); // 34, in octal
string str2 = "pi = 3.14";
stod(str2.substr(str2.find_first_of("+-.012345789"))); // 3.14
```

## Math

### Tricks

```C++
n * pow(2, m) = (n << m); // m: non-negative int
max({a, b, c});
```

### Computational geometry

- A basic `Point` class

```C++
struct Point
{
  double x;
  double y;
  Point(const double x = 0, const double y = 0) : x(x), y(y) { }
  Point(const Point& p) : x(p.x), y(p.y) { }
};

istream& operator>>(istream& is, const Point& p)
{
  is >> p.x >> p.y;
}
```

- `geometry.cpp`

### Numeric algorithms

- `number_theory.cpp`
- `linear_algebra.cpp`
- `reduced_row_echelon.cpp`
- `linear_programming.cpp`

## Graph Theory

### Representation

- Adjacency list O(V + E)

```C++
vector<vector<int>> adj(v); // vertex number of all neighbors
```

- Adjacency matrix, for quick query of edges' existance or dense graph (E close to V<sup>2</sup>), O(V<sup>2</sup>)

```C++
vector<vector<int>> w(v, vector<int>(v)); // edge weights
```

### Tree

n - 1 edges, no cycles

### Topological sort

O(V + E). DFS and insert at front of list when finishing a vertex

### DAG path count

O(V + E)

- Top-down DP

```C++
vector<int> path_num;
int num(int u, int terminal)
{
  if (u == terminal)
    return 1;
  if (path_num[u])
    return path_num[u];
  for (Edge& edge : adj[u])
    path_num[u] += num(edge.to);
  return path_num[u];
}
```

- Bottom-up DP with topological sort

### Cut vertex / bridge

For undirected graph, root is cut vertex when it has 2 or more children. Let low(v) be the earlist connected ancestor's previsit time. if low(u.child) >= pre(u), u is a cut vertex. if low(u.child) > pre(u), (u, v) is a bridge.

```C++
vector<vector<int>> adj;
vector<int> pre /* 0 */, low;
vector<bool> iscut; // false
int dfs_clock = 0;
int dfs(int u, int p)
{
  int lowu = pre[u] = ++dfs_clock;
  int child = 0;
  for (int v : adj[u]) {
    if (!pre[v]) {
      ++child;
      int lowv = dfs(v, u);
      lowu = min(lowu, lowv);
      if (lowv >= pre[u])
        iscut[u] = true;
    } else if (pre[v] < pre[u] && v != p)
      lowu = min(lowu, pre[v]);
  }
  if (p < 0 && child == 1)
    iscut[u] = false;
  low[u] = lowu;
  return lowu;
}
```

Bi-connected: every pair of vertices has at least 2 paths of unique vetices. No cut vertex. Every pair of edges in the same simple loop.

Edge bi-connected: every pair of vertices has at least 2 paths of unique edges. No bridges. Every edge in a loop.

code: p416

### Strongly connected components

Kosaraju: DFS in reverse graph in reversed topological sorted order (2 DFS).

Tarjan: p422

### 2-SAT as directed graph

### Shortest path

#### Bellman-Ford

O(VE)

```C++
bool bellman_ford(vector<vector<Edge>>& adj, int s, vector<double>& dist, vector<int>& p)
{
  int n = adj.size();
  dist = vector<double>(n, INFINITY); // use INFINITY in double if dist might be added
  dist[s] = 0;
  p = vector<int>(n);
  vector<bool> in_queue(n);
  in_queue[s] = true;
  vector<int> cnt(n);
  cnt[s] = 1;

  queue<int> q;
  q.push(s);
  while (!q.empty())
  {
    int cur = q.front();
    q.pop();
    for (Edge& edge : adj[cur])
      if (dist[cur] + edge.weight < dist[edge.to])
      {
        dist[edge.to] = dist[cur] + edge.weight;
        p[edge.to] = cur;
        if (!in_queue[edge.to])
        {
          if (++cnt[edge.to] > n - 1)
            return true;
          q.push(edge.to);
          in_queue[edge.to] = true;
        }
      }
  }
  return false;
}

```

#### Dijkstra

O(E log(V)) with adjacency list, no negative cycle

```C++
struct Edge
{
  int to, weight;
  Edge() {};
  Edge(int t, int w) : to(t), weight(w) {};
};

void dijkstra(vector<vector<Edge>>& adj, int s, /* int t, */ vector<double>& dist, vector<int>& p)
{
  dist.assign(adj.size(), INFINITY); // use INFINITY in double if dist might be added elsewhere
  dist[s] = 0;
  p = vector<int>(adj.size());
  priority_queue<PII, vector<PII>, greater<PII>> q; // weight, vertex
  q.emplace(0, s);
  while (!q.empty())
  {
    PII cur = q.top();
    q.pop();
    // if (cur.second == t)
    //   break;
    if (dist[cur.second] != cur.first)
      continue;
    for (Edge& edge : adj[cur.second])
      if (cur.first + edge.weight < dist[edge.to])
      {
        dist[edge.to] = cur.first + edge.weight;
        p[edge.to] = cur.second;
        q.emplace(dist[edge.to], edge.to);
      }
  }
}
```

### Minimum spanning tree

Connect all vertices, min weight.

Kruskal: sort edges, add if u, v not in the same set with Union-Find.

## Data structures

### Set

Complexity: set log(n), unordered_set O(1)

### Heap

```C++
priority_queue<int> q; // Max heap
priority_queue<int, vector<int>, greater<int>> q; // Min heap

// custom comparator
auto cmp = [](Edge& a, Edge& b) { return a.val > b.val; };
priority_queue<Edge, vector<Edge>, decltype(cmp)> q(cmp);
```

### Disjoint-set

- Average O(1)

```C++
struct Uf {
  Uf(int n) : p(n) {
    iota(p.begin(), p.end(), 0);
  }
  int find(int x) {
    if (x != p[x])
      p[x] = find(p[x]);
    return p[x];
  }
  int merge(int x, int y) {
    p[find(x)] = find(y);
  }
  vector<int> p;
};
```

union by size

```C++
struct Uf {
  Uf(int n) : p(n), size(n, 1) {
    iota(p.begin(), p.end(), 0);
  }
  int find(int x) {
    if (x != p[x])
      p[x] = find(p[x]);
    return p[x];
  }
  int merge(int x, int y) {
    int xp = find(x), yp = find(y);
    if (xp == yp)
      return;
    if (size[xp] > size[yp])
      swap(xp, yp);
    p[xp] = yp;
    size[yp] += xp;
  }
  vector<int> p, size;
};
```

### Binary Indexed Tree / Fenwick Tree

For mutable range sum query.

- Add, sum: O(log n)

⚠ BIT index begin with 1. Sum[m, n] = sum(n) - sum(m - 1)

```C++
struct Bit
{
  Bit(int size) : tree(size + 1) { }
  Bit(vector<int>& arr) : tree(arr)
  {
    for (int i = 1; i < tree.size(); ++i)
    {
      int p = i + (i & -i);
      if (p < tree.size())
        tree[p] += tree[i];
    }
  }
  int sum(int ind)
  {
    int ans = 0;
    while (ind)
    {
      ans += tree[ind];
      ind -= (ind & -ind);
    }
    return ans;
  }
  void add(int ind, int val)
  {
    while (ind < tree.size())
    {
      tree[ind] += val;
      ind += (ind & -ind);
    }
  }
  vector<int> tree;
};
```

### Sparse-Table

For Range Minimum Query. (Immutable)

- Initialize: O(n log n)
- Query: O(1)

```C++
struct St {
  St(vector<int> &arr) : d(arr.size()) {
    int n = d.size();
    for (int i = 0; i < n; ++i) {
      d[i].reserve(sizeof(int) * 8 - __builtin_clz(n - i)); // optional. can use log2(n)
      d[i].push_back(arr[i]);
    }
    for (int j = 1; (1 << j) <= n; ++j)
      for (int i = 0; i + (1 << j) <= n; ++i)
        d[i].push_back(max(d[i][j - 1], d[i + (1 << j - 1)][j - 1]));
  }
  int query(int begin, int end) {
    int k = 0;
    while ((1 << k + 1) <= end - begin)
      ++k;
    return max(d[begin][k], d[end - (1 << k)][k]);
  }
  vector<vector<int>> d;
};
```

### Segment Tree

Range query, single modification

```C++
struct Segtree {
  Segtree(int n) : n(n), tree(2 * n){};
  void init() {
    for (int i = n - 1; i > 0; --i)
      tree[i] = tree[2 * i] + tree[2 * i + 1];
  }
  int query(int begin, int end) {
    int res = 0;
    for (begin += n, end += n; begin < end; begin /= 2, end /= 2) {
      if (begin % 2)
        res += tree[begin++];
      if (end % 2)
        res += tree[--end];
    }
    return res;
  }
  void modify(int pos, int val) {
    for (tree[pos += n] = val; pos > 1; pos /= 2)
      tree[pos / 2] = tree[pos] + tree[pos ^ 1];
  }
  vector<int> tree;
  int n;
};
```

Single query, range modification

```C++
struct Segtree {
  Segtree(int n) : n(n), tree(2 * n){};
  int query(int pos) {
    int res = 0;
    for (pos += 0; pos > 0; pos /= 2)
      res += tree[pos];
    return res;
  }
  void modify(int begin, int end, int val) {
    for (begin += n, end += n; begin < end; begin /= 2, end /= 2) {
      if (begin % 2)
        tree[begin++] += val;
      if (end % 2)
        tree[--end] += val;
  }
  void push() {
    for (int i = 1; i < n; ++i) {
      tree[2 * i] += tree[i];
      tree[2 * i + 1] += tree[i];
      tree[i] = 0;
    }
  }
  vector<int> tree;
  int n;
};
```

Range query, range modification. Lazy propagation.

Increment update, max query.

```C++
struct Segtree {
  Segtree(int n)
      : n(n), tree(2 * n), d(n), h(sizeof(int) * 8 - __builtin_clz(n)){};
  void init() {
    for (int i = n - 1; i > 0; --i)
      tree[i] = max(tree[2 * i], tree[2 * i + 1]);
  }
  void apply(int pos, int val) {
    tree[pos] += val;
    if (pos < n)
      d[pos] += val;
  }
  void update(int pos) {
    while (pos > 1) {
      pos /= 2;
      tree[pos] = max(tree[pos * 2], tree[pos * 2 + 1]) + d[pos];
    }
  }
  void push(int pos) {
    for (int height = h; height > 0; --height) {
      int i = pos >> height;
      if (d[i]) { // is labeled
        apply(2 * i, d[i]);
        apply(2 * i + 1, d[i]);
        d[i] = 0;
      }
    }
  }
  int query(int begin, int end) {
    push(begin += n);
    push((end += n) - 1);
    int res = INT_MIN;
    for (; begin < end; begin /= 2, end /= 2) {
      if (begin % 2)
        res = max(res, tree[begin++]);
      if (end % 2)
        res = max(res, tree[--end]);
    }
    return res;
  }
  void modify(int begin, int end, int val) {
    begin += n;
    end += n;
    for (int l = begin, r = end; l < r; l /= 2, r /= 2) {
      if (l % 2)
        apply(l++, val);
      if (r % 2)
        apply(--r, val);
    }
    update(begin);
    update(end - 1);
  }
  vector<int> tree, d;
  int n, h;
};
```

Increment modification, sum query

```C++
struct Segtree {
  Segtree(int n)
      : n(n), tree(2 * n), d(n), h(sizeof(int) * 8 - __builtin_clz(n)){};
  void init() {
    for (int i = n - 1; i > 0; --i)
      tree[i] = tree[2 * i] + tree[2 * i + 1];
  }
  void update(int pos) {
    int k = 2;
    while (pos > 1) {
      pos /= 2;
      tree[pos] = tree[pos * 2] + tree[pos * 2 + 1] + d[pos] * k;
      k *= 2;
    }
  }
  void apply(int pos, int val, int len) {
    tree[pos] += val * len;
    if (pos < n)
      d[pos] += val;
  }
  void push(int pos) {
    for (int height = h, k = 1 << (h - 1); height > 0; --height, k /= 2) {
      int i = pos >> height;
      if (d[i]) {
        apply(2 * i, d[i], k);
        apply(2 * i + 1, d[i], k);
        d[i] = 0;
      }
    }
  }
  LL query(int begin, int end) {
    begin += n;
    end += n;
    push(begin);
    push(end - 1);
    LL res = 0;
    for (; begin < end; begin /= 2, end /= 2) {
      if (begin % 2)
        res += tree[begin++];
      if (end % 2)
        res += tree[--end];
    }
    return res;
  }
  void modify(int begin, int end, int val) {
    begin += n;
    end += n;
    for (int l = begin, r = end, k = 1; l < r; l /= 2, r /= 2, k *= 2) {
      if (l % 2)
        apply(l++, val, k);
      if (r % 2)
        apply(--r, val, k);
    }
    update(begin);
    update(end - 1);
  }
  vector<long long> tree, d;
  int n, h;
};
```

Assignment update, sum query

```C++
struct Segtree {
  Segtree(int n)
      : n(n), tree(2 * n), d(n), h(sizeof(int) * 8 - __builtin_clz(n)){};
  void init() {
    for (int i = n - 1; i > 0; --i)
      tree[i] = tree[2 * i] + tree[2 * i + 1];
  }
  void calc(int pos, int len) {
    tree[pos] = d[pos] ? (d[pos] * len) : (tree[pos * 2] + tree[pos * 2 + 1]);
  }
  void apply(int pos, int val, int len) {
    tree[pos] = val * len;
    if (pos < n)
      d[pos] = val;
  }
  void push(int pos) {
    for (int height = h, k = 1 << (h - 1); height > 0; --height, k /= 2) {
      int i = pos >> height;
      if (d[i]) {
        apply(2 * i, d[i], k);
        apply(2 * i + 1, d[i], k);
        d[i] = 0;
      }
    }
  }
  int query(int begin, int end) {
    push(begin += n);
    push(end += n);
    int res = 0;
    for (; begin < end; begin /= 2, end /= 2) {
      if (begin % 2)
        res += tree[begin++];
      if (end % 2)
        res += tree[--end];
    }
    return res;
  }
  void modify(int begin, int end, int val) {
    if (val == 0)
      return;
    begin += n;
    end += n;
    push(begin);
    push(end - 1);
    bool cl = false, cr = false;
    int k = 1;
    for (; begin < end; begin /= 2, end /= 2, k *= 2) {
      if (cl)
        calc(begin - 1, k);
      if (cr)
        calc(end, k);
      if (begin % 2) {
        apply(begin++, val, k);
        cl = true;
      }
      if (end % 2) {
        apply(--end, val, k);
        cr = true;
      }
    }
    for (--begin; end > 0; begin /= 2, end /= 2, k *= 2) {
      if (cl)
        calc(begin, k);
      if (cr && (!cl || begin != end))
        calc(end, k);
    }
  }
  vector<int> tree, d;
  int n, h;
};
```

## Techniques

### Discretization

### Continuous Sum

a1 + a2 + ... + an = Bn - a(n - 1)

### Inversion number with merge-sort

O(n log n)

```C++
VI arr;
VI temp;
int inv_num(int l, int r)
{
  if (l + 1 == r)
    return 0;
  int mid = l + (r - l) / 2;
  int ans = inv_num(l, mid) + inv_num(mid, r);
  int i = l;
  int j = mid;
  for (int k = l; k < r; ++k)
    if (i == mid || (j < r && arr[j] < arr[i]))
    {
      temp[k] = arr[j++];
      ans += mid - i;
    }
    else
      temp[k] = arr[i++];
  copy(temp.begin() + l, temp.begin() + r, arr.begin() + l);
  return ans;
}
```

### Ordering / all permutations

n! orderings

```C++
VI arr(4);
iota(arr.begin(), arr.end(), 0);
do {
  for (int i : arr)
    cout << i << ' ';
  cout << '\n';
} while (next_permutation(arr.begin(), arr.end()));
```

// UVa221
