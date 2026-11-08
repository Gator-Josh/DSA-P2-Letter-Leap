//
// Created by lucyn on 11/7/2026.
//

#ifndef DSA_P2_LETTER_LEAP_TRIE_CPP
#define DSA_P2_LETTER_LEAP_TRIE_CPP
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

class Trie : public GameLogic {
    TrieNode* root;
    string firstWord;
    string lastWord;
    list<string> solution;

    void destroy(TrieNode* node) {
        if (node == nullptr) return;
        for (TrieNode* child : node->children) {
            destroy(child);
        }
        delete node;
    }

public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        destroy(root);
    }

    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;

    void insert(const string& target) {
        TrieNode* curr = this->root;

        for (char c : target) {
            if (c < 'a' || c > 'z') return;  // ignore words with non a-z characters
            int index = c - 'a';
            if (curr->children[index] == nullptr) {
                curr->children[index] = new TrieNode();
            }
            curr = curr->children[index];
        }
        curr->isWord = true;
    }

    bool search(const string& target) const {
        TrieNode* current = this->root;
        for (char c : target) {
            if (c < 'a' || c > 'z') return false;
            int index = c - 'a';
            if (current->children[index] == nullptr) {
                return false;
            }
            current = current->children[index];
        }
        return current->isWord;
    }

    vector<string> neighbors(const string& word) const {
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
            }
            candidate[i] = original;
        }
        return result;
    }

    bool generateLastWord(int num_letters) override {
        return false;  // false = generation failed
    }

    string getLastWord() override {
        return lastWord;
    }

    string getFirstWord() override {
        return firstWord;
    }

    const list<string>& getSolution() const override {
        return solution;
    }

    string insertWord(string word) override {
        return "invalid word";
    }
};



#endif //DSA_P2_LETTER_LEAP_TRIE_CPP
