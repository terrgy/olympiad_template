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


#include <iostream>
#include <cmath>
#include <ctime>

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
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

void file_in(const string& filename)
{
    freopen(filename.c_str(), "r", stdin);
}

void file_out(const string& filename)
{
    freopen(filename.c_str(), "w", stdout);
}

double diffclock(clock_t clock1, clock_t clock2)
{
    double diffticks = clock2 - clock1;
    return diffticks / ((double)CLOCKS_PER_SEC / 1000);
}

void sleep(int milliseconds)
{
    clock_t start = clock();
    for (clock_t end = clock(); diffclock(start, end) < milliseconds; end = clock()) {}
}

signed main()
{
#ifndef LOCAL
    fast_io();
#endif
#ifdef LOCAL
    clock_t start = clock();
#endif



#ifdef LOCAL
    cerr << "TIME = " << (clock() - start) / ((double)CLOCKS_PER_SEC / 1000) << '\n';
#endif

    return 0;
}
