#ifndef __DECK_H
#define __DECK_H

#include <stdlib.h>

#include <deque>
#include <string>
using namespace std;

class Deck 
{
    public:
        Deck(bool);

        void shuffle();
        char draw();
        bool is_double(const char card);
        bool is_special(const char card);
        void reset();

    private:
        void _init_cards();
        void _debug(string);

        unsigned int _max_fans;
        unsigned int _shuffles;
        static const char _special_colors[7];
        bool _debugging;
        deque<char> _cards,
                    _discard;
};

#endif
