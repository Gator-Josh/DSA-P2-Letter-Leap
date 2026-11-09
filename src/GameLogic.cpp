//
// Created by Lucia Novo on 11/8/26.
//

#include <list>
#include <string>
#include <vector>

#ifndef DSA_P2_LETTER_LEAP_GAMELOGIC_CPP
#define DSA_P2_LETTER_LEAP_GAMELOGIC_CPP
using namespace std;

class GameLogic {
    public:
        virtual ~GameLogic() = default;
        virtual bool generateLastWord(int num_letters) = 0;
        virtual string getLastWord() = 0;
        virtual string getFirstWord() = 0;
        virtual const list<string> &getSolution() const = 0;
        virtual string insertWord(string word) = 0;
};

#endif //DSA_P2_LETTER_LEAP_GAMELOGIC_CPP
