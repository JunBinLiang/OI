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
 
 
using namespace std;  
using ll = long long;
#define pb push_back
 
//ifstream fcin("test/input.txt");
//ofstream fcout("test/output.txt");

const int N = 3e5 + 5;
const int M = N * 4;

int n;
int base = 10, mod = 1e9 + 7;
int p[N];


int h[M], hh[M], L[M], R[M];

void build(int id) {
  int& l = L[id]; int& r = R[id];
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  
  L[left] = l, R[left] = mid, h[left] = 0;
  L[right] = mid + 1, R[right] = r, h[right] = 0;
  build(left);
  build(right);
}

void update(int id, int s, int e, int v1, int v2) { 
  int& l = L[id]; int& r = R[id];
  if(l == s && r == e) {
    h[id] = v1;
    hh[id] = v2;
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;

  if(e <= mid) {
    update(left, s, e, v1, v2);
  } else if(s >= mid + 1) {
    update(right, s, e, v1, v2);
  } else {
    update(left, s, mid, v1, v2);
    update(right, mid + 1, e, v1, v2);
  }
  h[id] = (h[left] + h[right]) % mod;
  hh[id] = (hh[left] + hh[right]) % mod;
}

int query(int id, int s, int e, int ty) {
  int& l = L[id]; int& r = R[id];
  if(l == s && r == e){
    if(ty == 0) return h[id];
    else return hh[id];
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
      return query(left, s, e, ty);
  } else if(s >= mid + 1) {
      return query(right, s, e, ty);
  } else {
    return (query(left, s, mid, ty) + query(right, mid + 1, e, ty)) % mod;
  }
}


char cc[1<<21],*uu=cc,*vv=cc;
#define gc (uu==vv&&(vv=(uu=cc)+fread(cc,1,1<<21,stdin),uu==vv)?EOF:*uu++)
inline int read(){
	char ch=gc;int X=0;bool fl=0;
	while(ch<'0'||ch>'9'){if(ch=='-')fl=1;ch=gc;}
	while(ch>='0'&&ch<='9'){X=(X<<1)+(X<<3)+ch-'0';ch=gc;}
	if(fl)return ~(X-1);
	return X;
}

ll getHash1(int l, int r) {
    ll h1 = query(0, 0, r, 0);
    ll h2 = query(0, 0, l - 1, 0);
    
    h1 = (h1 - h2 + mod) % mod;
    return h1;
}

ll getHash2(int l, int r) {
    ll h1 = query(0, l, n + 1, 1);
    ll h2 = query(0, r + 1, n + 1, 1);
    h1 = (h1 - h2 + mod) % mod;
    return h1;
}
 
void solve() {
    p[0] = 1;
    for(int i = 1; i < N; i++) {
        p[i] = (int)(((p[i - 1] + 0ll) * base) % mod);
        p[i] %= mod;
    }
    
    scanf("%d", &n);

    L[0] = 0; R[0] = n + 1;
    h[0] = 0;
    build(0);
    

    for(int i = 0; i < n; i++) {
        int t = read();

        int k = min(t - 1, n - t);
        //hash[t - k : t - 1]  == hash[t + 1, t + k]
        //do rolling hash over segment tree
        ll h1 = getHash1(t - k, t);
        ll h3 = getHash2(t, t + k);
        
        int cnt1 = t - k;
        int cnt2 = (n + 1) - (t + k);
        
        //cout <<"get  " <<  t << " "  << k << endl;
        //cout << h1 << "  " << h3 << "    |" << cnt1 << " " << cnt2 << endl;
        
        if(cnt1 > cnt2) {
            h3 = h3 * p[cnt1 - cnt2];
            h3 %= mod;
        } else if(cnt2 > cnt1) {
            h1 = h1 * p[cnt2 - cnt1];
            h1 %= mod;
        }
        

        if(h1 != h3 && t != 1) {
            printf("YES\n");  
            return;
        }

        int v1 = p[t], v2 = p[n - t + 1];
        update(0, t, t, v1, v2); //update a single cell
        //cout << "update   " << v1 <<"  " << v2 << endl << endl;
    }

    printf("NO\n");  
}

int main() {
	// your code goes here
	int t = 1;
	//cin >> t;
	while(t--) {
	    solve();
	}
	return 0;
}
