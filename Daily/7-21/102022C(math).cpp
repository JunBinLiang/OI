#include <bits/stdc++.h>

int main() {
    const int maxn = 1e6 + 10;
    std::vector<long long> answer(maxn, INT_MAX);
    std::vector<long long> current(maxn);
    for (int i = 1; i < maxn; i++) {
        current[i] = i * 1LL * i + 1;
    }
    for (int i = 1; i < maxn; i++) {
        long long divisor = current[i];
        if (divisor == 1) {
            continue;
        }
        for (long long j = i; j < maxn; j += divisor) {
            while (current[j] % divisor == 0) current[j] /= divisor;
            answer[j] = std::min(answer[j], divisor);
        }
    }
	int q;
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        int x;
        scanf("%d", &x);
        if (answer[x] == INT_MAX || answer[x] == x * 1LL * x + 1) {
            printf("-1\n");
        } else {
            printf("%lld %lld\n", answer[x], (x * 1LL * x + 1) / answer[x]);
        }
    }
}
