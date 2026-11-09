//
// Created by lucyn on 11/7/2026.
//

#ifndef DSA_P2_LETTER_LEAP_TRIE_CPP
#define DSA_P2_LETTER_LEAP_TRIE_CPP
#include <algorithm>
#include <array>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <unordered_set>
#include <vector>
#include "GameLogic.cpp"

using namespace std;

struct TrieNode {
    array<TrieNode*, 26> children;
    bool isWord;

    TrieNode() : isWord(false) {
        children.fill(nullptr);
    }
};

class Trie : public GameLogic {
public:
    string lastWord;
    string firstWord;
    string prevWord;
    int letterCount = 0;
    int complexity = 5;
    int maxAttempts = 200;

	Trie() {
        static bool seeded = false;
        if (!seeded) {
            srand(static_cast<unsigned>(time(nullptr)));
            seeded = true;
        }
		root = new TrieNode();
    }

	~Trie() {
		destroy(root);
	}

	Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;

private:
	TrieNode* root;
	list<string> solution;
	unordered_set<string> usedWords;

	 void destroy(TrieNode* node) {
        if (node == nullptr) return;
        for (TrieNode* child : node->children) {
            destroy(child);
        }
        delete node;
    }

	void clear() {
        destroy(root);
		root = new TrieNode();
	}

	static size_t randomIndex(size_t n) {
        size_t r = (static_cast<size_t>(rand()) << 15) | static_cast<size_t>(rand());
        return r % n;
    }

	static bool cleanWord(string &w) {
		size_t s = w.find_first_not_of(" \t\r\n");
        if (s == string::npos) return false;
        size_t e = w.find_last_not_of(" \t\r\n");
        w = w.substr(s, e - s + 1);
        for (char &c : w) {
            c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
            if (c < 'a' || c > 'z') return false;
        }
        return true;
	}

	vector<string> loadWords(int numLetters) {
        vector<string> words;
        clear();

        ifstream in("letter" + to_string(numLetters) + ".txt");
        if (!in) {
            cerr << "Could not open letter" << numLetters << ".txt\n";
            return words;
        }
        string w;
        while (getline(in, w)) {
            if (cleanWord(w) && static_cast<int>(w.size()) == numLetters && !search(w)) {
				insert(w);
                words.push_back(w);
            }
        }
        return words;
    }

	bool buildSolution(const string &root) {
        solution.clear();
        unordered_set<string> inSolution;

        solution.push_back(root);
        inSolution.insert(root);
        string current = root;

        for (int step = 0; step < complexity; ++step) {
            vector<string> candidates;
            for (const auto &w : neighbors(current)) {
                if (!inSolution.count(w)) candidates.push_back(w);  // no duplicates allowed
            }
            if (candidates.empty()) return false;  // dead end

            const string &pick = candidates[randomIndex(candidates.size())];
            solution.push_front(pick);  // front is closer to the player's starting word
            inSolution.insert(pick);
            current = pick;
        }
        return true;
    }

	public:
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
        /*  Step 1: Load letter<numLetters>.txt into the trie and pick a random word as lastWord.
         *  Step 2: Walk randomly to a neighbor not already in <solution>, <complexity> times.
         *  Step 3: The final word reached becomes firstWord (front of <solution>).
         *  Step 4: prevWord starts as firstWord.
         */
        letterCount = num_letters;
        vector<string> words = loadWords(num_letters);
        if (words.empty()) {
            return false;
        }

		for (int attempt = 0; attempt < maxAttempts; ++attempt) {
			// Step 1
			lastWord = words[randomIndex(words.size())];

			// Steps 2-4
			if (buildSolution(lastWord)) {
				firstWord = solution.front();

				// Step 5:
				prevWord = firstWord;
				usedWords.clear();
				usedWords.insert(firstWord);
				return true;
			}
		}
		return false;
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
        /* Logic:
         *
         * Insert word is called by the front-end GUI and returns a string to indicate why the word is invalid or that it is valid.
         * If insertWord is valid, the GUI should check if word = lastWord (the user has completed the letter leap).
         * Note: When GUI calls this method it should first set the user's input to lowercase.
         *
         * Step 1: Check if word is of valid length, is not the same as any previously used word, and is not the same as firstWord.
         * Step 2: Check if word exists in letter<numLetter>.txt.
         * Step 3: Check if word is 1 letter swap away from prevWord using BK tree.
         * Step 4: The word meets all validation requirements so update prevWord and return "valid".
        */
        // Step 1
        if (static_cast<int>(word.length()) != letterCount) {
            return "invalid length";
        }
        if (word == firstWord || word == prevWord || usedWords.count(word)) {
            return "redundant";
        }
        // Step 2
        if (!search(word)) {
            return "invalid word";
        }
        // Step 3
        vector<string> adjacent = neighbors(prevWord);
        if (find(adjacent.begin(), adjacent.end(), word) == adjacent.end()) {
            return "invalid swap";
        }

        // Step 4
        prevWord = word;
        usedWords.insert(word);
        return "valid";
    }
};



#endif //DSA_P2_LETTER_LEAP_TRIE_CPP
