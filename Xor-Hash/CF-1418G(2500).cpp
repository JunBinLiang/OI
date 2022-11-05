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

unsigned long long seed=131;
unsigned long long rands(){return seed=(seed<<15)+(seed<<8)+(seed>>3);}

void debug() {
    cout << "________________" << endl;
}


const int N = 5e5 + 10, M = 61;
int a[N];
vector<int> pos[N];

typedef array<int, M> num;
num operator ^(const num &a, const num &b){
    num c;
    for(int i = 0; i < M; i++) {
        c[i] = a[i] + b[i];
        if (c[i] >= 3) c[i] -= 3;
    }
    return c;
}

void solve() {
    ll res = 0;
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    vector<num> rnd(n + 1);
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j < M; j++) {
            rnd[i][j] = rands() % 3;
        }
    }


    vector<num> p(1); //prefix
    map<num, int> f;
    f[p.back()] ++;
    int j = 0;
    for(int i = 1; i <= n; i++) {
        p.push_back(p.back() ^ rnd[a[i]]);
        pos[a[i]].push_back(i);
        
        if(pos[a[i]].size() >= 4) {
            int sz = pos[a[i]].size();
            while(j < pos[a[i]][sz - 4]) {
                f[p[j]] --;
                j++;
            }
        }
        
        res += f[p.back()];
        f[p.back()] += 1;
    }
    cout << res << endl;
} 

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}

