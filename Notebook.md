# ICPC Notebook

Assuming g++ compiler with -std=gnu++17 (Kattis setting)

## C++ Language

### Limits

```C++
-numeric_limits<int>::infinity()  // -∞
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

### Max with multiple elements

```C++
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

- `dijkstra.cpp`
- `scc.cpp`

## Data structures

### Set

Complexity: set log(n), unordered_set O(1)

## Techniques

### Discretization

// UVa221
