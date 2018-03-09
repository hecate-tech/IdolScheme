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

void BeatMapHandler::get_notevals(const int &bmnum, ofXml map, vector<string> &ret) {
	map.setToChild(bmnum);

	auto find_tag = [&](const string tag) {
		vector<int> res;
		std::size_t ff;
		for(int i = 0; i < map.getNumChildren(); i++) {
			map.setToChild(i);
			ff = map.getName().find(tag);
			if(ff != string::npos) {
				res.push_back(i);
			}
			map.setToParent(1);
		}
		return res;
	};

	std::size_t f = map.getName().find("note");
	vector<int> sectionNums = find_tag("section");
	
	for(int a : sectionNums) {
		cout << "section[" + ofToString(a) + "]" << endl;
	}

	/*for(int i = 0; f == string::npos && i < map.getNumChildren(); f = map.getName().find("note"), i++) {
		map.setToChild(i);
		cout << endl << "note[" + ofToString(i) + "]" << endl;

		for(int j = 0; j < map.getNumChildren(); j++) {
			map.setToChild(j);
			cout << map.getName() + ": " << map.getValue() << endl;
			map.setToParent(1);
		}

		map.setToParent(1);
	}*/
}

void BeatMapHandler::readBeatMaps() {
	vector<fs::path> paths;
	map<int, vector<string>> noteInfo;

	// Reads all beatmaps and stores them into 'paths'
	get_all(ofToDataPath("beatmaps"), ".xml", paths);
	
	for (unsigned int i = 0; i < paths.size(); i++) {
		ofFile file;
		
		file.open(paths.at(i));

		cout << paths.at(i).generic_string() << endl;

		ofBuffer buffer = file.readToBuffer();
		
		ofXml map;
		map.loadFromBuffer(buffer.getText());
		map.setTo("map"); // sets to root tag

		// for every <beatmap> tag
		for(int j = 0; j < map.getNumChildren(); j++) {
			map.setToChild(j); // goes inward one lvl

			// if the child is a beatmap
			std::size_t f = map.getName().find("beatmap");
			if(f != string::npos) {
				cout << "Beatmap[" + ofToString(j) + "]" << map.getNumChildren() << endl;
				vector<string> vals;
				BeatMapHandler::get_notevals(j, map, vals);

				/*for(int k = 0; k < map.getNumChildren(); k++) {
					map.setToChild(k); // goes inward one lvl
					
					if(map.getNumChildren() == 0)
						cout << "Bm[" + ofToString(j) + "]:  " << map.getName() + "[" +  ofToString(k) + "] = " + map.getValue() << endl;
					
					for(int l = 0; l < map.getNumChildren(); l++) {
						map.setToChild(l); // goes inward one lvl

						std::size_t fn = map.getName().find("note");
						if(fn != string::npos) {
							for(int n = 0; n < map.getNumChildren(); n++) {
								map.setToChild(n);
								cout << map.getName() + "[" + ofToString(n) + "]:  " << map.getValue() << endl;
								map.setToParent(1);
							}
						} else {
							cout << "Bm[" + ofToString(j) + "]:     ";
							cout << map.getName() + "[" + ofToString(l) + "] = ";
							cout << map.getValue() <<  endl;
						}
						
						map.setToParent(1); // goes backward one lvl
					}

					map.setToParent(1); // goes backward one lvl
				}*/
			}

			map.setToParent(1); // goes backward one lvl
		}
		//cout << map.getName() << endl;
	}
}