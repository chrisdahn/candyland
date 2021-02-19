/*
Plays 2 player games of Candyland for the purposes of doing an empirical study to confirm or refute the
mathematical study found at:
http://www.lscheffer.com/CandyLand.htm
*/

#include <candyland.h>
#include <common.h>

void usage()
{
    cout << "Usage:" << endl;
    cout << "  candyland -c <game count> [-d]" << endl << endl;
    cout << "Where:" << endl;
    cout << "-d  Print debug statements." << endl;
}

int main(int argc, char **argv)
{
    bool debug = false;
    unsigned long long game_count = 0;
    Board *board;

    for (int arg = 1; arg < argc; arg++)
    {
        if (string(argv[arg]).compare("-h") == 0)
        {
            usage();
            return 0;
        }

        if (string(argv[arg]).compare("-d") == 0) debug = true;
        if (string(argv[arg]).compare("-c") == 0) game_count = stoull(string(argv[++arg]));
    }

    if (game_count == 0) 
    {
        usage();
        return 1;
    }

    if (debug) cout << "Configured for [" << game_count << "] games and debugging output enabled" << endl;

    board = new Board(debug);

    for (unsigned long long games = 1; games <= game_count; games++)
    {
        if (debug) cout << "Beginning Game " << games << endl;
        board->play_game();
    }

    delete board;
    return 0;
}
