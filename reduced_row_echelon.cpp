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

// Reduced row echelon form via Gauss-Jordan elimination
// with partial pivoting. This can be used for computing
// the rank of a matrix.
//
// Running time: O(nˆ3)
//
// INPUT: a[][] = an n x m matrix
//
// OUTPUT: rref[][] = an n x m matrix (stored in a[][])
// returns rank of a[][]
int rref(VVD &a)
{
  int n = a.size();
  int m = a[0].size();
  int r = 0;
  for (int c = 0; c < m && r < n; c++)
  {
    int j = r;
    for (int i = r + 1; i < n; i++)
      if (fabs(a[i][c]) > fabs(a[j][c]))
        j = i;
    if (fabs(a[j][c]) < EPS)
      continue;
    swap(a[j], a[r]);
    double s = 1.0 / a[r][c];
    for (int j = 0; j < m; j++)
      a[r][j] *= s;
    for (int i = 0; i < n; i++)
      if (i != r)
      {
        double t = a[i][c];
        for (int j = 0; j < m; j++)
          a[i][j] -= t * a[r][j];
      }
    r++;
  }
  return r;
}

int main(int argc, char const *argv[])
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  return 0;
}
