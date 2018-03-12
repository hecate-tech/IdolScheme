#include "../include/BeatMapHandler.h"

void BeatMapHandler::get_all(const fs::path &root, const string &ext, vector<fs::path> &ret) {
	if (!fs::exists(root) || !fs::is_directory(root))
		return;
	
	/// iterators
	/// ---------
	fs::recursive_directory_iterator it(root);
	fs::recursive_directory_iterator endit;

	/// while there are still files
	/// ---------------------------
	while (it != endit) {
		if (fs::is_regular_file(*it) && it->path().extension() == ext)
			ret.push_back(it->path());

		++it;
	}
}

int BeatMapHandler::get_tagnum(const string &tag, ofXml &map) {
	int res = 0;
	std::size_t f;
	
	for (int i = 0; i < map.getNumChildren(); i++) {
		map.setToChild(i);
		f = map.getName().find(tag);
		if (f != string::npos) res++; // if the desired tag is found within the parameters.
		map.setToParent(1);
	}
	return res;
}

void BeatMapHandler::get_notevals(ofXml map, note_info &ret) {
	std::size_t f = map.getName().find("note");
	int sectionNum = BeatMapHandler::get_tagnum("section", map);

	for (int i = 0; i < sectionNum; i++) {
		map.setTo("section[" + ofToString(i) + "]");
		int noteNum = BeatMapHandler::get_tagnum("note", map);

		for (int j = 0; j < noteNum; j++) {
			map.setTo("note[" + ofToString(j) + "]");
			
			for (int k = 0; k < map.getNumChildren(); k++) {
				map.setToChild(k);
				
				if (map.getNumChildren() == 0) {
					ret[i][j][k].first = map.getName();
					ret[i][j][k].second = map.getValue();
				}
				else {
					map.setToChild(0);
					ret[i][j][k].first = map.getName();
					ret[i][j][k].second = map.getValue();
					map.setToParent(1);
				}

				map.setToParent(1);
			}

			map.setToParent(1);
		}

		map.setToParent(1);
	}
}

void BeatMapHandler::readBeatMaps() {
	vector<fs::path> paths;
	map<int, vector<string>> noteInfo;

	// Reads all beatmaps and stores them into 'paths'
	get_all(ofToDataPath("beatmaps"), ".xml", paths);

	// for every beatmap file.
	for (unsigned int i = 0; i < paths.size(); i++) {
		/// reading file
		/// ------------
		ofFile file;
		
		file.open(paths.at(i));

		cout << paths.at(i).generic_string() << endl;

		ofBuffer buffer = file.readToBuffer();
		ofXml map;
		map.loadFromBuffer(buffer.getText());
		map.setTo("map"); // sets to root tag

		int sectionNum = BeatMapHandler::get_tagnum("section", map);
		note_info myNoteInfo;
		BeatMapHandler::get_notevals(map, myNoteInfo);

		// for every <section> tag
		for (int j = 0; j < myNoteInfo.size(); j++) {
			cout << "section[" + std::to_string(j) + "]" << endl;
			// for every <note> tag
			for (int k = 0; k < myNoteInfo.at(j).size(); k++) {
				cout << "  note[" + std::to_string(k) + "]" << endl;
				// for every property within the <note>
				for (int l = 0; l < myNoteInfo.at(j).at(k).size(); l++) {
					cout << "    " + myNoteInfo[j][k][l].first + ": " + myNoteInfo[j][k][l].second << endl;
				}
			}
		}
	}
}