def solve(s: str, k: int) -> int:
    """
    Computes the required answer based on:
    - Binary string s
    - 1-based index k

    count[i][length]  -> number of alternating subsequences
                         of given length starting at index i
                         (for full string)

    count_k[i][length] -> same idea but only for prefix [0 .. k-1]
    """

    n = len(s)

    # Convert k to 0-based index
    k -= 1

    # DP table for entire string
    count = [[0] * 7 for _ in range(n)]

    # DP table for prefix [0 .. k]
    count_k = [[0] * 7 for _ in range(k + 1)]

    # Base case: subsequences of length 1
    for i in range(n):
        count[i][1] = 1

    # Fill DP for lengths 2 to 5 (full string)
    for length in range(2, 6):
        start_0 = 0
        start_1 = 0

        for i in range(n - 1, -1, -1):
            if s[i] == '0':
                start_0 += count[i][length - 1]
                count[i][length] = start_1
            else:
                start_1 += count[i][length - 1]
                count[i][length] = start_0

    # Base case for prefix DP
    for i in range(k):
        count_k[i][1] = 1

    # Fill prefix DP
    for length in range(2, 6):
        start_0 = 0
        start_1 = 0

        for i in range(k - 1, -1, -1):
            if s[i] == '0':
                start_0 += count_k[i][length - 1]
                count_k[i][length] = start_1
            else:
                start_1 += count_k[i][length - 1]
                count_k[i][length] = start_0

    ans = 0

    # Final computation
    if s[k] == '0':
        # Case 1: s[k] == '0'
        ans += count[k][5]

        total = 0
        for i in range(k):
            if s[i] == '0':
                total += count_k[i][2]

        ans += count[k][3] * total

        for i in range(k):
            if s[i] == '0':
                ans += count_k[i][4]

    else:
        # Case 2: s[k] == '1'
        total = 0
        for i in range(k):
            if s[i] == '0':
                total += count_k[i][3]

        ans += total * count[k][2]

        total = 0
        for i in range(k):
            if s[i] == '0':
                total += count_k[i][1]

        ans += total * count[k][4]

    return ans


# Main driver
if __name__ == "__main__":
    n = int(input().strip())
    s = input().strip()
    k = int(input().strip())

    print(solve(s, k))