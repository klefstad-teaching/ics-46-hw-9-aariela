#include "ladder.h"
#include <cassert>
// extern vector<string> global_ladder;
// extern set<string> global_word_list;

int main() {
    // cout << "\nRunning error() test..." << endl;
    // error("code", "data", "Test error message");

    // cout << "\nRunning edit_distance_within() tests..." << endl;
    // assert(edit_distance_within("code", "code", 0) == true);
    // assert(edit_distance_within("code", "coda", 1) == true);
    // assert(edit_distance_within("code", "codex", 1) == true);
    // assert(edit_distance_within("code", "codes", 1) == true);
    // assert(edit_distance_within("code", "cope", 1) == true);
    // assert(edit_distance_within("code", "doge", 2) == true);
    // assert(edit_distance_within("code", "data", 1) == false);

    // cout << "\nRunning is_adjacent() tests..." << endl;
    // assert(is_adjacent("code", "coda") == true);
    // assert(is_adjacent("code", "cope") == true);
    // assert(is_adjacent("code", "code") == false);
    // assert(is_adjacent("code", "data") == false);

    // cout << "\nRunning generate_word_ladder() test..." << endl;
    // set<string> dictionary = {"cade", "cate", "date", "data"};
    // vector<string> result = generate_word_ladder("cade", "data", dictionary);
    // print_word_ladder(result);

    // cout << "\nRunning load_words() test..." << endl;
    // set<string> loaded_words;
    // load_words(loaded_words, "src/words.txt");
    // cout << "Loaded " << loaded_words.size() << " words from file." << endl;

    // cout << "\nRunning verify_word_ladder() test..." << endl;
    // global_ladder = result;
    // global_word_list = dictionary;
    // //verify_word_ladder();

    // cout << "\nAll tests completed successfully." << endl;

    // set<string> dict = {"cat", "bat", "bet", "bed", "at", "ad", "ed"};
    // vector<string> result = generate_word_ladder("cat", "bed", dict);
    // print_word_ladder(result);

    set<string> word_list = {
        "hit", "hot", "dot", "dog", "cog", "log", "lot"
    };

    // Test 1: Normal case — valid ladder exists
    cout << "\n--- Test 1: Valid Ladder ---\n";
    vector<string> ladder1 = generate_word_ladder("hit", "cog", word_list);
    print_word_ladder(ladder1);
    verify_word_ladder(ladder1, word_list);

    // Test 2: No ladder possible
    cout << "\n--- Test 2: No Ladder ---\n";
    set<string> word_list2 = {"abc", "def", "ghi"};
    vector<string> ladder2 = generate_word_ladder("abc", "ghi", word_list2);
    print_word_ladder(ladder2);
    verify_word_ladder(ladder2, word_list2);

    // Test 3: Start and end are the same
    cout << "\n--- Test 3: Start Equals End ---\n";
    vector<string> ladder3 = generate_word_ladder("hit", "hit", word_list);
    print_word_ladder(ladder3);

    // Test 4: Start or End word not in dictionary
    cout << "\n--- Test 4: Word Not in Dictionary ---\n";
    vector<string> ladder4 = generate_word_ladder("hit", "zzz", word_list);
    print_word_ladder(ladder4);
    verify_word_ladder(ladder4, word_list);

    // Test 5: Larger dictionary with multiple paths
    cout << "\n--- Test 5: Multiple Paths ---\n";
    set<string> word_list3 = {
        "hit", "hot", "dot", "dog", "cog", "log", "lot", "lit", "cit", "cot"
    };
    vector<string> ladder5 = generate_word_ladder("hit", "cog", word_list3);
    print_word_ladder(ladder5);
    verify_word_ladder(ladder5, word_list3);
    return 0;
}
