#include "ladder.h"

// Error handling function
void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " [" << word1 << ", " << word2 << "]" << endl;
    exit(1);
}

// Load words from words.txt into a set (dictionary)
void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << file_name << endl;
        exit(1);
    }

    string word;
    while (file >> word) {
        word_list.insert(word);
    }
    file.close();
}

// Check if edit distance between two words is 1
bool edit_distance_within(const string& str1, const string& str2, int d) {
    int m = str1.size();
    int n = str2.size();

    if (abs(m - n) > d) return false; // If length difference is more than d, return false

    int edits = 0, i = 0, j = 0;
    while (i < m && j < n) {
        if (str1[i] != str2[j]) {
            if (++edits > d) return false;

            if (m > n) i++;
            else if (m < n) j++;
            else { i++; j++; }
        } else {
            i++; j++;
        }
    }
    if (i < m || j < n) edits++; // Account for any trailing letters

    return edits <= d;
}

// Wrapper for checking adjacency (edit distance == 1)
bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

// Generate the word ladder using BFS
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        error(begin_word, end_word, "Start and end words must be different");
    }
    if (word_list.find(end_word) == word_list.end()) {
        error(begin_word, end_word, "End word not found in dictionary");
    }

    queue<vector<string>> ladder_queue;
    set<string> visited;

    ladder_queue.push({begin_word});
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();

        for (const string& word : word_list) {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                if (word == end_word) {
                    return new_ladder;
                }
                ladder_queue.push(new_ladder);
                visited.insert(word);
            }
        }
    }
    return {}; // No ladder found
}

// Print the word ladder
void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
    } else {
        for (size_t i = 0; i < ladder.size(); ++i) {
            cout << ladder[i];
            if (i != ladder.size() - 1) cout << " -> ";
        }
        cout << endl;
    }
}

// Test function
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");

    auto my_assert = [](bool e) { cout << (e ? " passed" : " failed") << endl; };

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
