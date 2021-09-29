/*#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("vpt")
#pragma GCC optimize("rename-registers")
#pragma GCC optimize("move-loop-invariants")
#pragma GCC optimize("function-sections")
#pragma GCC optimize("branch-target-load-optimize")
#pragma GCC optimize("branch-target-load-optimize2")
#pragma GCC optimize("btr-bb-exclusive")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize ("O3")*/

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <iomanip>
#include <random>

#define len(a) (int)a.size()
#define all(a) a.begin(), a.end()
#define forn(n, i) for (int i = 0; i < n; ++i)
#define fornrev(n, i) for (int i = n - 1; i > -1; --i)
#define ll long long
#define ld long double
#define accuracy(a) fixed << setprecision(a)

const int INF = (int)1e9;
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

void solve()
{

}

signed main()
{
#ifndef LOCAL
    fast_io();
#else
    file_in("input.txt");
    file_out("output.txt");
    clock_t start = clock();
#endif

    solve();

#ifdef LOCAL
    cerr << "TIME = " << accuracy(3) << diff_clock(start, clock()) << '\n';
#endif
    return 0;
}