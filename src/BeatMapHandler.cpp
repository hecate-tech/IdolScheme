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

void BeatMapHandler::readBeatMaps() {
	vector<fs::path> paths;
	map<int, vector<string>> noteInfo;

	get_all(ofToDataPath("beatmaps"), ".xml", paths);
	
	for (unsigned int i = 0; i < paths.size(); i++) {
		ofFile file;
		
		file.open(paths.at(i));

		cout << paths.at(i).generic_string() << endl;

		ofBuffer buffer = file.readToBuffer();

		cout << endl << buffer.getText() << endl;
		
		ofXml map;
		map.loadFromBuffer(buffer.getText());
		map.setTo("map"); // sets to root tag

		// for every <beatmap> tag
		cout << map.getName() << endl;
	}
}