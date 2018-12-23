#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
using namespace std;

class Solution
{
public:
    map<char, string> letters;
    vector<string> letterCombinations(string digits)
    {
        vector<string> ans;
        if(digits.size() <= 2) {
            if(digits.size() == 1) {
                string s1 = letters[digits[0]];
                for( char& c : s1) {
                    ans.push_back({c});
                }
            } else {
                string s1 = letters[digits[0]];
                string s2 = letters[digits[1]];
                for( char& c1 : s1) {
                    for(char& c2 : s2)
                        ans.push_back({c1 , c2});
                }
            }

        } else {
            string s1 = letters[digits[0]];
            for( char c : s1) {
                vector<string> vec = letterCombinations(digits.substr(1, digits.size()));

                for( string& s : vec) {
                    string tmp = c + s;
                    ans.push_back(tmp);
                }
            }
        }

        return ans;
    }
};
