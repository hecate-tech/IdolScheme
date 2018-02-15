#include "../include/BeatMapHandler.h"

///////////////////////////////////////////////////////////////
   /////////////////      Constructor      ///////////////
///////////////////////////////////////////////////////////////

BeatMapHandler::BeatMapHandler() {
#ifdef TARGET_WIN32
	vector<string> directories = getBeatMapDirectories("bin\\beatmaps\\");
#else // UNIX SYSTEMS
	vector<string> directories = getBeatMapDirectories("beatmaps/");
#endif //!TARGET_WIN32

	for (unsigned int i = 0; i < directories.size(); i++) {
		// for debugging purposes the loop goes through every
		// beatmap available in the directory and loads them all.
		beatMaps.push_back(setNoteParameters(directories.at(i)));
	}
	/// debug beatmap printing
	for (beatMap bm : beatMaps) {
		std::cout << "BeatMap: " + bm.name << std::endl << std::endl;
		for (unsigned int j = 0; j < bm.noteParams.size(); j++) {
			std::cout << "Note: " + ofToString(j + 1) + " : line " + ofToString(bm.noteParams.at(j).lineNum) << std::endl;
			std::cout << "bpm:  " + ofToString(bm.noteParams.at(j).bpm) << std::endl;
			std::cout << "off:  " + ofToString(bm.noteParams.at(j).offset) << std::endl;
			std::cout << "len:  " + ofToString(bm.noteParams.at(j).length) << std::endl;
			std::cout << "type: " + ofToString(bm.noteParams.at(j).type) << std::endl;
			std::cout << "btn:  " + ofToString(bm.noteParams.at(j).button) << std::endl << std::endl;
		}
	}
	std::cout << "BeatMaps Loaded!" << std::endl << std::endl;
}

/////////////////////////////////////////////////////////////////
   /////////////////      Getters/Setters      ///////////////
/////////////////////////////////////////////////////////////////

vector<string> BeatMapHandler::getBeatMapDirectories(const string &path) {
	vector<string> fileList;

	if (!path.empty()) {
		filesystem::path apkPath(path);
		filesystem::recursive_directory_iterator end;

		for (filesystem::recursive_directory_iterator i(apkPath); i != end; ++i) {
			const filesystem::path cp = (*i);
			fileList.push_back(cp.string());
		}
	}

	return fileList;
}

//-------------------------------------------------------
beatMap BeatMapHandler::setNoteParameters(string path) {
	ifstream infile; // the file that's being read
	size_t pos = 0;  // which section of text you're on
	int lineNum = 1; // line number
	bool nameCheck = false; // checks if you're setting beatmap name
	string rawText; // the raw text in each line
	beatMap result;

	/// opens text file
	infile.open(path);
	
	/// lambda to push strings into note objects.
	auto pb_Element = [&](string str) {
		if (!result.noteParams.empty()) {
			for (noteInfo &a : result.noteParams) {
				if (a.lineNum == lineNum) {
					a.args.push_back(str);
					if (a.args.size() > 5) // if enough arguments to make a note.
						a.convert();
				}
			}
		}
	};

	while (!infile.eof()) {
		getline(infile, rawText); // one line of text

		/// check if it's not whitespace or a comment.
		if (rawText.find_first_not_of(' ') != string::npos
			&& rawText.compare(0, commentPrefix.size(), commentPrefix)) {
			
			for (unsigned int i = 0; i < rawText.length(); i++) {
				if (rawText[i] == ' ') { // removes all whitespace
					rawText.erase(remove(rawText.begin(), rawText.end(), ' '), rawText.end());
				}
			}

			/// while it can find more delimiters
			while ((pos = rawText.find(delimiter)) != string::npos) {
				if (!rawText.substr(0, pos).compare(0, noteText.size(), noteText)) { // if there's "note"
					result.noteParams.push_back(noteInfo(lineNum)); // adds new note
				}
				else if (!rawText.substr(0, pos).compare(0, nameText.size(), nameText)) { // if there's "beatname"
					nameCheck = true; // enable the name check
				}

				pb_Element(rawText.substr(0, pos)); // adds string to 'args'
				rawText.erase(0, pos + delimiter.length()); // erases what it just saved
			}
			pb_Element(rawText); // adds last string to 'args'

			if (nameCheck) {
				string temp = rawText;
				char c;
				for (unsigned int i = 0; i < temp.length(); i++) {
					c = rawText[i];
					if (isupper(c) && i != 0) {
						rawText.insert(i, " ");
						i++;
					}
				}
				result.name = rawText;
				nameCheck = false;
			}

		}
		lineNum++;
	}
	return result;
}