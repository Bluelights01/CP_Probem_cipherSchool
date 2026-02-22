"use strict";

/*
    Computes the required answer based on:
    - Binary string s
    - 1-based index k

    count[i][len]  -> number of alternating subsequences
                      of length = len starting at index i
                      (for full string)

    count_k[i][len] -> same idea but only for prefix [0 .. k-1]
*/

function solve(s, k) {
    const n = s.length;

    // Convert k to 0-based index
    k = k - 1;

    // DP table for entire string
    const count = Array.from({ length: n }, () => Array(7).fill(0));

    // DP table for prefix [0 .. k]
    const count_k = Array.from({ length: k + 1 }, () => Array(7).fill(0));

    // Base case: subsequences of length 1
    for (let i = 0; i < n; i++) {
        count[i][1] = 1;
    }

    // Fill DP for lengths 2 to 5 (full string)
    for (let len = 2; len <= 5; len++) {
        let start_0 = 0;
        let start_1 = 0;

        for (let i = n - 1; i >= 0; i--) {
            if (s[i] === '0') {
                start_0 += count[i][len - 1];
                count[i][len] = start_1;
            } else {
                start_1 += count[i][len - 1];
                count[i][len] = start_0;
            }
        }
    }

    // Base case for prefix DP
    for (let i = 0; i < k; i++) {
        count_k[i][1] = 1;
    }

    // Fill prefix DP
    for (let len = 2; len <= 5; len++) {
        let start_0 = 0;
        let start_1 = 0;

        for (let i = k - 1; i >= 0; i--) {
            if (s[i] === '0') {
                start_0 += count_k[i][len - 1];
                count_k[i][len] = start_1;
            } else {
                start_1 += count_k[i][len - 1];
                count_k[i][len] = start_0;
            }
        }
    }

    let ans = 0;

    // Final computation
    if (s[k] === '0') {

        ans += count[k][5];

        let sum = 0;
        for (let i = 0; i < k; i++) {
            if (s[i] === '0') {
                sum += count_k[i][2];
            }
        }

        ans += count[k][3] * sum;

        for (let i = 0; i < k; i++) {
            if (s[i] === '0') {
                ans += count_k[i][4];
            }
        }

    } else {

        let sum = 0;
        for (let i = 0; i < k; i++) {
            if (s[i] === '0') {
                sum += count_k[i][3];
            }
        }

        ans += sum * count[k][2];

        sum = 0;
        for (let i = 0; i < k; i++) {
            if (s[i] === '0') {
                sum += count_k[i][1];
            }
        }

        ans += sum * count[k][4];
    }

    return ans;
}


// ---- Input Handling (Node.js) ----

const fs = require("fs");

const input = fs.readFileSync(0, "utf8").trim().split("\n");

const n = parseInt(input[0]);
const s = input[1].trim();
const k = parseInt(input[2]);

console.log(solve(s, k));