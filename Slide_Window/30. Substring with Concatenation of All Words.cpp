/*
30. Substring with Concatenation of All Words
*/

// TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int n = s.size();
        const LL MOD = 1e9 + 7;
        const LL BASE = 499;
        vector<LL> hash(n+1);
        vector<LL> power(n+1);
        power[0] = 1;
        for(int i = 0; i < n; i++) {
            power[i+1] = (power[i] * BASE) % MOD;
            hash[i+1] = (hash[i] * BASE + (LL)s[i]) % MOD;
        }
        auto sub_hash = [&](int l, int r){
            return ((hash[r] - hash[l] * power[r-l]) % MOD + MOD) % MOD;
        };
        unordered_map<LL, LL> need;
        for(auto &word : words) {
            LL cur = 0;
            for(int i = 0;i < word.size(); i++) cur = (cur * BASE + (LL)word[i]) % MOD;
            need[cur] += 1;
        }
        int m = words[0].size(); // 每個字的長度
        int k = words.size(); // 多少個字 
        vector<int> res;
        for(int t = 0; t < m; t++) {
            unordered_map<LL, LL> mp;
            int i = t;
            int cnt = 0;
            for(int j = t; j + m <= n; j += m) {
                LL cur = sub_hash(j, j + m);
                if(need.count(cur)) {
                    mp[cur] += 1;
                    if(mp[cur] == need[cur]) cnt += 1;
                }
                if(j - i + m == m * k) {
                    if(cnt == need.size()) res.push_back(i);
                    LL tmp = sub_hash(i, i + m);
                    if(need.count(tmp)) {
                        if(need[tmp] == mp[tmp]) cnt -= 1;
                        mp[tmp] -= 1;
                    }
                    i += m;
                }
            }
        }

        return res;
    }
};

// 不用字符串哈希作法 TC:O(n * k) k 為source字串長度 SC:O(n)
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int n = s.size();
        int word_len = words[0].size();
        int total_len = word_len * words.size();
        unordered_map<string, int> need;
        for (auto &word : words) need[word]++;
        
        vector<int> res;

        for (int i = 0; i < word_len; i++) {
            unordered_map<string, int> mp;
            int left = i, cnt = 0;
            for (int j = i; j + word_len <= n; j += word_len) {
                string tmp = s.substr(j, word_len);

                if (need.count(tmp)) {
                    mp[tmp]++;
                    if (mp[tmp] == need[tmp]) cnt++;
                }
                if (j - left + word_len == total_len) {
                    if (cnt == need.size()) res.push_back(left);
                    string left_word = s.substr(left, word_len);
                    if (need.count(left_word)) {
                        if (mp[left_word] == need[left_word]) cnt--;
                        mp[left_word]--;
                    }
                    left += word_len;
                }
            }
        }

        return res;
    }
};
