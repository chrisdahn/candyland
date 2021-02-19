#include <deck.h>
#include <common.h>

Deck::Deck(bool debugging)
{
    _shuffles = 0;
    _max_fans = 10;
    _debugging = debugging;
    _init_cards();
}

char Deck::draw()
{
    _debug("Drawing a card..");
    char card = _cards.front();
    _cards.pop_front();
    _discard.push_back(card);

    if (_cards.empty())
    {
        _debug("Pulled last card, shuffling discard pile..");
        _cards.assign(_discard.begin(), _discard.end());
        _discard.clear();
        shuffle();
    }

    if (_debugging) cout << "  Got " << card << endl;
    return card;
}

void Deck::reset()
{
    _debug("Resetting deck, putting discard back into draw pile.");

    for (deque<char>::iterator disc_it = _discard.begin(); disc_it != _discard.end(); disc_it++)
    {
        _cards.push_back(*disc_it);
    }

    _discard.clear();

    if (_debugging) cout << "Draw pile now has [" << _cards.size() << "] and discard pile has [" << _discard.size() << "]" << endl;
}

// In reality, the distribution of cards apparently differs depending on when the
// game was produced. The one we own has 64 cards. 7 special, 8 blue and red, 7 of
// the other colors. Then there's 3 double blue, and only 2 of the other doubles. So
// for the sake of my own sanity, I'm going to generalize, especially since cards may
// have gone missing from ours..
// 67 cards: 7 special, 60 colors. Each color has 8 single move and 2 double
void Deck::_init_cards()
{
    _debug("Initializing cards..");

    for (int color = 0; color < total_board_colors; color++)
    {
        for (int card_count = 0; card_count < 8; card_count++) _cards.push_back(board_colors[color]);
        _cards.push_back(board_colors[color] - 32);
        _cards.push_back(board_colors[color] - 32);
    }

    for (int color = 0; color < total_special_colors; color++)
    {
        _cards.push_back(special_colors[color]);
    }

    if (_debugging)
    {
        int count = 0;
        for (deque<char>::iterator it = _cards.begin(); it != _cards.end(); it++)
        {
            cout << "Card position " << count << ": " << *it << endl;
            count++;
        }
    }
}

bool Deck::is_double(const char card)
{
    for (int color = 0; color < total_board_colors; color++)
    {
        if (card == (board_colors[color] - 32)) return true;
    }

    return false;
}

bool Deck::is_special(const char card)
{
    for (int color=0; color < total_special_colors; color++)
    {
        if (card == special_colors[color]) return true;
    }

    return false;
}

void Deck::shuffle()
{
    _debug("Shuffling cards..");

    deque<char> left_hand,
                right_hand;
    deque<char>::iterator split_left,
                          split_right;
    int split;

    if (_debugging) cout << "Cards count: " << _cards.size() << endl;

    unsigned int seed = (unsigned int)time(NULL) + _shuffles++;
    if (_debugging) cout << "  -> Using randomizer seed value " << seed << endl;
    srand(seed);

    for (int fan = 0; fan < _max_fans; fan++)
    {
        if (_debugging) cout << "Fan " << fan+1 << " of " << _max_fans << endl;

        split = (_cards.size() / 2) + (rand() % 15);

        if (_debugging) cout << "Split: " << split << endl;

        split_left = _cards.begin();
        split_right = _cards.begin() + split;

        left_hand.assign(split_left, split_right);
        right_hand.assign(split_right, _cards.end());

        split_left = left_hand.begin();
        split_right = right_hand.begin();

        _cards.clear();

        if (_debugging)
        {
            for (;split_left != left_hand.end(); split_left++)
            {
                cout << "Left hand: " << *split_left << endl;
            }
            for (;split_right != right_hand.end(); split_right++)
            {
                cout << "Right hand: " << *split_right << endl;
            }


            split_left = left_hand.begin();
            split_right = right_hand.begin();
        }

        while (! (split_left == left_hand.end() && split_right == right_hand.end()))
        {
            int fan_left = (rand() % 3) + 1,
                fan_right = (rand() % 3) + 1;

            for (int left = 0; left < fan_left && split_left != left_hand.end(); left++)
            {
                _cards.push_back(*split_left);
                split_left++;
            }
            for (int right = 0; right < fan_right && split_right != right_hand.end(); right++)
            {
                _cards.push_back(*split_right);
                split_right++;
            }
        }

        _debug("Splitting deck, swapping halves..");
        split = (_cards.size() / 2) + (rand() % 15);

        split_left = _cards.begin();
        split_right = _cards.begin() + split;

        left_hand.assign(split_left, split_right);
        right_hand.assign(split_right, _cards.end());

        split_left = left_hand.begin();
        split_right = right_hand.begin();

        _cards.assign(split_right, right_hand.end());
        
        for (;split_left != left_hand.end(); split_left++)
        {
            _cards.push_back(*split_left);
        }
    }

    if (_debugging)
    {
        cout << "Final shuffle of deck:" << endl;
        for (deque<char>::iterator it = _cards.begin(); it != _cards.end(); it++)
        {
            cout << *it << endl;
        }

        cout << "Cards count: " << _cards.size() << endl;
    }
}

void Deck::_debug(string msg)
{
    if (_debugging)
    {
        cout << msg << endl;
    }
}
