class Solution {
public:
    long long minimumMoney(vector<vector<int>>& a) {
        long long res = 0;
        long long neg = 0;
        for(int i = 0; i < a.size(); i++) {
            int earn = a[i][1], cost = a[i][0];
            res = max(res, cost + 0ll);
            int p = earn - cost;
            if(p < 0) {
                neg += abs(p);
            }
        }

        for(int i = 0; i < a.size(); i++) {
            int earn = a[i][1], cost = a[i][0];
            int p = earn - cost;
            if(p < 0) {
                res = max(res, cost + (neg - abs(p)));
            } else {
                res = max(res, cost + neg);
            }
        }

        return res;
    }
};
