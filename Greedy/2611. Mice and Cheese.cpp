/*
2611. Mice and Cheese
*/

// TC:O(nlgn) SC:O(n)
class Solution {
public:
    int miceAndCheese(vector<int>& reward1, vector<int>& reward2, int k) {
        int n = reward1.size();
        vector<pair<int,int>> reward(n);
        for(int i = 0; i < n; i++){
            reward[i] = {reward1[i] - reward2[i], i};
        }
       
        sort(reward.rbegin(), reward.rend());
        //也須記錄自己取了哪些idx 
       
        int res = 0;
        int i;
        for(i = 0; i < k; i++){
            res += reward1[reward[i].second];
        }

        for(;i < n; i++){
           int idx = reward[i].second;
           res += reward2[idx];
        }

        return res;
        
    }
};

/*
兩個數組代表兩隻貓咪吃某種type的起司所能得的分數
題目規定 第一隻貓一定要吃k種type 能得到的最大分數為何？
那就會是兩個數組2*n取不重複的最大n個
reward1 - reward2 -> 得到的分數
[-3 -3 2 3] Greedy
*/
