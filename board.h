#ifndef __BOARD_H
#define __BOARD_H

#include <common.h>
#include <deck.h>

#include <vector>
#include <string>
using namespace std;

/*
This board is based on the version of Candyland that we owned, which was a "retro" edition. I believe it
was supposed to be the same as the original Candyland that was produced. There were a few different boards
released over the years, but they were all essentially the same, just with different designs. A picture
of my specific board can be found at:
http://3.bp.blogspot.com/-Amu5ndVOexA/TyQQ0hN6rYI/AAAAAAAAPOU/csdA7ZkAATg/s640/Candyland+1962+2.jpg
*/
class Board
{
    public:
        Board(bool);
        ~Board();

        void play_game();

    private:
        void _init_board();
        void _debug(string msg);
        bool _goto(vector<char>::iterator& player, char);
        bool _move_player(vector<char>::iterator &player, int player_num);
        int _check_shortcut(vector<char>::iterator& player);
        int _current_position(vector<char>::iterator& player);
        char _is_stuck(vector<char>::iterator &player);

        Deck *_deck;
        vector<char> _board;
        bool _debugging;
        vector<char>::iterator _player1,
                               _player2;

        static const unsigned int _rainbow_start = 5,
                                  _candy_hearts = 8,         // H
                                  _peppermint_forest = 16,   // F
                                  _gingerbread_tree = 29,    // N
                                  _mountain_pass_start = 34,
                                  _gumdrop_mts = 43,         // D
                                  _mount_pass_end = 47,
                                  _blue_cherry_pitfall = 49,
                                  _rainbow_end = 61,
                                  _brittle_house = 76,       // T
                                  _red_cherry_pitfall = 89,
                                  _lollypop_woods = 99,      // L
                                  _icecream_floats = 107,    // I
                                  _molasses_swamp = 123,
                                  _win_position = 136;
};

#endif
