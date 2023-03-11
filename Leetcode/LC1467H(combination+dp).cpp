double fact[49];
int N;
class Solution {
public:
    double getProbability(vector<int>& a) {
        fact[0] = fact[1] = 1;
        for(int i = 2; i < 49; i++) {
            fact[i] = fact[i - 1] * i;
        }
        int tot = 0; double y = 1;
        for(int i : a) tot += i;
        N = tot / 2;
        for(int i = 0; i < a.size(); i++) {
            y *= C(tot, a[i]);
            tot -= a[i];
        }
        return cal(a) / y;
    }
    
    double C(int n, int r) {
        return fact[n] / (fact[r] * fact[n - r]);
    }
    
    double cal(vector<int>& a) {
        double res = 0;
        double dp[2][25][25][9][9];
        memset(dp, 0.0, sizeof dp);
        dp[0][0][0][0][0] = 1.0;
        for(int cnt : a) {
            for(int x = 0; x <= cnt; x++) {
                int add1 = 0, add2 = 0;
                if(x > 0) add1 = 1;
                if(cnt - x > 0) add2 = 1;
                for(int i = 0; i <= N; i++) {
                    for(int j = 0; j <= N; j++) {
                        for(int l = 0; l <= a.size(); l++) {
                            for(int r = 0; r <= a.size(); r++) {
                                if(i + x <= N && j + (cnt - x) <= N && l + add1 <= a.size() && r + add2 <= a.size()) {
                                    dp[1][i + x][j + (cnt - x)][l + add1][r + add2] += dp[0][i][j][l][r] * C(N - i, x) * C(N - j, cnt - x);
                                }
                            }
                        }
                    }
                }
            }
            swap(dp[0], dp[1]);
            memset(dp[1], 0, sizeof dp[1]);
        }
        for(int i = 0; i <= a.size(); i++) res += dp[0][N][N][i][i];
        return res;
    }
    
};
