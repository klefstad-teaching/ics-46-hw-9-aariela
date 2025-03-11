#include "ladder.h"
#include <cassert>

int main() {
    cout << "\nRunning error() test..." << endl;
    error("code", "data", "Test error message");

    cout << "\nRunning edit_distance_within() tests..." << endl;
    assert(edit_distance_within("code", "code", 0) == true);
    assert(edit_distance_within("code", "coda", 1) == true);
    assert(edit_distance_within("code", "codex", 1) == true);
    assert(edit_distance_within("code", "codes", 1) == true);
    assert(edit_distance_within("code", "cope", 1) == true);
    assert(edit_distance_within("code", "doge", 2) == true);
    assert(edit_distance_within("code", "data", 1) == false);

    cout << "\nRunning is_adjacent() tests..." << endl;
    assert(is_adjacent("code", "coda") == true);
    assert(is_adjacent("code", "cope") == true);
    assert(is_adjacent("code", "code") == false);
    assert(is_adjacent("code", "data") == false);

    cout << "\nRunning generate_word_ladder() test..." << endl;
    set<string> dictionary = {"cade", "cate", "date", "data"};
    vector<string> result = generate_word_ladder("cade", "data", dictionary);
    print_word_ladder(result);

    cout << "\nAll tests completed successfully." << endl;
    return 0;
}
