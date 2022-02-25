for (int right = 1; right <= n; ++right)
{
    dp[right][right] = 0;
    opt[right][right] = right;
    for (int left = right - 1; left >= 1; --left)
    {
        dp[left][right] = LINF;
        for (int k = max(left + 1, opt[left][right - 1]); k <= min(right, opt[left + 1][right]); ++k)
        {
            if (dp[left][k - 1] + dp[k][right] < dp[left][right])
            {
                dp[left][right] = dp[left][k - 1] + dp[k][right];
                opt[left][right] = k;
            }
        }
        dp[left][right] += get_sum(left, right, prefix_sums);
    }
}