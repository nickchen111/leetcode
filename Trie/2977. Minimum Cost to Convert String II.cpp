/*
2977. Minimum Cost to Convert String II
*/

// "TC:O(原始單詞數量 * 平均單詞長度 (構造Trie)+ n^3(Floyd) + m^2 * Trie查找單詞速度) SC:O(原始單詞數量 * 平均單詞長度 + n^2 + m)"
class Solution {
    using LL = long long;
    struct TrieNode{
        vector<TrieNode*> children;
        int idx;
        TrieNode(): children(26,NULL), idx(-1){}
        ~TrieNode(){
            for(auto child : children){
                if(child) delete child;
            }
        }
    };
    TrieNode* root = new TrieNode();
public:
    long long minimumCost(string source, string target, vector<string>& original, vector<string>& changed, vector<int>& cost) {
        
        //為了Trie的構造先reverse 因為這樣子在查找字串就不需呼叫substr的函式增加時間複雜度
        for(auto &s : original){
            reverse(s.begin(), s.end());
        }
        for(auto &s : changed){
            reverse(s.begin(), s.end());
        }
        unordered_set<string> set; // 去掉重複的字串
        set.insert(original.begin(), original.end());
        set.insert(changed.begin(), changed.end());

        //建構出字典樹 並且將他們賦予idx數值化 idx數值化也是方便去查找他們的距離 將他們當作節點一樣看待 將這些離散的數值歸併起來
        unordered_map<string,int> map;
        int idx = 0;
        for(string word : set){
            map[word] = idx;

            TrieNode* node = root;
            for(auto ch : word){
                if(node->children[ch-'a'] == NULL) node->children[ch-'a'] = new TrieNode();
                node = node->children[ch-'a'];
            }
            node->idx = idx;
            idx++;
        }

        int n = set.size();
        LL d[n][n];
        
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(i == j) d[i][j] = 0;
                else d[i][j] = LLONG_MAX/2;
            }
        }

        for(int i = 0; i < original.size(); i++){
            d[map[original[i]]][map[changed[i]]] = min(d[map[original[i]]][map[changed[i]]], (LL)cost[i]);
        }

        // Floyd n^3找出更優的距離
        for(int k = 0; k < n; k++){
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }

        // dp
        int m = source.size();
        source = "#" + source;
        target = "#" + target;
        vector<LL> dp(m+1);
        for(int i = 1; i <= m; i++){
            dp[i] = LLONG_MAX/2;
            if(source[i] == target[i]) dp[i] = dp[i-1];
            TrieNode* node1 = root;
            TrieNode* node2 = root;
           
            for(int j = i; j >= 1; j--){
                if(node1->children[source[j]-'a'] == NULL) break;
                if(node2->children[target[j]-'a'] == NULL) break;
                node1 = node1 -> children[source[j]-'a'];
                node2 = node2 -> children[target[j]-'a'];
                int idx1 = node1->idx;
                int idx2 = node2->idx;
                if(idx1 != -1 && idx2 != -1){
                    dp[i] = min(dp[i], dp[j-1] + d[idx1][idx2]);
                }
            }
        }

        if(dp[m] == LLONG_MAX/2) return -1;
        return dp[m];

    }
};

//原始做法 -> TLE
using LL = long long;
class Solution {    
public:
    long long minimumCost(string source, string target, vector<string>& original, vector<string>& changed, vector<int>& cost) 
    {
        unordered_set<string>Set;
        Set.insert(original.begin(), original.end());
        Set.insert(changed.begin(), changed.end());
        unordered_map<string, int>Map;
        int idx = 0;
        for (string x: Set)
        {
            Map[x] = idx;
            idx++;
        }
        
        int n = Set.size();
        LL d[n][n];
        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++)
            {
                if (i==j)
                    d[i][j] = 0;
                else
                    d[i][j] = LLONG_MAX/2;
            }
        
        for (int i=0; i<original.size(); i++)
            d[Map[original[i]]][Map[changed[i]]] = min(d[Map[original[i]]][Map[changed[i]]], (LL)cost[i]);
        
        for (int k=0; k<n; k++)
            for (int i=0; i<n; i++)
                for (int j=0; j<n; j++)
                    d[i][j] = min(d[i][j], d[i][k]+d[k][j]);
        
        
        int m = source.size();
        source = "#"+source;
        target = "#"+target;
        
        vector<LL>dp(m+1);
        dp[0] = 0;
        
        for (int i=1; i<=m; i++)
        {
            dp[i] = LLONG_MAX/2;
            if (source[i]==target[i])
                dp[i] = dp[i-1];            
            
            string a;
            string b;
            for (int j=i; j>=1; j--)
            {
                a = source.substr(j,1) + a;
                b = target.substr(j,1) + b;
                
                if (Map.find(a)!=Map.end() && Map.find(b)!=Map.end())
                    dp[i] = min(dp[i], dp[j-1] + d[Map[a]][Map[b]]);
            }
        }
        
        if (dp[m]==LLONG_MAX/2) return -1;
        
        return dp[m];
    }
};

/*
此題就是2976的進階題 不像2976只問說字母到字母的cost這題直接給你字串 字串到字串的cost
要你將source字串轉成target字串所需最小cost
1.字串轉字串 切割字串 長度1000可以接受n^2 -> 區間型DP
2. 字串到字串之間的最小cost n = 100 -> n^3 -> Floyd
但是實際在寫的時候會發現要切割原本的字串需要時間 看字串長度也可能是O(n) 就算改成倒著加入字串轉成O(1)
還是會在map.find()查找離散化序列的時候花費時間造成TLE(正常的字符串要哈希成什麼東西也要時間)此時要開始想有哪種資料結構是可以快速查找字串的呢？ Trie
*/
