/*
1438. Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit
*/

// 1120 TC:O(n) SC:O(n)
class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        int n = nums.size();
        // subarray 裡面最大以及最小的數字abs 在limit內 最長長度?
        deque<int> mn;
        deque<int> mx;
        int res = 0;
        int i = 0;
        for(int j = 0; j < n; j++) {
            while(!mx.empty() && nums[mx.back()] <= nums[j]) {
                mx.pop_back();
            }
            while(!mn.empty() && nums[mn.back()] >= nums[j]) {
                mn.pop_back();
            }
            mx.push_back(j);
            mn.push_back(j);

            while(nums[mx.front()] - nums[mn.front()] > limit) {
                if(mn.front() == i) {
                    mn.pop_front();
                }
                else if(mx.front() == i) {
                    mx.pop_front();
                }
                i++;
            }

            res = max(res, j-i+1);
        }

        return res;
    }
};

// 1/4
class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit){
        int n = nums.size();
        deque<int> dqMax;
        deque<int> dqMin;
        dqMax.push_back(0);
        dqMin.push_back(0);
        int j = 1;
        int res = 1;
        for(int i = 0; i < n; i++){
            while(j < n && nums[dqMax.front()] - nums[dqMin.front()] <= limit){
                // check whether new number would change maxVal or minVal
                while(!dqMin.empty() && nums[dqMin.back()] > nums[j]){
                    dqMin.pop_back();
                } 
                while(!dqMax.empty() && nums[dqMax.back()] < nums[j]){
                    dqMax.pop_back();
                } 
                dqMax.push_back(j);
                dqMin.push_back(j);
                if(nums[dqMax.front()] - nums[dqMin.front()] <= limit){
                    res = max(res, j-i+1);
                }
                j++;
            }
            if(dqMax.front() == i) dqMax.pop_front();
            if(dqMin.front() == i) dqMin.pop_front();
        }
        
        return res;
    }
};


// Multiset TC:O(nlgn) SC:O(n)
class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        int res = 1;
        multiset<int> set({nums[0]});
        int n = nums.size();
        int j = 0;
        for(int i = 0; i<n; i++){
            while(j<n && *set.rbegin()-*set.begin() <= limit){
                res = max(res, j-i+1);
                j++;
                if(j==n) break;
                set.insert(nums[j]);
            }
            if(j==n) break;
            set.erase(set.find(nums[i]));
        }

        return res;
    }
};

// Deque  TC:O(n) SC:O(n) 固定右端點寫法
class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        //在一個window中的最大最小值不可以超過limit
        //分別做最大最小值的deque
        int res = 1;
        int n = nums.size();
        deque<int> qmax({0});
        deque<int> qmin({0});
        int mx =nums[0]; int mn = nums[0];
        int j = 0;
        for(int i = 0; i<n; i++){
            while(mx-mn <= limit){
                res = max(res, j-i+1);
                j++;
                if(j == n) break;

                while(!qmax.empty() && nums[qmax.back()] <= nums[j]){
                    qmax.pop_back();
                }
                qmax.push_back(j);
                mx = nums[qmax.front()];

                while(!qmin.empty() && nums[qmin.back()] >= nums[j]){
                    qmin.pop_back();
                }
                qmin.push_back(j);
                mn = nums[qmin.front()];
            }
            
            //跳出limit範圍的可能是 雙指針j走到盡頭 或是最大減調最小值超過上限
            if(j == n) break;
            if(!qmax.empty() && qmax.front() == i){
                qmax.pop_front();
                mx = nums[qmax.front()];
            }
            if(!qmin.empty() && qmin.front() == i) {
                qmin.pop_front();
                mn = nums[qmin.front()];
            }
        }

        return res;
    }
};


// Deque 固定左端點 個人覺得比較直觀
class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        int n = nums.size();
        deque<int> qmax;
        deque<int> qmin; // 一個隊列只能維護一個最大or最小 用deque只是為了頭好彈出 在他年老色衰的時候
        int res = 1;
        int j = 0;
        for(int i = 0; i < n; i++){
            while(!qmax.empty() && nums[qmax.back()] < nums[i]){
                qmax.pop_back();
            }

            while(!qmin.empty() && nums[qmin.back()] > nums[i]){
                qmin.pop_back();
            }
            qmax.push_back(i);
            qmin.push_back(i);

            while(!qmax.empty()  && !qmin.empty() && nums[qmax.front()] - nums[qmin.front()] > limit){
                if(qmax.front() == j) qmax.pop_front();
                if(qmin.front() == j) qmin.pop_front();
                j++;
            }

            if(j == n) break;
            res = max(res, i-j+1);
          
        }

        return res;
    }
};
