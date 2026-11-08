//
// Created by lucyn on 11/7/2026.
//

#ifndef DSA_P2_LETTER_LEAP_TRIE_H
#define DSA_P2_LETTER_LEAP_TRIE_H
#include <array>
#include <string>
#include <vector>

using namespace std;

struct TrieNode {
    array<TrieNode*, 26> children;
    bool isWord;

    TrieNode() : isWord(false) {
        children.fill(nullptr);
    }
};

class Trie {
private:
    TrieNode* root;
public:
    Trie() {
        root = new TrieNode();
    }
    bool isLeaf;
    void insert(const string& key);
    bool search(const string &target) const;
    vector<string> neighbors(const string &current) const;
    string hint(const string &current, const string &target) const;
};


#endif //DSA_P2_LETTER_LEAP_TRIE_H
