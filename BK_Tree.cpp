#pragma once

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <cstdlib>
#include <ctime>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

class BK_Tree {
public:
    string lastWord;
    string firstWord;
    string prevWord;
    int letterCount = 0;
    int complexity = 5;
    int maxAttempts = 200;

    BK_Tree() {
        static bool seeded = false;
        if (!seeded) {
            srand(static_cast<unsigned>(time(nullptr)));
            seeded = true;
        }
    }

private:
    struct Node {
        string word;
        map<int, int> children;
        explicit Node(string w) : word(move(w)) {}
    };

    vector<Node> nodes; // nodes[0] is the root (the last word)
    unordered_set<string> dictionary;
    list<string> solution; // firstWord -> ... -> lastWord
    unordered_set<string> usedWords; // words the player has already used
    // Two rand() calls are combined to generate a random word
    // because rand() can max out at 32767, which is too small for some of the files.
    static size_t randomIndex(size_t n) {
        size_t r = (static_cast<size_t>(rand()) << 15) | static_cast<size_t>(rand());
        return r % n;
    }

    /* Because all words in the tree have the same length, we can use Hamming distance instead of
     * Levenshtein distance for a more optimal solution.
     */
    static int distance(const string &a, const string &b) {
        if (a.size() != b.size()) return static_cast<int>(max(a.size(), b.size()));
        int d = 0;
        for (size_t i = 0; i < a.size(); ++i)
            if (a[i] != b[i]) ++d;
        return d;
    }

    void insertNode(const string &word) {
        if (nodes.empty()) {
            nodes.emplace_back(word);
            return;
        }
        int cur = 0;
        while (true) {
            int d = distance(word, nodes[cur].word);
            if (d == 0) return;  // duplicate, ignore
            auto it = nodes[cur].children.find(d);
            if (it == nodes[cur].children.end()) {
                int newIndex = static_cast<int>(nodes.size());
                nodes.emplace_back(word);
                nodes[cur].children[d] = newIndex;
                return;
            }
            cur = it->second;
        }
    }

    vector<string> search(const string &query, int tolerance) const {
        vector<string> results;
        if (nodes.empty()) return results;

        vector<int> stack{0};
        while (!stack.empty()) {
            int index = stack.back();
            stack.pop_back();
            const Node &n = nodes[index];

            int d = distance(query, n.word);
            if (d <= tolerance) results.push_back(n.word);

            // Triangle inequality: only children with edge in [d - tol, d + tol] can match.
            auto low = n.children.lower_bound(d - tolerance);
            auto high = n.children.upper_bound(d + tolerance);
            for (auto it = low; it != high; ++it) stack.push_back(it->second);
        }
        return results;
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
        dictionary.clear();

        ifstream in("letter" + to_string(numLetters) + ".txt");
        if (!in) {
            cerr << "Could not open letter" << numLetters << ".txt\n";
            return words;
        }
        string w;
        while (getline(in, w)) {
            if (cleanWord(w) && static_cast<int>(w.size()) == numLetters &&
                dictionary.insert(w).second) {
                words.push_back(w);
            }
        }
        return words;
    }

    void buildTree(const string &root, vector<string> &words) {
        nodes.clear();
        nodes.reserve(words.size());
        insertNode(root);
        for (size_t i = words.size(); i > 1; --i)
            swap(words[i - 1], words[randomIndex(i)]);
        for (const auto &w : words) insertNode(w);
    }

    bool buildSolution(const string &root) {
        solution.clear();
        unordered_set<string> inSolution;

        solution.push_back(root);
        inSolution.insert(root);
        string current = root;

        for (int step = 0; step < complexity; ++step) {
            vector<string> candidates;
            for (const auto &w : search(current, 1)) {
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
    bool generateLastWord(int numLetters) {
        /* Logic:
        *  Step 0: Directional linked list "solution" hold each word in the following sequence. This way, solution can be returned later to display a valid solution in game.
        *  Step 1: The last word is set as the BK tree's root. Randomly select a word from "letter<numLetters>.txt" as the last word and add it to <solution>.
        *  Step 2: Randomly choose a next word until landing on one that has a distance of 1 away from the root.
        *          This becomes the new root IF it is not in <solution>. No duplicate words.
        *  Step 3: Repeat step 2 <complexity> times to ensure there is enough change between the first and last word.
        *  Step 4: The final word generated randomly is the user's starting word, or first word. This is an instance of a completed solution.
        *  Step 5: Since this is the beginning of the program, prevWord is assigned to firstWord.
        */

        letterCount = numLetters;
        vector<string> words = loadWords(numLetters);
        if (words.empty()) {
            return false;
        }

        for (int attempt = 0; attempt < maxAttempts; ++attempt) {
            // Step 1
            lastWord = words[randomIndex(words.size())];
            buildTree(lastWord, words);

            // Steps 2-4
            if (buildSolution(lastWord)) {
                firstWord = solution.front();

                //Step 5:
                prevWord = firstWord;
                usedWords.clear();
                usedWords.insert(firstWord);
                return true;
            }
        }
        return false;
    }

    string getLastWord() {
        return lastWord;
    }

    string getFirstWord() {
        return firstWord;
    }

    const list<string> &getSolution() const {
        return solution;
    }

    string insertWord(string word) {
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
        if (!dictionary.count(word)) {
            return "invalid word";
        }
        // Step 3
        vector<string> neighbors = search(prevWord, 1);
        if (find(neighbors.begin(), neighbors.end(), word) == neighbors.end()) {
            return "invalid swap";
        }

        // Step 4
        prevWord = word;
        usedWords.insert(word);
        return "valid";
    }
};



