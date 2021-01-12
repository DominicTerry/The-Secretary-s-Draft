/*
Remove the minimum number of invalid parentheses in order to make the input string valid. Return all possible results.

Note: The input string may contain letters other than the parentheses ( and ).

Example 1:

Input: "()())()"
Output: ["()()()", "(())()"]
Example 2:

Input: "(a)())()"
Output: ["(a)()()", "(a())()"]
Example 3:

Input: ")("
Output: [""]
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        unordered_set<string> result;
        int left_removed = 0;
        int right_removed = 0;
        for(auto c : s) {
            if(c == '(') {
                ++left_removed;
            }
            if(c == ')') {
                if(left_removed != 0) {
                    --left_removed;
                }
                else {
                    ++right_removed;
                }
            }
        }
        helper(s, 0, left_removed, right_removed, 0, "", result);
        return vector<string>(result.begin(), result.end());
    }

private:
    void helper(string s, int index, int left_removed, int right_removed, int pair, string path, unordered_set<string>& result) {
        if(index == s.size()) {
            if(left_removed == 0 && right_removed == 0 && pair == 0) {
                result.insert(path);
            }
            return;
        }
        if(s[index] != '(' && s[index] != ')') {
            helper(s, index + 1, left_removed, right_removed, pair, path + s[index], result);
        }
        else {
            if(s[index] == '(') {
                if(left_removed > 0) {
                    helper(s, index + 1, left_removed - 1, right_removed, pair, path, result);
                }
                helper(s, index + 1, left_removed, right_removed, pair + 1, path + s[index], result);
            }
            if(s[index] == ')') {
                if(right_removed > 0) {
                    helper(s, index + 1, left_removed, right_removed - 1, pair, path, result);
                }
                if(pair > 0) {
                    helper(s, index + 1, left_removed, right_removed, pair - 1, path + s[index], result);
                }
            }
        }
    }
};

vector<string> removeInvalidParentheses(string s) {

    vector<string> res;
    queue<string> q;
    map<string, int> visited;
    q.push(s);
    ++visited[s];

    while (!q.empty()) {
        bool found = false;
        s = q.front();
        q.pop();
        //判断是否合理
        if (isvalid(s)) {
            found = true;
            res.push_back(s);
        }
        if (found)continue;
        //如果此字符串不合理则
        for (int i = 0;i < s.size();i++) {
            if (s[i] != ')'&&s[i] != '(')continue;
            //拼凑新的字符串
            string t = s.substr(0, i) + s.substr(i + 1);
            //如果新的字符串之前没遇到过就将其入队列
            if (visited.find(t) == visited.end()) {
                q.push(t);
                ++visited[t];
            }
        }

    }

    return res;
}
//验证是否是合理串的函数（之前用栈实现过这个功能）
bool isvalid(string s) {

    int cnt = 0;
    for (int i = 0;i < s.size();i++) {

        if (s[i] == '(')++cnt;
        if (s[i] == ')'&&cnt-- == 0)return false;
    }
    return cnt == 0;
}

//测试函数
int main() {

    string s;
    while (cin >> s) {

        vector<string> res = removeInvalidParentheses(s);

        for (auto a : res) {
            cout << a << endl;
        }
    }
    return 0;
}
