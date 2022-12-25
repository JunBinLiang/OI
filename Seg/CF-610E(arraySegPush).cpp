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


int n, m, k;
string s;
int id = 0;

const int MAX = 2e5 + 5;
int l[MAX * 4];
int r[MAX  * 4];
int tags[MAX * 4];
int a[MAX * 4][10][10];

void build(int id) {
    if(l[id] == r[id]) {
        return;
    }
    int left = id * 2 + 1, right = id * 2 + 2;
    int mid = l[id] + (r[id] - l[id]) / 2;
    l[left] = l[id];
    r[left] = mid;
    l[right] = mid + 1;
    r[right] = r[id];
    build(left);
    build(right);
}

void pushup(int id) {
    int left = id * 2 + 1, right = id * 2 + 2;
    for(int i = 0; i < k; i++) {
        for(int j = 0; j < k; j++) {
            a[id][i][j] = a[left][i][j] + a[right][i][j];
        }
    }
}

void update(int id, int s, int e, int c) { //row : x   col : y
    if(l[id] == s && r[id] == e) {
        tags[id] = c; //all change to c
        for(int i = 0; i < k; i++) {
            int x = c / k;
            int y = c % k;
            for(int j = 0; j < k; j++) {
                if(i == x && j == y) {
                    //cout << "update   " << c << "   " << s <<" " << e << endl;
                    //cout << x  << "   " << y << endl;
                    a[id][i][j] = (e - s + 1);
                } else {
                    a[id][i][j] = 0;
                }
            }
        }
        return;
    } 
    
    int mid = l[id] + (r[id] - l[id]) / 2;
    int left = id * 2 + 1, right = id * 2 + 2;

    if(tags[id] != -1) {
        update(left, l[left], r[left], tags[id]);
        update(right, l[right], r[right], tags[id]);
        tags[id] = -1;
    }

    if(e <= mid) {
        update(left, s, e, c);
    } else if(s >= mid + 1) {
        update(right, s, e, c);
    } else {
        update(left, s, mid, c);
        update(right, mid + 1, e, c);
    }
    pushup(id);
}

int query(int id, int x, int y, int s, int e) {
    if(l[id] == s && r[id] == e){
        return a[id][x][y];
    }
    int mid = l[id] + (r[id] - l[id]) / 2;
    int left = id * 2 + 1, right = id * 2 + 2;
    if(tags[id] != -1) {
        update(left, l[left], r[left], tags[id]);
        update(right, l[right], r[right], tags[id]);
        tags[id] = -1;
    }
    if(e <= mid){
        return query(left, x, y, s, e);
    } else if(s >= mid + 1) {
        return query(right, x, y, s, e);
    } else {
        return query(left, x, y, s, mid) + query(right, x, y, mid + 1, e);
    }
}

void solve() {
    scanf("%d%d%d", &n, &m, &k);  
    cin >> s;
    memset(l, -1, sizeof l);
    memset(r, -1, sizeof r);
    memset(a, 0, sizeof a);
    memset(tags, -1, sizeof tags);

    l[0] = 0, r[0] = n - 1;
    build(0);
    
    for(int i = 1; i < n; i++) {
        int x = s[i - 1] - 'a';
        int y = s[i] - 'a';
        update(0, i - 1, i - 1, x * k + y);
    }
    
    
    /*cout << endl << endl;
    cout <<"query  " <<  query(0, 0, 1, 0, 0) << endl;
    cout <<"query  " <<  query(0, 1, 0, 1, 1) << endl;
    cout <<"query  " <<  query(0, 0, 2, 2, 2) << endl;
    cout <<"query  " <<  query(0, 2, 0, 3, 3) << endl;
    cout << endl;*/

    
    for(int i = 0; i < m; i++) {
        int ty;
        scanf("%d", &ty);
        if(ty == 1) {
            int l, r; char c;
            cin >> l >> r >> c;
            int d = c - 'a';
            l--; r--;
            
            if(l <= r - 1) {
                update(0, l, r - 1, d * k + d);
            }
            
            if(l > 0) {
                int pre = -1;
                for(int u = 0; u < k && pre == -1; u++) {
                    for(int v = 0; v < k; v++) {
                        if(query(0, u, v, l - 1, l - 1) > 0) {
                            pre = u;
                            break;
                        }
                    }
                }
                //cout <<"pre1  "  << pre << "  " << d << endl;
                update(0, l - 1, l - 1, pre * k + d);
            }
            
            if(r != n - 1) {
                int nxt = -1;
                for(int u = 0; u < k && nxt == -1; u++) {
                    for(int v = 0; v < k; v++) {
                        if(query(0, u, v, r, r) > 0) {
                            nxt = v;
                            break;
                        }
                    }
                }
                //cout <<"nxt1  "  << d << "  " << nxt << endl;
                update(0, r, r, d * k + nxt);
            }
        } else {
            string t;
            cin >> t;
            int res = 0;
            for(int u = 0; u < t.size(); u++) {
                int d1 = t[u] - 'a';
                for(int v = u; v >= 0; v--) {
                    int d2 = t[v] - 'a';
                    res += a[0][d1][d2];
                }
            }
            printf("%d\n", res + 1);
        }
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

