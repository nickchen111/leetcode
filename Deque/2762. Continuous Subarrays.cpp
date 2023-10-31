/*
2762. Continuous Subarrays
*/


// TC:O(n) SC:O(n)
class Solution {
public:
    long long continuousSubarrays(vector<int>& nums) {
        int n = nums.size();
        long long res = 0;
        //滑動窗口紀錄最大最小值
        deque<int> qmax;
        deque<int> qmin;

        int i = 0;
        for(int j = 0; j < n; j++){
            while(!qmax.empty() && nums[qmax.back()] <= nums[j]){
                qmax.pop_back();
            }

            while(!qmin.empty() && nums[qmin.back()] >= nums[j]){
                qmin.pop_back();
            }

            qmax.push_back(j);
            qmin.push_back(j);

            while(!qmax.empty() && !qmin.empty() && nums[qmax.front()] - nums[qmin.front()] > 2){
                if(!qmax.empty() &&qmax.front() <= i) qmax.pop_front();
                if(!qmin.empty() && qmin.front() <= i) qmin.pop_front();
                i++;
            }
            res +=(long long)(j-i+1);
        }

        return res;
    }
};
