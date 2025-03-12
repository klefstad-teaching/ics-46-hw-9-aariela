#include "ladder.h"
#include <iostream>
#include <cmath>
#include <unordered_set> 

using namespace std;

// vector<string> global_ladder;
// set<string> global_word_list;

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
    if (begin_word == end_word) {
        error(begin_word, end_word, "Start and end words are the same");
        return {};
    }

    if (word_list.find(end_word) == word_list.end()) {
        error(begin_word, end_word, "End word not in dictionary");
        return {};
    }

    unordered_set<string> dict(word_list.begin(), word_list.end());
    queue<vector<string>> q;
    q.push({begin_word});
    unordered_set<string> visited;
    visited.insert(begin_word);

    while (!q.empty()) {
        int qSize = q.size();
        unordered_set<string> this_level_visited;

        for (int i = 0; i < qSize; ++i) {
            vector<string> path = q.front(); q.pop();
            string last_word = path.back();

            for (int j = 0; j < last_word.size(); ++j) {
                string new_word = last_word;
                for (char c = 'a'; c <= 'z'; ++c) {
                    if (c == last_word[j]) continue;
                    new_word[j] = c;

                    if (dict.find(new_word) == dict.end()) continue;

                    if (new_word == end_word) {
                        path.push_back(new_word);
                        return path;
                    }

                    if (visited.find(new_word) == visited.end()) {
                        vector<string> new_path = path;
                        new_path.push_back(new_word);
                        q.push(new_path);
                        this_level_visited.insert(new_word);
                    }
                }
            }
        }

        for (const auto& word : this_level_visited)
            visited.insert(word);
    }

    return {};
}

    // queue<vector<string>> ladder_queue;
    // set<string> visited;

    // ladder_queue.push({begin_word});
    // visited.insert(begin_word);

    // while (!ladder_queue.empty()) {
    //     vector<string> ladder = ladder_queue.front();
    //     ladder_queue.pop();

    //     string last_word = ladder.back();

    //     for (const string& word : word_list) {
    //         if (visited.find(word) != visited.end()) continue;
    //         if (is_adjacent(last_word, word)) {
    //             if (visited.find(word) == visited.end()) {
    //                 visited.insert(word);
    //                 vector<string> new_ladder = ladder;
    //                 new_ladder.push_back(word);

    //                 if (word == end_word) {
    //                     return new_ladder;
    //                 }

    //                 ladder_queue.push(new_ladder);
    //             }
    //         }
    //     }
    // }

    // return {};


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

void verify_word_ladder(const vector<string>& ladder, const set<string>& word_list) {
    if (ladder.empty()) {
        cout << "Ladder is empty. Cannot verify." << endl;
        return;
    }

    for (size_t i = 0; i < ladder.size(); ++i) {
        if (word_list.find(ladder[i]) == word_list.end()) {
            error(ladder[i], "", "Word not in dictionary");
            return;
        }
        if (i > 0 && !is_adjacent(ladder[i-1], ladder[i])) {
            error(ladder[i-1], ladder[i], "Invalid transition");
            return;
        }
    }

    cout << "Word ladder verified successfully." << endl;
}