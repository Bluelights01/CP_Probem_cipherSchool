#include <iostream>
#include <vector>
using namespace std;

/*
    This function computes the required answer based on:
    - Binary string s
    - 1-based index k

    Idea:
    1. count[i][len]  → number of alternating subsequences 
       of length = len starting at index i (for full string)

    2. count_k[i][len] → same idea but only for prefix [0 .. k-1]

    We compute DP from right to left.
*/

long long solve(string &s, int k) {

    int n = s.length();

    // Convert k to 0-based index
    k = k - 1;

    // DP table for entire string
    vector<vector<long long>> count(n, vector<long long>(7, 0));

    // DP table for prefix [0 .. k]
    vector<vector<long long>> count_k(k + 1, vector<long long>(7, 0));

    // Base case: subsequences of length 1
    for (int i = 0; i < n; i++) {
        count[i][1] = 1;
    }

    /*
        Fill DP for lengths 2 to 5
        We iterate backwards to build subsequences.
    */
    for (int len = 2; len <= 5; len++) {

        long long start_0 = 0;
        long long start_1 = 0;

        for (int i = n - 1; i >= 0; i--) {

            if (s[i] == '0') {
                start_0 += count[i][len - 1];
                count[i][len] = start_1;  // must alternate
            }
            else {
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
            }
            else {
                start_1 += count_k[i][len - 1];
                count_k[i][len] = start_0;
            }
        }
    }

    long long ans = 0;

    /*
        Final computation depends on whether s[k] is 0 or 1
    */
    if (s[k] == '0') {

        // Case 1: s[k] == '0'
        ans += count[k][5];

        long long sum = 0;

        // Count certain prefix combinations
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

        // Case 2: s[k] == '1'
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

    return ans;
}

int main() {

    int n;
    cin >> n;

    string s;
    cin >> s;

    int k;
    cin >> k;

    cout << solve(s, k) << endl;

    return 0;
}