#include "ladder.h"

//g++ -std=c++20 -Wall -Wextra -pthread -I src -I gtest    src/ladder.cpp src/ladder_main.cpp     -o ladder -lgtest_main -lgtest -pthread
g++ -std=c++20 -Wall -Wextra -pthread -I src -I gtest    src/dijkstras_main.cpp src/dijkstras.cpp     -o dijkstras -lgtest_main -lgtest -pthread
int main() {
    set<string> word_list;
    load_words(word_list, "src/words.txt");

    string start_word, end_word;
    cout << "Enter start word: ";
    cin >> start_word;
    cout << "Enter end word: ";
    cin >> end_word;

    vector<string> ladder = generate_word_ladder(start_word, end_word, word_list);
    print_word_ladder(ladder);

    return 0;
}
