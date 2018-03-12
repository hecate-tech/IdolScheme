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

bpm_map BeatMapHandler::get_sectionbpm(ofXml &doc) {
	bpm_map res;
	for (int i = 0; i < BeatMapHandler::get_tagnum("section", doc); i++)
		res[i] = doc.getValue("section[" + std::to_string(i) + "]/bpm");
	
	return res;
}

int BeatMapHandler::get_tagnum(const string &tag, ofXml &doc) {
	int res = 0;
	std::size_t f;
	
	for (int i = 0; i < doc.getNumChildren(); i++) {
		doc.setToChild(i);
		f = doc.getName().find(tag);
		if (f != string::npos) res++; // if the desired tag is found within the parameters.
		doc.setToParent(1);
	}
	return res;
}

void BeatMapHandler::get_notevals(ofXml doc, note_info &ret) {
	int sectionNum = BeatMapHandler::get_tagnum("section", doc);

	for (int i = 0; i < sectionNum; i++) {
		doc.setTo("section[" + std::to_string(i) + "]");
		int noteNum = BeatMapHandler::get_tagnum("note", doc);

		for (int j = 0; j < noteNum; j++) {
			doc.setTo("note[" + std::to_string(j) + "]");
			
			for (int k = 0; k < doc.getNumChildren(); k++) {
				doc.setToChild(k);
				
				if (doc.getNumChildren() == 0) {
					ret[i][j][k].first = doc.getName();
					ret[i][j][k].second = doc.getValue();
				}
				else {
					doc.setToChild(0);
					ret[i][j][k].first = doc.getName();
					ret[i][j][k].second = doc.getValue();
					doc.setToParent(1);
				}

				doc.setToParent(1);
			}

			doc.setToParent(1);
		}

		doc.setToParent(1);
	}
}

vector<ofXml> BeatMapHandler::get_xml(vector<fs::path> paths_) {
	vector<ofXml> xmlRes;
	for (unsigned int i = 0; i < paths_.size(); i++) {
		ofFile file;
		file.open(paths_.at(i));

		ofBuffer buffer = file.readToBuffer();
		ofXml doc;
		doc.loadFromBuffer(buffer.getText());
		xmlRes.push_back(doc);
	}
	return xmlRes;
}

void BeatMapHandler::readBeatMaps() {
	vector<fs::path> paths;

	// Reads all beatmaps and stores them into 'paths'
	get_all(ofToDataPath("beatmaps"), ".xml", paths);
	vector<ofXml> xmlDocs = BeatMapHandler::get_xml(paths);

	for (ofXml &doc : xmlDocs) {
		int sectionNum = BeatMapHandler::get_tagnum("section", doc);
		note_info noteInfo;
		BeatMapHandler::get_notevals(doc, noteInfo);
		map<int, string> bpmMap = BeatMapHandler::get_sectionbpm(doc);

		// for every <section> tag
		for (int j = 0; j < noteInfo.size(); j++) {
			cout << "section[" + std::to_string(j) + "]" << endl;
			cout << "bpm = " + bpmMap[j] << endl;
			// for every <note> tag
			for (int k = 0; k < noteInfo.at(j).size(); k++) {
				cout << "  note[" + std::to_string(k) + "]" << endl;
				// for every property within the <note>
				for (int l = 0; l < noteInfo.at(j).at(k).size(); l++) {
					cout << "    " + noteInfo[j][k][l].first + ": " + noteInfo[j][k][l].second << endl;
				}
			}
		}
	}
}