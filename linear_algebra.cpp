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

// Gauss-Jordan elimination with full pivoting.
//
// Uses:
// (1) solving systems of linear equations (AX=B)
// (2) inverting matrices (AX=I)
// (3) computing determinants of square matrices
//
// Running time: O(nˆ3)
//
// INPUT: a[][] = an nxn matrix
// b[][] = an nxm matrix
//
// OUTPUT: X = an nxm matrix (stored in b[][])
// Aˆ{-1} = an nxn matrix (stored in a[][])
// returns determinant of a[][]
double gauss_jordan(VVD &a, VVD &b)
{
  const int n = a.size();
  const int m = b[0].size();
  VI irow(n), icol(n), ipiv(n);
  double det = 1;
  for (int i = 0; i < n; i++)
  {
    int pj = -1, pk = -1;
    for (int j = 0; j < n; j++)
      if (!ipiv[j])
        for (int k = 0; k < n; k++)
          if (!ipiv[k])
            if (pj == -1 || fabs(a[j][k]) > fabs(a[pj][pk]))
            {
              pj = j;
              pk = k;
            }
    if (fabs(a[pj][pk]) < EPS)
    {
      cerr << "Matrix is singular." << endl;
      exit(0);
    }
    ipiv[pk]++;
    swap(a[pj], a[pk]);
    swap(b[pj], b[pk]);
    if (pj != pk)
      det *= -1;
    irow[i] = pj;
    icol[i] = pk;
    double c = 1.0 / a[pk][pk];
    det *= a[pk][pk];
    a[pk][pk] = 1.0;
    for (int p = 0; p < n; p++)
      a[pk][p] *= c;
    for (int p = 0; p < m; p++)
      b[pk][p] *= c;
    for (int p = 0; p < n; p++)
      if (p != pk)
      {
        c = a[p][pk];
        a[p][pk] = 0;
        for (int q = 0; q < n; q++)
          a[p][q] -= a[pk][q] * c;
        for (int q = 0; q < m; q++)
          b[p][q] -= b[pk][q] * c;
      }
  }
  for (int p = n - 1; p >= 0; p--)
    if (irow[p] != icol[p])
    {
      for (int k = 0; k < n; k++)
        swap(a[k][irow[p]], a[k][icol[p]]);
    }
  return det;
}

int main(int argc, char const *argv[])
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  return 0;
}
