// #pragma GCC target("sse,sse2,sse3,ssse3,sse4")
#pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

// hloya template v26

// ░░░░░░░▄▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▄░░░░░░
// ░░░░░░█░░▄▀▀▀▀▀▀▀▀▀▀▀▀▀▄░░█░░░░░
// ░░░░░░█░█░▀░░░░░▀░░▀░░░░█░█░░░░░
// ░░░░░░█░█░░░░░░░░▄▀▀▄░▀░█░█▄▀▀▄░
// █▀▀█▄░█░█░░▀░░░░░█░░░▀▄▄█▄▀░░░█░
// ▀▄▄░▀██░█▄░▀░░░▄▄▀░░░░░░░░░░░░▀▄
// ░░▀█▄▄█░█░░░░▄░░█░░░▄█░░░▄░▄█░░█
// ░░░░░▀█░▀▄▀░░░░░█░██░▄░░▄░░▄░███
// ░░░░░▄█▄░░▀▀▀▀▀▀▀▀▄░░▀▀▀▀▀▀▀░▄▀░
// ░░░░█░░▄█▀█▀▀█▀▀▀▀▀▀█▀▀█▀█▀▀█░░░
// ░░░░▀▀▀▀░░▀▀▀░░░░░░░░▀▀▀░░▀▀░░░░

#include <bits/stdc++.h>
using namespace std;

bool dbg = 0;

clock_t start_time = clock();
#define current_time fixed<<setprecision(6)<<(ld)(clock()-start_time)/CLOCKS_PER_SEC

#define f first
#define s second
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define eb emplace_back
#define all(v) (v).begin(), (v).end()
#define sz(v) ((int)(v).size())
#define sqr(x) ((x) * (x))


#define ull unsigned long long
#define ll long long
#define ld long double
#define pii pair<int,int>
#define umap unordered_map<int, int>

#define files1 freopen("input.txt","r",stdin)
#define files2 freopen("output.txt","w",stdout)
#define files files1;files2
#define fast_io ios_base::sync_with_stdio(0);cin.tie(0)

#define endl '\n'
#define ln(i,n) " \n"[(i) == (n) - 1]

void bad(string mes = "Impossible"){cout << mes;exit(0);}
void bad(int mes){cout << mes;exit(0);}

template<typename T>
string bin(T x, int st = 2){
    string ans = "";
    while (x > 0){
        ans += char('0' + x % st);
        x /= st;
    }
    reverse(ans.begin(), ans.end());
    return ans.empty() ? "0" : ans;
}

mt19937_64 mt_rand(
    chrono::system_clock::now().time_since_epoch().count()
);

template<typename T1, typename T2> inline bool upmax(T1& a, T2 b) { return (a < b ? (a = b, true) : false); }
template<typename T1, typename T2> inline bool upmin(T1& a, T2 b) { return (b < a ? (a = b, true) : false); }

// inline int popcount(int x){
//     int count = 0;
//     __asm__ volatile("POPCNT %1, %0;":"=r"(count):"r"(x):);
//     return count;
// }

template<typename T>
T input(){
    T ans = 0, m = 1;
    char c = ' ';

    while (!((c >= '0' && c <= '9') || c == '-')) {
        c = getchar();
    }

    if (c == '-')
        m = -1, c = getchar();
    while (c >= '0' && c <= '9'){
        ans = ans * 10 + (c - '0'), c = getchar();
    }
    return ans * m;
}

ll gcd (ll a, ll b) { while (b) { a %= b; swap (a, b); } return a; }

template<typename T> void read(T& a) { a = input<T>(); }
template<typename T> void read(T& a, T& b) { read(a), read(b); }
template<typename T> void read(T& a, T& b, T& c) { read(a, b), read(c); }
template<typename T> void read(T& a, T& b, T& c, T& d) { read(a, b), read(c, d); }

int inf = 1e9 + 20;
const short short_inf = 3e4 + 20;
const long double eps = 1e-12;
const int maxn = (int)5e5 + 12, base = 1e9 + 7;
const ll llinf = 2e18 + 5;

template<typename T>
T binpow(T n, T s)
{
    if (s <= 0)
        return 1LL;
    if (s % 2 == 0){
        T b = binpow(n, s / 2);
        return ( 1LL * b * b ) % base;
    } else {
        return (1LL* binpow(n, s - 1) * n) % base;
    }
}

vector<int> gensmall() {
    int n = rand() % 50 + 1;
    vector<int> a;
    for (int i = 0; i < n; i++) {
        int x = rand() % 51 - 25;
        a.pb(x);
    }
    return a;
}

ll isqrt(ll x) {
    ll y = sqrt(x);
    while (y * y < x) y++;
    while (y * y > x) y--;
    return y;
}

bool completesquate(ll x) {
    if (x < 0) return 0;
    ll y = isqrt(x);
    if (y * y == x)
        return true;
    return false;
}

long long average(const vector<int>& a) {
    long long sum = 0;
    int n = a.size();
    for (int i = 0; i < a.size(); i++) {
        sum += a[i];
    }
    return sum / n;
}

long long dispertion(const vector<int>& a) {
    ll avg = average(a);
    long long sum = 0;
    int n = a.size();
    for (int i = 0; i < a.size(); i++) {
        sum += sqr(avg - a[i]);
    }
    return sum / n;
}

ll check(const vector<int>& a, const vector<int>& b) {
    return average(a) == average(b) && dispertion(a) == dispertion(b);
}

bool solve(const vector<int>& a) {
    int n = a.size();

    long long sum = 0, sqs = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
        sqs += a[i] * (ll)a[i];
    }

    if (sum % n || sqs % n)
        return 0;

    for (int i = 0; i < n; i++) {
        ll d = sum / n + a[i]; //k

        ll e = sqs / n + a[i] * (ll)a[i]; //c1

        ld mda = sqrt(2 * e - d * d);

        if (completesquate(2 * e - d * d)) {
            ll s = isqrt(2 * e - d * d);
            if ((d + s) % 2 == 0) {
                ll b = (d + s) / 2, c = (d - s) / 2;
                vector<int> result = a;
                result.erase(result.begin() + i);
                result.pb(b);
                result.pb(c);
                assert(check(result, a));

                cout << "Possible\n";
                cout << i + 1 << ' ' << b << ' ' << c << "\n";
                return true;
            }
        }
    }
    return false;
}

long double daverage(const vector<int>& a) {
    long double sum = 0;
    int n = a.size();
    for (int i = 0; i < a.size(); i++) {
        sum += a[i];
    }
    return sum / n;
}

long double ddispertion(const vector<int>& a) {
    long double avg = daverage(a);
    long double sum = 0;
    int n = a.size();
    for (int i = 0; i < a.size(); i++) {
        sum += sqr(avg - a[i]);
    }
    return sum / n;
}

bool eq(ld a, ld b) {
    return abs(a - b) < eps;
}

bool dcheck(const vector<int>& a, const vector<int>& b) {
    return eq(daverage(a), daverage(b)) && eq(ddispertion(a), ddispertion(b));
}

bool brute(const vector<int>& a) {
    for (int i = 0; i < a.size(); i++) {
        for (int b = -100; b <= 100; b++)
            for (int c = -100; c <= 100; c++) {
                vector<int> result = a;
                result.erase(result.begin() + i);
                result.pb(b);
                result.pb(c);
                if (dcheck(result, a)) {
                    cout << a[i] << ' ' << b << ' ' << c << endl;
                    return true;
                }
            }
    }
    return false;
}

int main() {
    // files1;
    fast_io;

    // vector<int> tmp = {7,4,3,-2,2,-3,-9,-10};
    // cout << daverage(tmp) << ' ' << ddispertion(tmp) << endl;
    // vector<int> tmp2 = {7,4,3,-2,2,-3,-9,-10,-1};
    // cout << daverage(tmp2) << ' ' << ddispertion(tmp2) << endl;
    // cout << solve(tmp) << ' ' << brute(tmp) << endl;
    // return 0;

    bool stress = 0;
    if (stress) {
        int cok = 0, cwg = 0;
        for (int iter = 0; iter < 1000; iter++) {
            auto e = gensmall();
            bool rmy;
            if ((rmy = solve(e)) != brute(e)) {
                cout << "vector<int> tmp = {";
                for (auto i : e)
                    cout << i << ',';
                cout << "};";
                cout << endl;
                exit(228);
            }
            if (rmy)
                cok++;
            else
                cwg++;
            if (iter % 10 == 0) {
                cout << iter << " iters passed\n";
                cout.flush();
            }
        }
        cout << cok << ' ' << cwg << endl;
    } else {
        int n;
        cin >> n;

        vector<int> a(n);

        for (int i = 0; i < n; i++)
            cin >> a[i];

        bool f = solve(a);
        if (!f)
            cout << "Impossible";
    }
    return 0;
}
