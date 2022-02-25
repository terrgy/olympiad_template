// width[1] < width[2] < width[3] < ... < width[n]
// height[1] > height[2] > height[3] > ... > height[n]

vector<ll> dp(len(sorted) + 1);
vector< pair<ll, int> > cht;
dp[0] = 0;

cht.emplace_back(-INF, 1);
dp[1] = (ll)sorted[0].height * sorted[0].width;

int last_ind = 0;
for (int i = 2; i <= len(sorted); ++i)
{
while (!cht.empty())
{
ll inters = (dp[i - 1] - dp[cht.back().second - 1] - 1) / (sorted[cht.back().second - 1].height - sorted[i - 1].height) + 1;
if (inters > cht.back().first)
{
cht.emplace_back(inters, i);
break;
}
cht.pop_back();
}

last_ind = min(last_ind, len(cht) - 1);
while ((last_ind + 1 < len(cht)) && (cht[last_ind + 1].first <= sorted[i - 1].width))
{
++last_ind;
}

dp[i] = dp[cht[last_ind].second - 1] + (ll)sorted[cht[last_ind].second - 1].height * sorted[i - 1].width;
}