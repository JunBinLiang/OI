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
#include<fstream>
#include <bitset>

using namespace std;  
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define P pair
#define V vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define FFOR(i, a, b) for (int i = a; i <= b; ++i)

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}




const int N = 2e6 + 10;
struct PalindromeTree {
    char s[N];
    int len[N], fail[N], cnt1[N], cnt2[N];
    vector<pair<int, int>> ch[N];
    int tot = 0, last = 0;    
    
    void init() {
        memset(cnt1, 0, sizeof cnt1);
        memset(cnt2, 0, sizeof cnt2);
        memset(len, 0, sizeof len);
        memset(fail, 0, sizeof fail);
        s[0] = -1;
        len[0] = 0; //初始化even root 
        len[1] = -1;//初始化odd root 
        fail[0] = 1;
        fail[1] = 1;
        tot = 1;
        last = 0;
        for(int i = 0; i < N; i++) ch[i].clear();
    }
    
    int getfail(int x, int i) { //寻找fail node
        while(i - len[x] - 1 < 0 || s[i - len[x] - 1] != s[i]) x = fail[x];
        return x;
    }
    
    int newnode(int x) { //简历长度为x 的新node
        tot++;
        len[tot] = x;
        return tot;
    }
    
    int get(int failnode, int index) {
        for(int i = 0; i < ch[failnode].size(); i++) {
            if(ch[failnode][i].first == index) {
                return ch[failnode][i].second;
            }
        }
        return 0;
    }

    
    void add(int i) {
        s[i] -= 'a';
        int failnode = getfail(last, i);
        if(get(failnode, s[i]) == 0) { //需要新建node
            int node = newnode(len[failnode] + 2); //前后都加上新字符，所以新回文串长度要加2
            fail[node] = get(getfail(fail[failnode], i), s[i]); //因为fail指向的是原串的严格后缀，所以要从failnode的fail开始找起 
            ch[failnode].push_back({s[i], node});
            cnt2[node] = 1 + cnt2[fail[node]];
        }
        last = get(failnode, s[i]);
        cnt1[last]++;
    }
} pt1;



int MOD = 51123987;
void solve() {
    int n;
    scanf("%d", &n);
    scanf("%s", pt1.s + 1);
    
    pt1.init();
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        pt1.add(i);
        a[i] = pt1.cnt2[pt1.last];
        a[i] %= MOD;
    }
    
    ll count = 0;
    for(int i = pt1.tot; i >= 2; i--) {
        count += pt1.cnt1[i];
        pt1.cnt1[pt1.fail[i]] += pt1.cnt1[i];
    }
    
    count %= MOD;
    ll sum = (count) * (count - 1) / 2;
    sum %= MOD;
    
    pt1.init();
    int l = 1, r = n;
    while(l < r) { //reverse the string
        swap(pt1.s[l], pt1.s[r]);
        l++; r--;
    }

    vector<int> b(n + 1);
    for(int i = 1; i <= n; i++) {
        pt1.add(i);
        b[n - i + 1] = pt1.cnt2[pt1.last];
    }
    
    for(int i = n - 1; i >= 1; i--) {
        b[i] += b[i + 1];
        b[i] %= MOD;
    }
    
    for(int i = 1; i < n; i++) {
        sum -= (((a[i] + 0ll) * b[i + 1]) % MOD);
        if(sum < 0) sum += MOD;
    }
    cout << sum << endl;
}

int main()
{
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
