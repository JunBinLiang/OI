const int N = 2e4 + 10, M = 1e5 + 10;
const int INF = 1e9;

int h[N], e[M], w[M], ne[M], idx;
int dist[N];
int q[N], cnt[N];
bool st[N];
int n;

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

void spfa() {
    int hh = 0, tt = 1;
    for(int i = 0; i <= n; i++) dist[i] = -INF; 
    dist[0] = 0;
    q[0] = 0;
    st[0] = true;
    while (hh != tt)
    {
        int t = q[ -- tt];
        st[t] = false;

        for (int i = h[t]; ~i; i = ne[i])
        {
            int j = e[i];
            if (dist[j] < dist[t] + w[i])
            {
                dist[j] = dist[t] + w[i];
                if (!st[j])
                {
                    q[tt ++ ] = j;
                    st[j] = true;
                }
            }
        }
    }
}

class Solution {
public:
    int candy(vector<int>& a) {
        n = a.size();
        for(int i = 0; i <= n; i++) h[i] = -1;
        idx = 0;
        
        for(int i = 1; i < a.size(); i++) {
            if(a[i] > a[i - 1]) {
                add(i, i + 1, 1);
            } else {
                if(a[i] < a[i - 1]) {
                    add(i + 1, i, 1);
                }
            }
        }
        
        for(int i = 1; i <= a.size(); i++) {
            add(0, i, 1);
        }
        
        spfa();
        
        int res = 0;
        for(int i = 0; i <= a.size(); i++) {
            res += dist[i];
        }
        
        return res;
        
    }
};
