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
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define pb push_back
#define ve vector

//ifstream fcin("test/input.txt");
//ofstream fcout("test/output.txt");

const int N = 2e5 + 10;
const int INF = 1e7;
int a[N];


struct Node {
  int l, r;
  int setTo = 0;
  int ab, ba;
  int mx, mn;
  int ans;
} tr[N * 4];

void pushup(int id) {
    int left = id * 2 + 1, right = id * 2 + 2;
    tr[id].mn = min(tr[left].mn, tr[right].mn);
    tr[id].mx = max(tr[left].mx, tr[right].mx);

    tr[id].ab = max(tr[left].ab, tr[right].ab);
    tr[id].ab = max(tr[id].ab, tr[left].mx - 2 * tr[right].mn);

    tr[id].ba = max(tr[left].ba, tr[right].ba);
    tr[id].ba = max(tr[id].ba, tr[right].mx - tr[left].mn * 2);

    tr[id].ans = max(tr[left].ans, tr[right].ans);
    tr[id].ans = max(tr[id].ans, tr[left].ab + tr[right].mx);
    tr[id].ans = max(tr[id].ans, tr[left].mx + tr[right].ba);
    
    //cout << "pushup  " << tr[id].l << " " << tr[id].r << endl;
    //cout <<  tr[id].mx <<"  " << tr[id].mn << " " << tr[id].ab << " " << tr[id].ba << endl << endl;
}

void build(int id) {
  int l = tr[id].l, r = tr[id].r;
  if(l == r) {
    tr[id].mx = tr[id].mn = a[l];
    tr[id].ab = tr[id].ba = -a[l];
    tr[id].ans = 0;
    return;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  tr[left] = {l, mid, 0, -INF, -INF, -INF, -INF, - INF};
  tr[right] = {mid + 1, r, 0, -INF, -INF, -INF, -INF, -INF};
  build(left);
  build(right);
  pushup(id);
}

void update(int id, int s, int e, int val) { 
  int l = tr[id].l, r = tr[id].r;
  if(l == s && r == e) {
    tr[id].mx += val;
    tr[id].mn += val;
    tr[id].ab -= val;
    tr[id].ba -= val;
    tr[id].setTo += val;
    
    //cout << "update  " << s << " " << e << " | " << tr[id].mx <<"  " << tr[id].mn << " " << tr[id].ab << " " << tr[id].ba << endl;
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;

  if(tr[id].setTo != 0) {
    update(left, tr[left].l, tr[left].r, tr[id].setTo);
    update(right, tr[right].l, tr[right].r, tr[id].setTo);
    tr[id].setTo = 0;
  }

  if(e <= mid) {
    update(left, s, e, val);
  } else if(s >= mid + 1) {
    update(right, s, e, val);
  } else {
    update(left, s, mid, val);
    update(right, mid + 1, e, val);
  }
  pushup(id);
}


void solve() {
    int n, m;
    string s;
    cin >> n >> m >> s;
    n = s.size();

    int o = 0;
    a[0] = 0;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '(') o++;
        else o--;
        a[i + 1] = o;
    }


    tr[0] = {0, n, 0, -INF, -INF, -INF, -INF, - INF};
    build(0);
    
    //cout << endl << endl;
    //cout << "first  " << tr[0].ans << endl;
    printf("%d\n", tr[0].ans);

    for(int i = 0; i < m; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        if(l > r) swap(l, r);
        if(s[l - 1] == s[r - 1]) {
            //do nothing
        } else {
            char c = s[l - 1];
            if(c == '(') {
                update(0, l, r - 1, -2);
            } else {
                update(0, l, r - 1, 2);
            }
        }
        swap(s[l - 1], s[r - 1]);
        //cout << s << endl;
        printf("%d\n", tr[0].ans);
    }
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
