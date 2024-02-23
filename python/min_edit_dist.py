def return_DP_table(word1, word2):
    m = len(word1)
    n = len(word2)
    dp = [[0] * (n + 1) for _ in range(m + 1)]
    # initialize the dp table
    # d[i][0] = i and d[0][j] = j
    for i in range(m + 1):
        dp[i][0] = i
    for j in range(n + 1):
        dp[0][j] = j
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            dp[i][j] = min(dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] if word1[i - 1] == word2[j - 1] else dp[i - 1][j - 1] + 2)
    return dp

def backtrace_alignment(dp, word1, word2):
    result = []
    w1 = ""
    w2 = ""
    i = len(dp) - 1
    j = len(dp[0]) - 1
    while i > 0 and j > 0:
        # find which operation was performed by finding min of i-1,j-1, i-1,j, i,j-1
        min_val = min(dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1])
        if min_val == dp[i - 1][j - 1]:  # ptr going diagonal
            w1 = word1[i - 1] + w1
            w2 = word2[j - 1] + w2
            i -= 1
            j -= 1
        elif min_val == dp[i - 1][j]:  # ptr going up
            w1 = word1[i - 1] + w1
            w2 = "-" + w2
            i -= 1
        else:  # ptr going left
            w1 = "-" + w1
            w2 = word2[j - 1] + w2
            j -= 1
    while i > 0:
        w1 = word1[i - 1] + w1
        w2 = "-" + w2
        i -= 1
    while j > 0:
        w1 = "-" + w1
        w2 = word2[j - 1] + w2
        j -= 1
    result.append(w1)
    result.append(w2)
    return result

def return_min_dist(dp):
    return dp[-1][-1]

def print_min_dist_table(dp):
    for i in range(len(dp)):
        for j in range(len(dp[0])):
            print(dp[i][j], end=" ")
        print()

word1 = "intention"
word2 = "execution"
dp = return_DP_table(word1, word2)
print("Minimum Edit Distance:", return_min_dist(dp))
print("Following is the DP table:")
print_min_dist_table(dp)
result = backtrace_alignment(dp, word1, word2)
print("Alignment:")
print(result[0])
print(result[1])