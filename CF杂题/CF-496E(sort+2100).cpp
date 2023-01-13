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
const int N = 1e5 + 10;
int n, m;
int ans[N];

struct E {
    int l, r, i, k, ty;
};

//9:27  9:48
bool COMP(E& e1, E& e2) {
    if(e1.l == e2.l) {
        if(e1.ty == e2.ty) {
            return e1.r > e2.r;
        }
        return e1.ty > e2.ty;
    }
    return e1.l < e2.l;
}

void solve() {
    scanf("%d", &n);
    vector<E> a;
    
    for(int i = 0; i < n; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        a.push_back({l, r, i, 0, 1});
    }
    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        a.push_back({l, r, i, k, 2});
    }

    sort(a.begin(), a.end(), COMP);
    map<int, vector<pair<int, int>>> f;
    
    /*for(auto it : a) {
        cout << it.l << " " << it.r << " "  << it.i << " " << it.k << " " << it.ty << endl;
    }*/
    
    for(int i = 0; i < a.size(); i++) {
        if(a[i].ty == 1) {
            //f[a[i].r].push_back(a[i].i);
             int j = i;
             while(j < a.size() && a[j].l == a[i].l) {
                 int l = a[j].l, r = a[j].r, idx = a[j].i;
                 auto nxt = f.upper_bound(r - 1);
                 if(nxt == f.end()) {
                     cout << "NO" << endl;
                     return;
                 }
                 
                 
                 vector<pair<int, int>> & v = nxt -> second;
                 int sz = v.size();
                 v[sz - 1].first --;
                 ans[idx] = v[sz - 1].second;
                 
                 //cout <<"get  " << idx << "  " <<  v[sz - 1].second << endl;
                 
                 if(v[sz - 1].first == 0) v.pop_back();
                 if(v.size() == 0) f.erase(nxt);
                 j++;
             }
             
             i = j - 1;
        } else {
            /*int j = i;
            while(j < a.size() && a[j].l == a[i].l) {
                int k  = a[j].k, r = a[j].r;
                cout <<"que  " << a[j].l << "  " << a[j].r << endl;
                for(int x = 0; x < k && f.size(); x++) {
                    auto nxt = f.upper_bound(r - 1);
                    cout <<"find  " << nxt -> first << endl;
                    if(nxt == f.end()) break;
                    
                    vector<int> & indexs = nxt -> second;
                    int last = indexs[indexs.size() - 1];
                    ans[last] = a[j].i;
                    indexs.pop_back();
                    if(indexs.size() == 0) f.erase(nxt);
                }
                j++;
            }
            i = j - 1;*/
            f[a[i].r].push_back({a[i].k, a[i].i});
        }
    }


    printf("YES\n");
    for(int i = 0; i < n; i++) {
        printf("%d ", ans[i] + 1);
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
