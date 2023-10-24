/*
494. Target Sum
*/

// 背包問題解法 類似01背包問題 但是這裡是不論 0 or 1 的解答都要加入res裡
// TC:O(n*sum) SC:O(n*sum)
class Solution {
    int dp[25][2005];
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size();
        nums.insert(nums.begin(), 0);
        int offset = 1000;
        
        //base case 
        dp[0][0+offset] = 1;// nums裡面定義為沒東西可以組成sum = 0的方式
        for(int i = 1; i <=n; i++){
            for(int sum = -1000; sum<=1000; sum++){
                if(sum-nums[i] >=-1000 && sum-nums[i] <= 1000)
                    dp[i][sum+offset] += dp[i-1][sum-nums[i]+offset];//會overflow 需有offset
                if(sum+nums[i] >=-1000 && sum+nums[i] <= 1000)
                    dp[i][sum+offset] += dp[i-1][sum+nums[i]+offset];
            }
        }

        return dp[n][target+offset];
    }
};

//recursion+memo TC:O(2^n)搭配剪枝 SC:O(n * sum)
class Solution {
    unordered_map<string, int> memo;
public:
    int findTargetSumWays(vector<int>& nums, int target) {

        return dp(nums, 0, target);
    }

    //定義為nums從0開始到終點 總共有幾種方式組成remain
    int dp(vector<int>& nums, int cur, int remain){
        //base case
        if(cur == nums.size()){
            if(remain == 0) return 1;
            return 0;//代表失敗
        }

        //將結果進入到memo 需轉成字串儲存
        string key = to_string(cur)+ ","+to_string(remain);

        if(memo.count(key)) return memo[key];//剪枝

        int result = dp(nums, cur+1, remain-nums[cur]) + dp(nums, cur+1, remain+nums[cur]);

        memo[key] = result;
        return result;
    }
};

/*
此題看似有兩種做法
1. 建立dp函式 recursion所有可能
2. dp 背包問題解法 每個數字都可以有兩種可能 + or -
dp[i][sum]: nums[0:i]可以組成sum的方法有幾個
dp[i][sum] = dp[i-1][sum-nums[i]] + dp[i-1][sum+nums[i]] 兩種可能相加
最後dp[n][target]就會是你要的答案 但這題小地方注意要再補數
*/
