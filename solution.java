import java.util.*;

public class Main {

    /*
        Computes the required answer based on:
        - Binary string s
        - 1-based index k

        count[i][len]  -> number of alternating subsequences
                          of length = len starting at index i
                          (for full string)

        count_k[i][len] -> same idea but only for prefix [0 .. k-1]
    */

    public static long solve(String s, int k) {

        int n = s.length();

        // Convert k to 0-based index
        k = k - 1;

        // DP table for entire string
        long[][] count = new long[n][7];

        // DP table for prefix [0 .. k]
        long[][] count_k = new long[k + 1][7];

        // Base case: subsequences of length 1
        for (int i = 0; i < n; i++) {
            count[i][1] = 1;
        }

        // Fill DP for lengths 2 to 5 (full string)
        for (int len = 2; len <= 5; len++) {

            long start_0 = 0;
            long start_1 = 0;

            for (int i = n - 1; i >= 0; i--) {

                if (s.charAt(i) == '0') {
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

            long start_0 = 0;
            long start_1 = 0;

            for (int i = k - 1; i >= 0; i--) {

                if (s.charAt(i) == '0') {
                    start_0 += count_k[i][len - 1];
                    count_k[i][len] = start_1;
                } else {
                    start_1 += count_k[i][len - 1];
                    count_k[i][len] = start_0;
                }
            }
        }

        long ans = 0;

        // Final computation
        if (s.charAt(k) == '0') {

            ans += count[k][5];

            long sum = 0;

            for (int i = 0; i < k; i++) {
                if (s.charAt(i) == '0') {
                    sum += count_k[i][2];
                }
            }

            ans += count[k][3] * sum;

            for (int i = 0; i < k; i++) {
                if (s.charAt(i) == '0') {
                    ans += count_k[i][4];
                }
            }

        } else {

            long sum = 0;

            for (int i = 0; i < k; i++) {
                if (s.charAt(i) == '0') {
                    sum += count_k[i][3];
                }
            }

            ans += sum * count[k][2];

            sum = 0;

            for (int i = 0; i < k; i++) {
                if (s.charAt(i) == '0') {
                    sum += count_k[i][1];
                }
            }

            ans += sum * count[k][4];
        }

        return ans;
    }

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();
        String s = sc.next();
        int k = sc.nextInt();

        System.out.println(solve(s, k));

        sc.close();
    }
}