#pragma once

#ifndef ERRORCODES_H
#define ERRORCODES_H

namespace error_codes { // find error codes easier with a namespace

#define BAD_COORDINATE -97852563948
#define BAD_LENGTH -93402564

	enum IdolSchemeErrorCodes {
		BUTTON_INVALID = 199,
		GAME_LOAD_SCRIPT,
		GAME_LOAD_BACKGROUND,
		GAME_LOAD_BEATMAP,
		GAME_LOAD_SONG,
		GAME_LOAD_MENU,
		GAME_SAVE_SETTINGS,
	};
	enum NoteErrorCodes {
		NOTE_BADTYPE = 99,
		NOTE_INVALID,
		NOTE_TIMEROFF,
	};
}

#endif //!ERRORCODES_H