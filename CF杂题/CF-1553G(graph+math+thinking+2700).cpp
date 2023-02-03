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

const int N = 1e6 + 10;
vector<int> primes[N];
set<pair<int, int>> edges;
set<int> singleEedge[N];
int pos[N], ele[N];
bool is[N];
int n, m;

int find(vector<int>& nums, int x){
  if(nums[x] == x) return x;
  int root = find(nums, nums[x]);
  nums[x] = root;
  return root;
}

//answer: 0 1 2
void solve() {
    vector<int> nums(N);
    for(int i = 0; i < nums.size(); i++) {
        nums[i] = i;
    }
 
    memset(pos, -1, sizeof pos);
    memset(ele, -1, sizeof ele);

    scanf("%d%d", &n, &m);
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        pos[a[i]] = i;
    }

    memset(is, false, sizeof is);
    int cnt = 0;
    for(int i = 2; i < N; i++) {
        if(is[i]) continue;
        int u = -1;
        cnt++;
        for(int j = i; j < N; j += i) {
            primes[j].push_back(i);
            is[j] = true;
            if(pos[j] != -1) {
                if(u == -1) u = pos[j];
                else {
                    int r1 = find(nums, pos[j]), r2 = find(nums, u);
                    if(r1 != r2) {
                        nums[r1] = r2;
                    }
                    u = pos[j];
                }
            }
        }
        ele[i] = u;
    } 
    
    for(int i = 1; i < N; i++) {
        if(pos[i] != -1) {
            int nxt = i + 1;
            vector<int>& pri = primes[nxt];
            // <<"nxt    " << nxt << "  " << pri << endl;
            
            for(int x = 0; x < pri.size(); x++) {
                for(int y = x + 1; y < pri.size(); y++) {
                    int t1 = ele[pri[x]], t2 = ele[pri[y]];
                    if(t1 != -1 && t2 != -1) {
                        int r1 = find(nums, t1), r2 = find(nums, t2);
                        if(r1 != r2) {
                            int mn = min(r1, r2), mx = max(r1, r2);
                            edges.insert({mn, mx});
                        }
                    }
                }
            }

            int r1 = find(nums, pos[i]);

            for(int& p : pri) {
                int u = ele[p];
                if(u != -1) {
                    int r2 = find(nums, u);
                    if(r1 != r2) {
                        singleEedge[r2].insert(r1);
                    }
                }
            }
        }
    }


    for(int i = 0; i < m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        x--; y--;
        int r1 = find(nums, x);
        int r2 = find(nums, y);
        if(r1 == r2) {
            printf("0\n");
        } else {
            int mn = min(r1, r2), mx = max(r1, r2);
            pair<int, int> p = {mn, mx};
            if(edges.find(p) != edges.end()) {
                printf("1\n");
                continue;
            }

            if(singleEedge[r1].find(r2) != singleEedge[r1].end() || singleEedge[r2].find(r1) != singleEedge[r2].end()) {
                printf("1\n");
                continue;
            }

            printf("2\n");
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
