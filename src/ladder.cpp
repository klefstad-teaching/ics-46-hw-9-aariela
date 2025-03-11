#include "ladder.h"
#include <iostream>
#include <cmath>

using namespace std;

void error(string word1, string word2, string msg) {
    cout << "Error: " << msg << " between '" << word1 << "' and '" << word2 << "'." << endl;
    return;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int m = str1.size();
    int n = str2.size();
    if (abs(m - n) > d) return false;

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (int i = 0; i <= m; ++i) dp[i][0] = i;
    for (int j = 0; j <= n; ++j) dp[0][j] = j;

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (str1[i - 1] == str2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]);
        }
    }

    return dp[m][n] <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1) && word1 != word2;
}

// vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {

// }

void load_words(set<string> & word_list, const string& file_name) {

}

void print_word_ladder(const vector<string>& ladder) {

}

void verify_word_ladder() {

}