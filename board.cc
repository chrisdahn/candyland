#include <board.h>

Board::Board(bool debugging)
{
    _debugging = debugging;
    _deck = new Deck(_debugging);
    _init_board();
}

Board::~Board()
{
    delete _deck;
}

void Board::play_game()
{
    bool done = false;
    unsigned int rounds = 0;

    _deck->reset();
    _deck->shuffle();

    _player1 = _player2 = _board.begin();

    _debug("Let the game begin!");

    while (!done)
    {
        rounds++;

        if (_debugging) cout << "Round " << rounds << endl;

        if (_move_player(_player1, 1))
        {
            cout << "Player 1," << rounds << endl;
            done = true;
        } else if (_move_player(_player2, 2))
        {
            cout << "Player 2," << rounds << endl;
            done = true;
        }
    }
}

bool Board::_move_player(vector<char>::iterator &it, int player)
{
    bool got_double = false;

    if (_debugging) cout << "Taking a turn for Player " << player << endl;

    char card = _deck->draw();
    got_double = _deck->is_double(card);

    if (got_double)
    {
        if (_debugging) cout << "  -> Got double, translating to regular board space [ " << card << " ] ";
        card += 32;
        if (_debugging) cout << "is now [ " << card << " ] " << endl;
    }

    char card_required = _is_stuck(it);

    if (card_required != ' ' && card != card_required)
    {
        _debug("  -> Still stuck..");
        return false;
    }

    bool end = _goto(it, card);
    if (!end && got_double) end = _goto(it, card);

    if (end) return true;

    int shortcut = _check_shortcut(it);
    if (shortcut > 0)
    {
        it = _board.begin() + shortcut;
        if (_debugging) cout << "  -> Finished shortcut, now at space [" << *it << "] (" << _current_position(it) << ")" << endl;
    }

    return false;
}

int Board::_current_position(vector<char>::iterator &player)
{
    return (player - _board.begin());
}

bool Board::_goto(vector<char>::iterator &player, char space)
{
    if (_debugging) cout << "  -> Moving from space [" << *player << "] (" << _current_position(player) << ") to space [" << space << ']' << endl;

    if (_deck->is_special(space))
    {
        _debug("  -> Sending player to special location..");
        player = _board.begin();

        if (space == candy_hearts) player += _candy_hearts;
        else if (space == peppermint_forest) player += _peppermint_forest;
        else if (space == gingerbread_tree) player += _gingerbread_tree;
        else if (space == gumdrop_mountains) player += _gumdrop_mts;
        else if (space == peanutbrittle_house) player += _brittle_house;
        else if (space == lollypop_woods) player += _lollypop_woods;
        else if (space == icecream_floats) player += _icecream_floats;
        else {
            cerr << "ERROR: You asked me to go to special location [" << space << "], but I don't what that is! MAARON!" << endl;
            exit(1);
        }
    } else
    {
        player++;
        while (_current_position(player) != _win_position && *player != space)
        {
            player++;
        }
    }

    if (_debugging) cout << "  -> Now at space [" << *player << "] (" << _current_position(player) << ")" << endl;

    if (_current_position(player) == _win_position) return true;
    return false;
}

char Board::_is_stuck(vector<char>::iterator &player)
{
    _debug("  -> Checking if player is on a sticky spot..");

    int pos = _current_position(player);

    if (pos == _blue_cherry_pitfall)
    {
        _debug("  -> Oh no! You're in Cherry Pitfall, can't leave until a 'b' is drawn");
        return 'b';
    } else if (pos == _red_cherry_pitfall)
    {
        _debug("  -> Oh no! You're in Cherry Pitfall, can't leave until an 'r' is drawn");
        return 'r';
    } else if (pos == _molasses_swamp)
    {
        _debug("  -> Oh no! You're in Molasses Swamp, can't leave until a 'b' is drawn");
        return 'b';
    }

    return ' ';
}

int Board::_check_shortcut(vector<char>::iterator &player)
{
    _debug("  -> Checking if player is on a shortcut space..");

    int pos = _current_position(player);

    if (pos == _rainbow_start)
    {
        _debug("  -> HUZZAH! Player is on the start of the Rainbow Bridge!");
        return _rainbow_end;
    } else if (pos == _mountain_pass_start)
    {
        _debug("  -> HUZZAH! Player is on the start of Gumdrop Mountain Pass!");
        return _mount_pass_end;
    }

    return 0;
}

void Board::_init_board()
{
    _debug("Initializing board..");

    _board.push_back('*');

    // The board I'm using has 136 spaces. 129 regular colors, and 7 "special" spaces, such as Candy Hearts
    for (int numberofbagels = 0; numberofbagels < _win_position - total_special_colors; numberofbagels++)
    {
        _board.push_back(board_colors[numberofbagels%total_board_colors]);
    }

    _board.insert(_board.begin() + _candy_hearts, candy_hearts);
    _board.insert(_board.begin() + _peppermint_forest, peppermint_forest);
    _board.insert(_board.begin() + _gingerbread_tree, gingerbread_tree);
    _board.insert(_board.begin() + _gumdrop_mts, gumdrop_mountains);
    _board.insert(_board.begin() + _brittle_house, peanutbrittle_house);
    _board.insert(_board.begin() + _lollypop_woods, lollypop_woods);
    _board.insert(_board.begin() + _icecream_floats, icecream_floats);

    if (_debugging)
    {
        int count = 0;
        for (vector<char>::iterator it = _board.begin(); it != _board.end(); it++)
        {
            cout << "Board position " << count << ": " << *it << endl;
            count++;
        }
    }
}

void Board::_debug(string msg)
{
    if (_debugging)
    {
        cout << msg << endl;
    }
}
