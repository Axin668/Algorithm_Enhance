//
// Created by 陈艺欣 on 2022/11/28.
//

class Solution {
public:
    double largestSumOfAverages(vector<int>& nums, int k) {
        int n = nums.size();
        vector<double> sum(n + 1);
        //处理前缀和
        for(int i = 1; i <= n; i ++ ) sum[i] = sum[i - 1] + nums[i - 1];

        vector<vector<double>> dp(n + 1, vector<double>(k + 1));
        //处理边界, 将nums[0 ~ i - 1] 划分为1 段
        for(int i = 1; i <= n; i ++ ) dp[i][1] = sum[i] / i;

        //划分为2 ~ k段
        for(int j = 2; j <= k; j ++ ){
            //i往后走一个数字, 至少从j开始, 才可以分为j段
            for(int i = j; i <= n; i ++ ){
                //倒数第二个至少要从j - 1开始, 才可以分为j - 1段, 从而进行状态转移
                for(int x = j - 1; x < i; x ++ )
                    dp[i][j] = max(dp[i][j], dp[x][j - 1] + (sum[i] - sum[x]) / (i - x));
            }
        }
        return dp[n][k];
    }
};