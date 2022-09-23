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


bool COMP(const pair<int, int>& p1, const pair<int, int>& p2) {
    return p1.first > p2.first;
}

int find(ve<int>& nums, int x){
  if(nums[x] == x) return x;
  int root = find(nums, nums[x]);
  nums[x] = root;
  return root;
}

void merge(ve<int>& nums, int r1, int r2) {
    nums[r1] = r2;
    
}

int n, m;
const int N = 2e5 + 10;
ll res = 0;
pair<int, int> g[N];
int tag[N];
int main() {
    scanf("%d%d", &n, &m);
    vector<pair<int, int>> a;
    for(int i = 0; i < m; i++) {
        int x, y, w;
        scanf("%d%d%d", &x, &y, &w);
        g[i] = {x, y};
        a.push_back({w, i});
    }

    sort(a.begin(), a.end(), COMP);
    memset(tag, 0, sizeof(tag));
    vector<int> nums(N);
    for(int i = 0; i < nums.size(); i++) {
        nums[i] = i;
    }

    for(int i = 0; i < a.size(); i++) {
        int w = a[i].first, idx = a[i].second;
        int u = g[idx].first, v = g[idx].second;
        int r1 = find(nums, u), r2 = find(nums, v);
        if(r1 != r2) {
            if(tag[r1] + tag[r2] < 2) {
                tag[r1] += tag[r2];
                nums[r2] = r1;
                res += w; 
            }
        } else {
            if(!tag[r1]) {
                tag[r1] ++;
                res += w;
            }
        }
        
    }
    cout << res << endl;
    return 0;
}
