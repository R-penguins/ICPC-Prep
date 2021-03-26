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

int dcmp(double x)
{
  return abs(x) < EPS ? 0 : (x < 0 ? -1 : 1);
}

//////////////////// Point /////////////////////////
struct Point
{
  double x;
  double y;
  Point(const double x = 0, const double y = 0) : x(x), y(y) { }
  Point(const Point &p) : x(p.x), y(p.y) { }
  Point(const Point& a, const Point& b) : x(b.x - a.x), y(b.y - a.y) { }
  Point& operator*=(const double k)
  {
    x *= k;
    y *= k;
    return *this;
  }
  Point& operator/=(const double k)
  {
    x /= k;
    y /= k;
    return *this;
  }
  double length() const
  {
    return sqrt(x * x + y * y);
  }

  void normalize()
  {
    const double len = length();
    x /= len;
    y /= len;
  }

  double angle() const
  {
    return atan2(y, x);
  }
};

Point operator-(const Point &l, const Point &r)
{
  return Point(l.x - r.x, l.y - r.y);
}

Point operator+(const Point &l, const Point &r)
{
  return Point(l.x + r.x, l.y + r.y);
}

Point operator*(const Point &p, const double k)
{
  return Point(k * p.x, k * p.y);
}

Point operator/(const Point &p, const double k)
{
  return Point(p.x / k, p.y / k);
}

bool operator==(const Point &l, const Point &r)
{
  return abs(l.x - r.x) <= EPS && abs(l.y - r.y) <= EPS;
}

bool operator<(const Point &l, const Point &r)
{
  return l.x < r.x || (l.x == r.x && l.y < r.y);
}

istream& operator>>(istream& is, const Point& p)
{
  is >> p.x >> p.y;
}

ostream& operator<<(ostream& os, const Point& p)
{
  os << "(" << p.x << ", " << p.y << ")";
}

double distance_squared(const Point& a, const Point& b)
{
  const Point c = a - b;
  return c.x * c.x + c.y * c.y; 
}

double distance(const Point& a, const Point& b)
{
  return sqrt(distance_squared(a, b));
}
////////////////////       /////////////////////////

/////////////////// Vector ////////////////////////
using Vector = Point;

double dot(const Vector &l, const Vector &r)
{
  return l.x * r.x + l.y * r.y;
}

double angle(const Vector &l, const Vector &r)
{
  return acos(dot(l, r) / l.length() / r.length());
}

double cross(const Vector &l, const Vector &r)
{
  return l.x * r.y - l.y * r.x;
}

Vector normalized(const Vector& vec)
{
  const double len = vec.length();
  return Vector(vec.y / len, vec.x / len);
}
///////////////////        ////////////////////////

struct Line
{
  Point point;
  Vector slope;
  Line(Point pt = 0, Vector vec = 0) : point(pt), slope(vec) { }
};

struct Segment
{
  Point a, b;
  Vector ab;
  Segment(Point a = 0, Point b = 0) : a(a), b(b)
  {
    ab = Vector(a, b);
  }
};

double signed_area(const Point &a, const Point &b, const Point &c)
{
  return cross(Vector(a, b), Vector(a, c)) / 2.0;
}

double signed_area(const vector<Point> &pts)
{
  double area = 0;
  for (int i = 0; i < pts.size(); i++) {
    int j = (i + 1) % pts.size();
    area += pts[i].x * pts[j].y - pts[j].x * pts[i].y;
  }
  return area / 2.0;
}

Vector rotate(const Vector &vec, double a)
{
  return Vector(vec.x * cos(a) - vec.y * sin(a),
                vec.x * sin(a) + vec.y * cos(a));
}

// Make sure cross(vp, vq) != 0
Point intersection(const Point &p, const Vector &vp, const Point &q, const Vector &vq)
{
  return p + vp * cross(vq, Vector(q, p)) / cross(vp, vq);
}

double distance(const Point &p, const Line &line)
{
  return abs(cross(line.slope, Vector(line.point, p))) / line.slope.length();
}

double distance(const Point &p, const Segment &seg)
{
  if (seg.a == seg.b)
    return distance(p, seg.a);
  Vector ap(seg.a, p), bp(seg.b, p);
  if (dot(seg.ab, ap) < -EPS)
    return ap.length();
  else if (dot(seg.ab, bp) > EPS)
    return bp.length();
  return abs(cross(seg.ab, ap)) / seg.ab.length();
}

Point projection(const Point &p, const Line &line)
{
  return line.point +
    line.slope * dot(line.slope, Vector(line.point, p)) / dot(line.slope, line.slope);
}

bool hasIntersection(const Segment &l, const Segment &r)
{
    double la = cross(l.ab, r.a - l.a), lb = cross(l.ab, r.b - l.a),
           ra = cross(r.ab, l.a - r.a), rb = cross(r.ab, l.b - r.a);
    return dcmp(la) * dcmp(lb) < 0 && dcmp(ra) * dcmp(rb) < 0;
}

bool on(const Point &p, const Segment &seg)
{
  return dcmp(cross(seg.a - p, seg.b - p)) == 0 &&
          dcmp(dot(seg.a - p, seg.b - p)) < 0;
}

// Compute the 2D convex hull of a set of points using the monotone chain
// algorithm. Eliminate redundant points from the hull if REMOVE_REDUNDANT is
// #defined.
//
// Running time: O(n log n)
//
/// OUTPUT: a vector of points in the convex hull, counterclockwise, starting
// with bottommost/leftmost point
// INPUT: a vector of input points, unordered.
void convex_hull(vector<Point> &pts) {
  sort(pts.begin(), pts.end());
  pts.erase(unique(pts.begin(), pts.end()), pts.end());
  vector<Point> up, dn;
  for (int i = 0; i < pts.size(); i++) {
    while (up.size() > 1 && signed_area(up[up.size()-2], up.back(), pts[i]) >= 0) up.pop_back();
    while (dn.size() > 1 && area2(dn[dn.size()-2], dn.back(), pts[i]) <= 0) dn.pop_back();
    up.push_back(pts[i]);
    dn.push_back(pts[i]);
  }
  pts = dn;
  for (int i = (int) up.size() - 2; i >= 1; i--) pts.push_back(up[i]);
  #ifdef REMOVE_REDUNDANT
  if (pts.size() <= 2) return;
  dn.clear();
  dn.push_back(pts[0]);
  dn.push_back(pts[1]);
  for (int i = 2; i < pts.size(); i++) {
  if (between(dn[dn.size()-2], dn[dn.size()-1], pts[i])) dn.pop_back();
  dn.push_back(pts[i]);
  }
  if (dn.size() >= 3 && between(dn.back(), dn[0], dn[1])) {
  dn[0] = dn.back();
  dn.pop_back();
  }
  pts = dn;
  #endif
}