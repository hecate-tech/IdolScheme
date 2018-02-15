#include "../include/BeatMapReader.h"

///////////////////////////////////////////////////////////////
   /////////////////      Constructor      ///////////////
///////////////////////////////////////////////////////////////

BeatMapReader::BeatMapReader() {
#ifdef TARGET_WIN32
	vector<string> directories = getBeatMapDirectories("bin\\beatmaps\\");
#else // UNIX SYSTEMS
	vector<string> directories = getBeatMapDirectories("beatmaps/");
#endif //!TARGET_WIN32

	for (int i = 0; i < directories.size(); i++) {
		// for debugging purposes the loop goes through every
		// beatmap available in the directory and loads them all.
		beatMaps.push_back(setNoteParameters(directories.at(i)));
	}
	for (beatMap bm : beatMaps) {
		std::cout << "BeatMap: " + bm.name << std::endl << std::endl;
		for (int j = 0; j < bm.noteParams.size(); j++) {
			std::cout << "Note: " + ofToString(j + 1) + " : line " + ofToString(bm.noteParams.at(j).lineNum) << std::endl;
			std::cout << "bpm: " + ofToString(bm.noteParams.at(j).bpm) << std::endl;
			std::cout << "off: " + ofToString(bm.noteParams.at(j).offset) << std::endl;
			std::cout << "len: " + ofToString(bm.noteParams.at(j).length) << std::endl << std::endl;
		}
	}
	std::cout << "BeatMaps Loaded!" << std::endl << std::endl;
}

/////////////////////////////////////////////////////////////////
   /////////////////      Getters/Setters      ///////////////
/////////////////////////////////////////////////////////////////

vector<string> BeatMapReader::getBeatMapDirectories(const string &path) {
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
beatMap BeatMapReader::setNoteParameters(string path) {
	ifstream infile;
	size_t pos = 0;
	int lineNum = 1;
	bool nameCheck = false;
	string rawText;
	beatMap result;

	infile.open(path);
	
	auto pb_Element = [&](string str) {
		if (!result.noteParams.empty()) {
			for (noteInfo &a : result.noteParams) {
				if (a.lineNum == lineNum) {
					a.args.push_back(str);
					if (a.args.size() > 3)
						a.convert();
				}
			}
		}
	};

	while (!infile.eof()) {
		getline(infile, rawText);

		if (rawText.find_first_not_of(' ') != string::npos
			&& rawText.compare(0, commentPrefix.size(), commentPrefix)) {

			for (int i = 0; i < rawText.length(); i++) {
				if (rawText[i] == ' ') {
					rawText.erase(remove(rawText.begin(), rawText.end(), ' '), rawText.end());
				}
			}

			while ((pos = rawText.find(delimiter)) != string::npos) {
				if (!rawText.substr(0, pos).compare(0, noteText.size(), noteText)) {
					result.noteParams.push_back(noteInfo(lineNum));
				}
				else if (!rawText.substr(0, pos).compare(0, nameText.size(), nameText)) {
					nameCheck = true;
				}

				pb_Element(rawText.substr(0, pos));
				rawText.erase(0, pos + delimiter.length());
			}
			pb_Element(rawText);

			if (nameCheck) {
				string temp = rawText;
				char c;
				for (int i = 0; i < temp.length(); i++) {
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