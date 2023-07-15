#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <deque>
#include <fstream>
 
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define vec vector
#define var auto
using namespace std;
 
 
const int N = 1e6 + 10;
int n, m, res = 0;

int cal(vector<string>& a) {
    int res = 0;
    vector<int> col;
    int L[N], R[N];
    int n = a.size(), m = a[0].size();

    int rowMax = 0, colMax = 0;
    for(int i = 0; i < n; i++) {
        int len = 0;
        for(int j = 0; j < m; j++) {
            if(a[i][j] == '#') {
                if(len != 0) {
                    rowMax = max(rowMax, len);
                }
                len = 0;
                continue;
            }
            len++;
            res = max(res, len + rowMax);
        }
        if(len != 0) {
            rowMax = max(rowMax, len);
        }
    }
    
    //cout << res <<endl;

    //column
    vector<vector<int>> coldp1(n, vector<int>(m, 0));
    vector<vector<int>> coldp2(n, vector<int>(m, 0));
    for(int j = 0; j < m; j++) {
        int len = 0, curMax = 0;
        for(int i = 0; i < n; i++) {
            if(a[i][j] == '#') {
                colMax = max(colMax, len);
                curMax = max(curMax, len);
                len = 0;
                coldp1[i][j] = len;
                if(i - 1 >= 0) coldp1[i][j] = max(coldp1[i][j], coldp1[i - 1][j]);
                continue;
            }
            len++;
            coldp1[i][j] = len;
            if(i - 1 >= 0) coldp1[i][j] = max(coldp1[i][j], coldp1[i - 1][j]);
            res = max(res, len + colMax);
        }
        if(len != 0) {
            colMax = max(colMax, len);
            curMax = max(curMax, len);
        }
        col.push_back(curMax);
    }
    
    //for(int x  :col)cout << x << " ";
    //cout << endl;

    for(int j = 0; j < m; j++) {
        int len = 0;
        for(int i = n - 1; i >= 0; i--) {
            if(a[i][j] == '#') {
                len = 0;
                coldp2[i][j] = len;
                if(i + 1 < n) coldp2[i][j] = max(coldp2[i][j], coldp2[i + 1][j]);
                continue;
            }
            len++;
            coldp2[i][j] = len;
            if(i + 1 < n) coldp2[i][j] = max(coldp2[i][j], coldp2[i + 1][j]);
        }
    }


    //left right
    for(int i = 0; i < col.size(); i++) {
        L[i] = col[i];
        if(i) L[i] = max(L[i], L[i - 1]);
    }
    for(int i = col.size() - 1; i >= 0; i--) {
        R[i] = col[i];
        if(i + 1 < m) {
            R[i] = max(R[i], R[i + 1]);
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(a[i][j] == '#') continue;
            int l = j, r = j;
            int crossMax = 0;
            while(r < m && a[i][r] == '.') {
                if(i - 1 >= 0) crossMax = max(crossMax, coldp1[i - 1][r]);
                if(i + 1 < n) crossMax = max(crossMax, coldp2[i + 1][r]);
                r++;
            }
            r--;
            int len = r - l  + 1;
            if(l - 1 >= 0) {
                res = max(res, len + L[l - 1]);
            }
            if(r + 1 < m) {
                res = max(res, len + R[r + 1]);
            }
            res = max(res, len + crossMax);
            j = r;
        }
    }
    return res;
}

void solve() {
    cin >> n >> m;
    vector<string> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    //rotate the matrix
    vector<string> rot;
    for(int j = 0; j < m; j++) {
        string s = "";
        for(int i = 0; i < n; i++) {
            s += a[i][j];
        }
        rot.push_back(s);
    }
    
    int x = cal(a);
    int y = cal(rot);
    cout << max(x, y) << endl;
}

int main()
{
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
