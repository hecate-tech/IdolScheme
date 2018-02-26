#pragma once


#ifndef GAMESTATES_H
#define GAMESTATES_H

/* @brief - GameState
* an easily accessible state that the
* game is currently in. This enum is
* accessible by the entire class and
* used to track where the game is.
*/
enum GameState {
	GAME_ACTIVE,
	GAME_LOSE,
	GAME_WIN,
	GAME_MAINMENU,
	GAME_PAUSEMENU,
	GAME_OPTIONSMENU,
	GAME_CONTROLSMENU,
	GAME_LOAD,
	GAME_ERROR,
};

#endif //!GAMESTATES_H