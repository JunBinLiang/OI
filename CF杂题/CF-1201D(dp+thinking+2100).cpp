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

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

const int N = 2e5 + 10;
const ll INF = 100000000000000ll;
ll dp[2];
vector<pair<int, int>> a;
vector<int> b;
int n, m, k, q;

//3: 25  - 4: 16
bool COMP(pair<int, int>& p1, pair<int, int>& p2) {
    if(p1.first == p2.first) {
        return p1.second < p2.second;
    }
    return p1.first < p2.first;
}

int next(int v) {
    int l = 0, r = b.size() - 1;
    int res = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(b[mid] >= v) {
            res = b[mid];
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }  
    return res;
}

int pre(int v) {
    int l = 0, r = b.size() - 1;
    int res = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(b[mid] <= v) {
            res = b[mid];
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }    
    return res;
}


void solve() {
    cin >> n >> m >> k >> q;
    for(int i = 0; i < k; i++) {
        int r, c;
        scanf("%d%d", &r, &c);
        a.push_back({r, c});
    }
    a.push_back({1, 1});

    for(int i = 0; i < q; i++) {
        int c;
        scanf("%d", &c);
        b.push_back(c);
    }
    
    sort(b.begin(), b.end());
    sort(a.begin(), a.end(), COMP);
    
    
    int start = 0;
    vector<int> lastRow;
    if(a[0].first == 1) {
        for(int i = 0; i < a.size(); i++) {
            if(a[i].first == 1) {
                start = i;
                lastRow.push_back(a[i].second);
            }
        }
        dp[0] = (a[start].second - 1) * 2;
        dp[1] = a[start].second - 1;
    }
    
    //cout << dp[0] << " " << dp[1] << endl << endl;
    
    for(int i = start + 1; i < a.size(); i++) {
        int j = i;
        vector<int> row;
        while(j < a.size() && a[j].first == a[i].first) {
            row.push_back(a[j].second);
            j++;
        }
        
        int c1 = row[0], c2 = row[row.size() - 1];
        int p1 = pre(c1);
        int p2 = next(c1 + 1);
        int p3 = next(c2);
        
        ll f[2]; 
        f[0] = f[1] = INF;
        //f[0] : end at c1
        //f[1] : end at c2
        
        if(p1 != -1 && p1 <= c1) {
            f[0] = min(f[0], dp[0] + abs(lastRow[0] - p1) + abs(p1 - c1) + 2 * abs(c2 - c1));
            f[0] = min(f[0], dp[1] + abs(lastRow[lastRow.size() - 1] - p1) + abs(p1 - c1) + 2 * abs(c2 - c1));
            
            f[1] = min(f[1], dp[0] + abs(lastRow[0] - p1) + abs(p1 - c2));
            f[1] = min(f[1], dp[1] + abs(lastRow[lastRow.size() - 1] - p1) + abs(p1 - c2));
        }
        
        if(p2 != -1 && p2 <= c2) {
            f[0] = min(f[0], dp[0] + abs(lastRow[0] - p2) + abs(p2 - c2) + abs(c2 - c1));
            f[0] = min(f[0], dp[1] + abs(lastRow[lastRow.size() - 1] - p2) + abs(p2 - c2) + abs(c2 - c1)); 
            f[1] = min(f[1], dp[0] + abs(lastRow[0] - p2) + abs(p2 - c1) + abs(c1 - c2));
            f[1] = min(f[1], dp[1] + abs(lastRow[lastRow.size() - 1] - p2) + abs(p2 - c1) + abs(c1 - c2)); 
        }
        
        p2 = pre(c2 - 1);
        if(p2 != -1 && p2 <= c2) {
            f[0] = min(f[0], dp[0] + abs(lastRow[0] - p2) + abs(p2 - c2) + abs(c2 - c1));
            f[0] = min(f[0], dp[1] + abs(lastRow[lastRow.size() - 1] - p2) + abs(p2 - c2) + abs(c2 - c1)); 
            f[1] = min(f[1], dp[0] + abs(lastRow[0] - p2) + abs(p2 - c1) + abs(c1 - c2));
            f[1] = min(f[1], dp[1] + abs(lastRow[lastRow.size() - 1] - p2) + abs(p2 - c1) + abs(c1 - c2)); 
        }
        
        if(p3 != -1 && p3 >= c2) {
            f[0] = min(f[0], dp[0] + abs(lastRow[0] - p3) + abs(p3 - c2) + abs(c2 - c1));
            f[0] = min(f[0], dp[1] + abs(lastRow[lastRow.size() - 1] - p3) + abs(p3 - c2) + abs(c2 - c1));
            
            f[1] = min(f[1], dp[0] + abs(lastRow[0] - p3) + abs(p3 - c2) + 2 * abs(c1 - c2));
            f[1] = min(f[1], dp[1] + abs(lastRow[lastRow.size() - 1] - p3) + abs(p3 - c2) + 2 * abs(c1 - c2));
        }
        
        i = j - 1;
        lastRow = row;
        dp[0] = f[0];
        dp[1] = f[1];
    }
    
    cout << min(dp[0], dp[1]) + (a[a.size() - 1].first - a[0].first) << endl;
    
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

