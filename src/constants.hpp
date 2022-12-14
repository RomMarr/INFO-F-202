#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#include "point.hpp"

#include <FL/Fl.H>
#include <string>

using namespace std;

const string WINDOW_TITLE = "Sokoban";
const int REFRESH_RATE = 60; // Frames per seconds

// LOADING SCREEN
const double LOADING_SCREEN_TIMEOUT = 1.0; // seconds
const string LOADING_TITLE = "SOKOBAN";
const string LOADING_AUTHORS = "By Romain Markowitch & Pol Marnette";

// LEVEL SELECTOR
const string PLAY_BUTTON_TITLE = "Play";
const int NUMBER_OF_LEVELS = 6;

// IN GAME
const string WIN_TITLE = "Gagné";
const string LOST_TITLE = "Perdu";
const string RESET_BUTTON_TITLE = "Reset level";
const string CHANGE_LEVEL_BUTTON_TITLE = "Change level";

// COLORS
const Fl_Color PLAYER_COLOR = fl_rgb_color(0, 0, 255);
const Fl_Color BLOCK_WALL_COLOR = fl_rgb_color(0, 0, 0);
const Fl_Color BLOCK_FLOOR_COLOR = fl_rgb_color(224, 224, 224);
const Fl_Color BLOCK_TARGET_COLOR = fl_rgb_color(255, 204, 153);
const Fl_Color BLOCK_TELEPORTER_COLOR = fl_rgb_color(153, 0, 153);
const Fl_Color BLOCK_LIGHT_BOX_COLOR = fl_rgb_color(204, 102, 0);
const Fl_Color BLOCK_HEAVY_BOX_COLOR_NORMAL = fl_rgb_color(102, 51, 0);
const Fl_Color BLOCK_HEAVY_BOX_COLOR_GREEN = fl_rgb_color(35, 78, 20);
const vector<const Fl_Color> BLOCK_HEAVY_BOX_COLORS{BLOCK_HEAVY_BOX_COLOR_NORMAL, BLOCK_HEAVY_BOX_COLOR_GREEN};

// WEIGHTS
const int HEAVY_BOX_WEIGHT = 9;
const int LIGHT_BOX_WEIGHT = 3;
const int MAX_PLAYER_WEIGHT = 10;

// POSSIBLE MOVES
const Point POSSIBLE_MOVE_RIGHT{1, 0};
const Point POSSIBLE_MOVE_LEFT{-1, 0};
const Point POSSIBLE_MOVE_UP{0, -1};
const Point POSSIBLE_MOVE_DOWN{0, 1};
#endif