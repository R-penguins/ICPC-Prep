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

// return a % b (positive value)
int mod(int a, int b)
{
  return ((a % b) + b) % b;
}

// (aˆb) mod m via successive squaring
int powermod(int a, int b, int m)
{
  int ret = 1;
  while (b)
  {
    if (b & 1)
      ret = mod(ret * a, m);
    a = mod(a * a, m);
    b >>= 1;
  }
  return ret;
}

// returns g = gcd(a, b); finds x, y such that d = ax + by
int extended_euclid(int a, int b, int &x, int &y)
{
  int xx = y = 0;
  int yy = x = 1;
  while (b)
  {
    int q = a / b;
    int t = b;
    b = a % b;
    a = t;
    t = xx;
    xx = x - q * xx;
    x = t;
    t = yy;
    yy = y - q * yy;
    y = t;
  }
  return a;
}

// finds all solutions to ax = b (mod n)
VI modular_linear_equation_solver(int a, int b, int n)
{
  int x, y;
  VI ret;
  int g = extended_euclid(a, n, x, y);
  if (!(b % g))
  {
    x = mod(x * (b / g), n);
    for (int i = 0; i < g; i++)
      ret.push_back(mod(x + i * (n / g), n));
  }
  return ret;
}

// computes b such that ab = 1 (mod n), returns -1 on failure
int mod_inverse(int a, int n)
{
  int x, y;
  int g = extended_euclid(a, n, x, y);
  if (g > 1)
    return -1;
  return mod(x, n);
}

// Chinese remainder theorem (special case): find z such that
// z % m1 = r1, z % m2 = r2. Here, z is unique modulo M = lcm(m1, m2).
// Return (z, M). On failure, M = -1.
PII chinese_remainder_theorem(int m1, int r1, int m2, int r2)
{
  int s, t;
  int g = extended_euclid(m1, m2, s, t);
  if (r1 % g != r2 % g)
    return make_pair(0, -1);
  return make_pair(mod(s * r2 * m1 + t * r1 * m2, m1 * m2) / g, m1 * m2 / g);
}

// Chinese remainder theorem: find z such that
// z % m[i] = r[i] for all i. Note that the solution is
// unique modulo M = lcm_i (m[i]). Return (z, M). On
// failure, M = -1. Note that we do not require the a[i]’s
// to be relatively prime.
PII chinese_remainder_theorem(const VI &m, const VI &r)
{
  PII ret = make_pair(r[0], m[0]);
  for (int i = 1; i < m.size(); i++)
  {
    ret = chinese_remainder_theorem(ret.second, ret.first, m[i], r[i]);
    if (ret.second == -1)
      break;
  }
  return ret;
}

// computes x and y such that ax + by = c
// returns whether the solution exists
bool linear_diophantine(int a, int b, int c, int &x, int &y)
{
  if (!a && !b)
  {
    if (c)
      return false;
    x = 0;
    y = 0;
    return true;
  }
  if (!a)
  {
    if (c % b)
      return false;
    x = 0;
    y = c / b;
    return true;
  }
  if (!b)
  {
    if (c % a)
      return false;
    x = c / a;
    y = 0;
    return true;
  }
  int g = gcd(a, b);
  if (c % g)
    return false;
  x = c / g * mod_inverse(a / g, b / g);
  y = (c - a * x) / b;
  return true;
}

int main(int argc, char const *argv[])
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  return 0;
}
