#include "ladder.h"
#include <iostream>
#include <cmath>

using namespace std;

vector<string> global_ladder;
set<string> global_word_list;

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
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladder_queue;
    set<string> visited;

    ladder_queue.push({begin_word});
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();

        string last_word = ladder.back();

        for (const string& word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (visited.find(word) == visited.end()) {
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);

                    if (word == end_word) {
                        return new_ladder;
                    }

                    ladder_queue.push(new_ladder);
                }
            }
        }
    }

    return {};
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file.is_open()) {
        cout << "Failed to open file: " << file_name << endl;
        return;
    }
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
    file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    cout << "Word ladder found: ";
    for (const string& word : ladder) {
        cout << word << " ";
    }
    cout << "\n";
}

void verify_word_ladder() {
   if (global_ladder.empty()) {
        cout << "Ladder is empty. Cannot verify." << endl;
        return;
    }

    for (size_t i = 0; i < global_ladder.size(); ++i) {
        if (global_word_list.find(global_ladder[i]) == global_word_list.end()) {
            error(global_ladder[i], "", "Word not in dictionary");
            return;
        }
        if (i > 0 && !is_adjacent(global_ladder[i-1], global_ladder[i])) {
            error(global_ladder[i-1], global_ladder[i], "Invalid transition");
            return;
        }
    }

    cout << "Word ladder verified successfully." << endl;
}