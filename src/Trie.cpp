//
// Created by lucyn on 11/7/2026.
//

#include "Trie.h"

#include <string>
#include <vector>
using namespace std;

void Trie::insert(const string& target) {

    TrieNode* curr = this->root;

    for (char c : target) {
        int index = c - 'a';
        if (curr->children[index] == nullptr) {
            curr->children[index] = new TrieNode();
        }
        curr = curr->children[index];
    }
    curr->isWord = true;
};

bool Trie::search(const string& target) const {
    TrieNode* current = this->root;
    for (char c : target) {
        int index = c - 'a';
        if (current->children[index] == nullptr) {
            return false;
        }
        current = current->children[index];
    }
    return current->isWord;
}

vector<string> Trie::neighbors(const string& word) const {
    vector<string> result;
    string candidate = word;

    for (size_t i = 0; i < word.size(); i++) {
        char original = word[i];
        for (char c = 'a'; c <= 'z'; c++) {
            if (c == original) {
                continue;
            }
            candidate[i] = c;
            if (search(candidate)) {
                result.push_back(candidate);
            }
        } candidate[i] = original;
    } return result;
}
