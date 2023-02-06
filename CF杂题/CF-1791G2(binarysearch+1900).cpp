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


bool COMP(pair<int, int>& p1, pair<int, int>& p2) {
    return min(p1.first, p1.second) < min(p2.first, p2.second);
}

const int N = 2e5 + 10;
int n;
ll c;
ll p[N];
void solve() {
    cin >> n >> c;
    vector<pair<int, int>> a;
    for(int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        a.push_back({x + i, x + (n + 1 - i)});
    }
    
    sort(a.begin(), a.end(), COMP);
    for(int i = 0; i < a.size(); i++) {
        p[i] = min(a[i].first, a[i].second);
        if(i) p[i] += p[i - 1];
    }
    
    /*for(int i = 0; i < a.size(); i++) {
        cout << a[i].first << "  " << a[i].second << endl;
    }
    
    for(int i = 0; i < a.size(); i++) {
        cout << p[i] << "  ";
    } cout << endl;*/


    int res = 0;
    for(int i = 0; i < a.size(); i++) {
        int cnt = 0;
        ll tt = a[i].first;
        if(tt <= c) cnt = 1;
        int l = 0, r = a.size() - 1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            ll sum = p[mid];
            if(i <= mid) {
                sum -= min(a[i].first, a[i].second);
            }
            sum += tt;
            
           // if(i == 2) {
                //cout << "gg  " << mid << "  " << sum << endl;
               // cout << tt << endl;
            //}
            
            if(sum <= c) {
                if(i <= r) cnt = max(cnt, mid + 1);
                else {
                    cnt = max(cnt, mid + 2);
                }
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        res = max(res, cnt);
    }

    printf("%d\n", res);

} 


int main() {
	// your code goes here
	int t = 1;
	cin >> t;
	while(t--) {
	    solve();
	}
	return 0;
}  
