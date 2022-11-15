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

unsigned long long seed = 131;
unsigned long long rands() { return seed = (seed << 15) + (seed << 8 ) + (seed >> 3);}

void debug() {
    cout << "________________" << endl;
}

vector<int> p;
const int N = 5e4 + 10;
bool is[N];
void init() {
    memset(is, false, sizeof is);
    for(int i = 2; i < N; i++) {
        if(is[i]) continue;
        p.push_back(i);
        for(int j = i; j < N; j += i) {
            is[j] = true;
        }
    }
}

int cal(int x) {
    int cnt = 0;
    for(int i : p) {
        if(x < i) break;
        while(x % i == 0) x /= i, cnt++;
    }
    if(x != 1) cnt++;
    return cnt;
}

void solve() {
    int a, b, k;
    scanf("%d%d%d", &a, &b, &k);
    int t1 = cal(a), t2 = cal(b);
    int g = __gcd(a, b);
    int t3 = cal(g);
   //cout << g << " " << a << " " << b << endl;
    //cout << t1 << " " << t2 << " " << t3 << endl;
    
    int mx = max(a, b);
    int mn = min(a, b);
    
    
    
    if(k == 1) {
        if(mx % mn == 0 && mx != mn) {
            printf("YES\n");    
        } else {
            printf("NO\n");    
        }
    } else {
        if(k <= t1 + t2) {
            printf("YES\n");    
        } else {
            printf("NO\n");
        }
    }
    
    
} 

int main() {
    int t = 1;
    init();
    cin >> t;
    
    while(t--) {
        solve();
    }
    return 0;
}

