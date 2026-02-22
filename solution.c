#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Computes the required answer based on:
    - Binary string s
    - 1-based index k

    count[i][len]  -> number of alternating subsequences
                      of length = len starting at index i
                      (for full string)

    count_k[i][len] -> same idea but only for prefix [0 .. k-1]
*/

long long solve(char *s, int k) {

    int n = strlen(s);

    // Convert k to 0-based index
    k = k - 1;

    // Allocate DP table for entire string
    long long **count = (long long **)malloc(n * sizeof(long long *));
    for (int i = 0; i < n; i++) {
        count[i] = (long long *)calloc(7, sizeof(long long));
    }

    // Allocate DP table for prefix [0 .. k]
    long long **count_k = (long long **)malloc((k + 1) * sizeof(long long *));
    for (int i = 0; i <= k; i++) {
        count_k[i] = (long long *)calloc(7, sizeof(long long));
    }

    // Base case: subsequences of length 1
    for (int i = 0; i < n; i++) {
        count[i][1] = 1;
    }

    // Fill DP for lengths 2 to 5 (full string)
    for (int len = 2; len <= 5; len++) {

        long long start_0 = 0;
        long long start_1 = 0;

        for (int i = n - 1; i >= 0; i--) {
            if (s[i] == '0') {
                start_0 += count[i][len - 1];
                count[i][len] = start_1;
            } else {
                start_1 += count[i][len - 1];
                count[i][len] = start_0;
            }
        }
    }

    // Base case for prefix DP
    for (int i = 0; i < k; i++) {
        count_k[i][1] = 1;
    }

    // Fill prefix DP
    for (int len = 2; len <= 5; len++) {

        long long start_0 = 0;
        long long start_1 = 0;

        for (int i = k - 1; i >= 0; i--) {
            if (s[i] == '0') {
                start_0 += count_k[i][len - 1];
                count_k[i][len] = start_1;
            } else {
                start_1 += count_k[i][len - 1];
                count_k[i][len] = start_0;
            }
        }
    }

    long long ans = 0;

    // Final computation
    if (s[k] == '0') {

        ans += count[k][5];

        long long sum = 0;

        for (int i = 0; i < k; i++) {
            if (s[i] == '0') {
                sum += count_k[i][2];
            }
        }

        ans += count[k][3] * sum;

        for (int i = 0; i < k; i++) {
            if (s[i] == '0') {
                ans += count_k[i][4];
            }
        }
    }
    else {

        long long sum = 0;

        for (int i = 0; i < k; i++) {
            if (s[i] == '0') {
                sum += count_k[i][3];
            }
        }

        ans += sum * count[k][2];

        sum = 0;

        for (int i = 0; i < k; i++) {
            if (s[i] == '0') {
                sum += count_k[i][1];
            }
        }

        ans += sum * count[k][4];
    }

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(count[i]);
    }
    free(count);

    for (int i = 0; i <= k; i++) {
        free(count_k[i]);
    }
    free(count_k);

    return ans;
}

int main() {

    int n;
    scanf("%d", &n);

    char s[200005];   // adjust size based on constraints
    scanf("%s", s);

    int k;
    scanf("%d", &k);

    printf("%lld\n", solve(s, k));

    return 0;
}