/************************************************
 *                  IdolScheme                  *
 ************************************************/

#ifndef IDOLSCHEME_H
#define IDOLSCHEME_H

/// Includes
/// --------

#include <iostream>

/// Globals
/// -------


/// Represents the current state of the game
/// ----------------------------------------
enum IdolSchemeStates {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN,
    GAME_LOSE,
    GAME_PAUSE,
};


/*************************************************
 * `IdolScheme` holds all the game related states
 * and functionality. It combines all game-related
 * data into a single class for easy access of the
 * components and manageability.
 *************************************************/
class IdolScheme {
    /// Game settings
    /// -------------
    IdolSchemeStates State;
    unsigned int Width, Height;
    

    /// Constructor/Destructor
    /// ----------------------
    IdolScheme(unsigned int width_, unsigned int height_);
    ~IdolScheme();

    /// Initialized game state (load all shaders/textures/beatmaps)
    /// -----------------------------------------------------------
    void Init();

    /// Game loop
    /// ---------
    void ProcessInput(float deltaTime);
    void Update(float deltaTime);
    void Render();
};

#endif //!IDOLSCHEME_H