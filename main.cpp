#ifndef LOCAL
#pragma GCC optimize("Ofast")
#pragma GCC optimize ("O3")
#endif

#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <iomanip>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <numeric>
#include <bitset>
#include <list>
#include <forward_list>
#include <tuple>
#include <string>
#include <complex>
#include <random>
#include <array>
#include <sstream>

#define len(a) (int)a.size()
#define all(a) a.begin(), a.end()
#define forn(n, i) for (int i = 0; i < n; ++i)
#define fornrev(n, i) for (int i = n - 1; i > -1; --i)
#define accuracy(a) fixed << setprecision(a)

typedef long long ll;
typedef long double ld;

const int INF = (int)2e9;
const ll LINF = (ll)1e18;
const double EPS = 0.000000000000001;
const double PI = acos(-1.0);
const int MOD = 1e9 + 7;

using namespace std;

void fast_io()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

void file_in(const string& filename)
{
    freopen(filename.c_str(), "r", stdin);
}

void file_out(const string& filename)
{
    freopen(filename.c_str(), "w", stdout);
}

double diff_clock(clock_t clock1, clock_t clock2)
{
    return (double)(clock2 - clock1) * 1000 / CLOCKS_PER_SEC;
}

void sleep(int milliseconds)
{
    clock_t start = clock();
    for (clock_t end = clock(); diff_clock(start, end) < milliseconds; end = clock()) {}
}

int randint(int a, int b)
{
    static random_device rd;
    static mt19937 rnd(rd());
    return (int)(rnd() % (b - a + 1) + a);
}

ll randint64(ll a, ll b)
{
    static random_device rd;
    static mt19937_64 rnd(rd());
    return (ll)(rnd() % (b - a + 1) + a);
}

template<typename T>
void uniquize(vector<T>& vec)
{
    vec.resize(distance(vec.begin(), unique(vec.begin(), vec.end())));
}

#ifdef LOCAL
#include "Code/Utilities/Debug output.cpp"
#define debug(...) cerr << "debug(" << #__VA_ARGS__ << "): ", debug_out(cerr, __VA_ARGS__)
#else
#define debug(...)
#endif

inline string input_filename();

void run();

signed main()
{
#ifdef LOCAL
    file_in("input.txt");
    file_out("output.txt");
    clock_t start = clock();
#else
    fast_io();
    if (!input_filename().empty())
    {
        file_in(input_filename() + ".in");
        file_out(input_filename() + ".out");
    }
#endif

    run();

#ifdef LOCAL
    cerr << "TIME = " << accuracy(3) << diff_clock(start, clock()) << endl;
#endif
    return 0;
}

inline string input_filename()
{
    return "";
}

void run()
{
    debug(5);
}