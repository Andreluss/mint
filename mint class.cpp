//Author: Andrzej Jabłoński
//This is a copy of an old project
//the mint class can be used like a normal int
//just set the mint::mod 
//and write long, clean expressions without worrying about overflows!
#include "bits/stdc++.h"
using namespace std;
using LL = long long;
#define SIZE(x) (int)(x).size()
#define FOR(i, b, e) for(auto i = (b); i <= (e); i++)
#define DFOR(i, b, e) for(auto i = (b); i >= (e); i--)
#define REP(cnt) FOR(_iter, 0, (cnt-1))
#define P2(x) (1LL<<(x))
#define st first
#define nd second
#define mt make_tuple
#define SONIC_SPEED() ios::sync_with_stdio(0); cin.tie(0);
#define ALL(x) (x).begin(), (x).end()

constexpr LL INF = LLONG_MAX / 4;//max 4 razy w sumie
constexpr int iINF = INT_MAX / 2 - 1;

#define DEBUG 0
#if DEBUG
#include <ultimate_power.h>
#else 
#define echo(...)
//#undef assert
//#define assert(...)
#endif
#define debug if(DEBUG)

/* --------------------------------- MODULO --------------------------------- */
struct mint
{
    static int Mod;
    int x;

    int _modulize(int x) const { x %= Mod; if (x < 0) x += Mod; return x; }
    mint(int x = 0) : x(_modulize(x)) {}
    mint(LL x) : x(_modulize(int(x% Mod))) {}
    operator int& () { return x; }

    mint& operator+= (const mint& rhs) { x += rhs.x; if (x >= Mod) x -= Mod; return *this; } //damn that x > MOD was a huge bug
    mint& operator+= (int y) { return *this += mint(y); }
    mint& operator+= (LL y) { return *this += mint(y); }
    mint operator+ (const mint& rhs) const { return mint(*this) += rhs; }
    mint operator+ (int y) const { return *this + mint(y); }
    mint operator+ (LL y) const { return *this + mint(y); }
    friend mint operator+ (int x, const mint& rhs) { return mint(x) + rhs; }
    friend mint operator+ (LL x, const mint& rhs) { return mint(x) + rhs; }

    mint operator- () const { return mint(x == 0 ? 0 : Mod - x); }
    mint& operator-= (const mint& rhs) { return *this += -rhs; }
    mint& operator-= (int y) { return *this -= mint(y); }
    mint& operator-= (LL y) { return *this -= mint(y); }
    mint operator- (const mint& rhs) const { return mint(*this) -= rhs; }
    mint operator- (int y) const { return *this - mint(y); }
    mint operator- (LL y) const { return *this - mint(y); }
    friend mint operator- (int x, const mint& rhs) { return mint(x) - rhs; }
    friend mint operator- (LL x, const mint& rhs) { return mint(x) - rhs; }

    mint& operator*= (const mint& rhs) { x = int((LL)x * rhs.x % Mod); return *this; }
    mint& operator*= (int y) { return *this *= mint(y); }
    mint& operator*= (LL y) { return *this *= mint(y); }
    mint operator* (const mint& rhs) const { return mint(*this) *= rhs; }
    mint operator* (int y) const { return *this * mint(y); }
    mint operator* (LL y) const { return *this * mint(y); }
    friend mint operator* (int x, const mint& rhs) { return mint(x) * rhs; }
    friend mint operator* (LL x, const mint& rhs) { return mint(x) * rhs; }

    mint pow(int e) const {
        mint res = 1;
        for (mint p = *this; e > 0; p *= p, e /= 2)
            if (e % 2)
                res *= p;
        return res;
    }
    mint inv() const { return pow(Mod - 2); }

    mint& operator/= (const mint& rhs) { x *= rhs.inv();  return *this; }
    mint& operator/= (int y) { return *this /= mint(y); }
    mint& operator/= (LL y) { return *this /= mint(y); }
    mint operator/ (const mint& rhs) const { return mint(*this) /= rhs; }
    mint operator/ (int y) const { return *this / mint(y); }
    mint operator/ (LL y) const { return *this / mint(y); }
    friend mint operator/ (int x, const mint& rhs) { return mint(x) / rhs; }
    friend mint operator/ (LL x, const mint& rhs) { return mint(x) / rhs; }
    friend std::ostream& operator<<(std::ostream& stream, const mint& mod_x) { return stream << mod_x.x; }
};
int mint::Mod = 1'000'000'007;
/* ------------------------------------------------------------------------ */

struct Tree
{
    int LC = 4;
    vector<int> tree;
    Tree(int n)
    {
        while (LC < n) LC *= 2;
        tree.resize(2 * LC, 0);
    }
    int less(int x)
    {
        x += LC;
        int res = 0;
        while (x > 1)
        {
            if (x % 2 == 1)
                res += tree[x - 1];
            x /= 2;
        }
        return res;
    }
    void insert(int x)
    {
        tree[x += LC] = 1;
        while (x /= 2)
            tree[x] = tree[2 * x] + tree[2 * x + 1];
    }
};

int main()
{
    //Some example competetive programming task...
    SONIC_SPEED();

    int n; cin >> n;
    vector<int> p(n);
    for (auto& pi : p) cin >> pi;

    auto g = [](int t)->mint {return (t + 1) / 2; };
    vector<mint> f(n + 1, 0);
    FOR(i, 1, n)
        f[i] = i * f[i - 1] + g(i) * (i - 1);

    Tree T(n + 1);
    mint res = 0;
    DFOR(i, n - 1, 0)
    {
        T.insert(p[i]);
        int s = T.less(p[i]);

        int t = n - i;
        res += s * (g(t) + f[t - 1]);
    }

    cout << res << "\n";
}
