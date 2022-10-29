#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#include <list>

   
using namespace std;  

using ll = long long;
#define pb push_back
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define RFOR(i, a, b) for (int i = a; i >= b; i--)
#define f first
#define se second
#define W while
#define um unordered_map
#define us unordered_set
#define be begin
#define en end

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const unordered_map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}


ll a, b, c, d;
void out(ll x, ll y) {
    cout << x << " " << y << endl;
}
//6 : 10 - 6 : 40
//2e9 : around 1600 divisors 
vector<int> divisor1;
vector<int> divisor2;
void solve() {
    scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
    
    //a <= x <= c
    //b <= y <= d
    //(x * y) / (a * b)
    ll t = a * b;

    divisor1.clear();
    divisor2.clear();
    
    for(int i = 1; i * i <= a; i++) {
        if(a % i == 0) {
            int j = a / i;
            divisor1.pb(i);
            if(i != j) {
                divisor1.pb(j);
            }
        }
    }
    
    for(int i = 1; i * i <= b; i++) {
        if(b % i == 0) {
            int j = b / i;
            divisor2.pb(i);
            if(i != j) {
                divisor2.pb(j);
            }
        }
    }
    
    vector<ll> divisor3;
    for(ll i : divisor1) {
        for(ll j : divisor2) {
            divisor3.pb(i * j);
        }
    }
    
    for(ll dd : divisor3) {
        ll x = dd;
        ll y = t / x;
        if(x <= a) {
            x *= (c / x);
        }
        if(y <= b) {
            y *= (d / y);            
        }
        if(x <= c && y <= d && x > a && y > b) {
            out(x, y);
            return;
        }
    }
    out(-1, -1);

} 

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}

