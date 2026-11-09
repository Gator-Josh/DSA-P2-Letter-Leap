//
// Created by lucyn on 11/8/2026.
//

#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cctype>


using namespace std;

std::vector<string> loadWords(const std::string& path, int length);

vector<string> loadWords(const std::string& path, int length) {
    vector<string> words;
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "Unable to open file " << path << endl;
        return words;
    }

    string line;
    while (file >> line) {
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        bool valid = (int)line.size() == length && all_of(line.begin(), line.end(), [](char c) {
            return c >= 'a' && c <= 'z';
        });
        if (valid) { words.push_back(line); }
    }
    return words;
}
