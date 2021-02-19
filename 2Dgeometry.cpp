#include <bits/stdc++.h>
using namespace std;

struct Vector
{
    double x, y;
    Vector(double x = 0, double y = 0) : x(x), y(y) { }

    double length() const
    {
        return sqrt(x * x + y * y);
    }

    Vector normalize() const
    {
        return Vector(-y / length(), x / length());
    }

    double angle() const
    {
        return atan2(y, x);
    }
};

using Point = Vector;

struct Line
{
    Point pt;
    Vector vec;
    Line(Point pt = 0, Vector vec = 0) : pt(pt), vec(vec) { }
};

struct Segment
{
    Point a, b;
    Vector ab;
    Segment(Point a = 0, Point b = 0) : a(a), b(b)
    {
        ab = b - a;
    }
};

const double EPS = 1e-10;
int dcmp(double x)
{
    return abs(x) < EPS ? 0 : (x < 0 ? -1 : 1);
}

bool operator==(const Point &l, const Point &r)
{
    return abs(l.x - r.x) <= EPS && abs(l.y - r.y) <= EPS;
}

bool operator<(const Point &l, const Point &r)
{
    return l.x < r.x || (l.x == r.x && l.y < r.y);
}

Vector operator-(const Vector &l, const Vector &r)
{
    return Vector(l.x - r.x, l.y - r.y);
}

Vector operator+(const Vector &l, const Vector &r)
{
    return Vector(l.x + r.x, l.y + r.y);
}

Vector operator*(double k, const Vector &vec)
{
    return Vector(k * vec.x, k * vec.y);
}

Vector operator/(const Vector &vec, double k)
{
    return Vector(vec.x / k, vec.y / k);
}

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

double area(const Point &a, const Point &b, const Point &c)
{
    return cross(b - a, c - a);
}

// Make sure !pts.empty()
double area(const vector<Point> &pts)
{
    double ans = 0;
    for (int i = 1; i < pts.size() - 1; ++i)
        ans += cross(pts[i] - pts[0], pts[i + 1] - pts[0]);
    return ans / 2;
}

Vector rotate(const Vector &vec, double a)
{
    return Vector(vec.x * cos(a) - vec.y * sin(a),
                  vec.x * sin(a) + vec.y * cos(a));
}

// Make sure cross(vp, vq) != 0
Point intersect(const Point &p, const Vector &vp, const Point &q, const Vector &vq)
{
    return p + cross(vq, p - q) / cross(vp, vq) * vp;
}

double dist(const Point &p, const Line &line)
{
    return abs(cross(line.vec, p - line.pt)) / line.vec.length();
}

double dist(const Point &p, const Segment &seg)
{
    if (seg.a == seg.b)
        return (p - seg.a).length();
    Vector ap = p - seg.a, bp = p - seg.b;
    if (dot(seg.ab, ap) < -EPS)
        return ap.length();
    else if (dot(seg.ab, bp) > EPS)
        return bp.length();
    return abs(cross(seg.ab, ap)) / seg.ab.length();
}

Point projection(const Point &p, const Line &line)
{
    return line.pt +
        dot(line.vec, p - line.pt) / dot(line.vec, line.vec) * line.vec;
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
