#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#include <FL/Fl.H>
#include <string>

using namespace std;

const char * WINDOW_TITLE = "Sokoban";

// LOADING SCREEN
// const string LOADING_TITLE = "SOKOBAN";
// const string LOADING_AUTHORS = "By Romain Markowitch & Pol Marnette";

// LEVEL SELECTOR
const string PLAY_BUTTON_TITLE = "Change level";


// IN GAME
const string WIN_TITLE = "Gagné";
const string LOST_TITLE = "Perdu";
const string RESET_BUTTON_TITLE = "Reset level";
const string CHANGE_LEVEL_BUTTON_TITLE = "Change level";

// COLORS
const Fl_Color PLAYER_COLOR = fl_rgb_color(0, 0, 255);

#endif