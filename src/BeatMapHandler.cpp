#include "../include/BeatMapHandler.h"

void BeatMapHandler::get_paths(const fs::path &root, const string &ext, vector<fs::path> &ret) {
	if (!fs::exists(root) || !fs::is_directory(root))
		return;
	
	/// iterators ---------------------------
	fs::recursive_directory_iterator it(root);
	fs::recursive_directory_iterator endit;

	/// while there are still files ---------
	while (it != endit) {
		if (fs::is_regular_file(*it) && it->path().extension() == ext) ret.push_back(it->path());

		++it;
	}
}

val_map BeatMapHandler::getSectionVals(ofXml &doc, string value) {
	val_map res;
	for (int i = 0; i < BeatMapHandler::getNumOfTags(doc, "section"); i++)
		res[i] = ofToInt(doc.getValue("section[" + std::to_string(i) + "]/" + value));
	
	return res;
}

int BeatMapHandler::getNumOfTags(ofXml &doc, const string &tag) {
	int res = 0;
	std::size_t f;
	
	for (int i = 0; i < doc.getNumChildren(); i++) {
		doc.setToChild(i);
		f = doc.getName().find(tag);
		if (f != string::npos) res++;
		doc.setToParent(1);
	}

	return res;
}

note_info BeatMapHandler::getNoteVals(ofXml doc) {
	note_info ret;
	int sectionNum = BeatMapHandler::getNumOfTags(doc, "section");

	for (int i = 0; i < sectionNum; i++) {
		doc.setTo("section[" + std::to_string(i) + "]");
		int noteNum = BeatMapHandler::getNumOfTags(doc, "note");

		for (int j = 0; j < noteNum; j++) {
			doc.setTo("note[" + std::to_string(j) + "]");
			
			for (int k = 0; k < doc.getNumChildren(); k++) {
				doc.setToChild(k);

				if (doc.getNumChildren() == 0) {
					ret[i][j][k].first = doc.getName();
					ret[i][j][k].second = doc.getValue();
				} else {
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

	return ret;
}

string BeatMapHandler::getMapName(ofXml &doc) {
	return doc.getValue("name");
}

int BeatMapHandler::getMapRating(ofXml &doc) {
	return ofToInt(doc.getValue("rating"));
}

vector<ofXml> BeatMapHandler::getXml(vector<fs::path> paths_) {
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
	get_paths(ofToDataPath("beatmaps"), ".xml", paths);
	vector<ofXml> xmlDocs = BeatMapHandler::getXml(paths);

	for (ofXml &doc : xmlDocs) {
		int sectionNum     = BeatMapHandler::getNumOfTags(doc, "section");
		val_map offMap     = BeatMapHandler::getSectionVals(doc, "offset");
		val_map bpmMap     = BeatMapHandler::getSectionVals(doc, "bpm");
		note_info noteInfo = BeatMapHandler::getNoteVals(doc);
		string beatmapname = BeatMapHandler::getMapName(doc);
		int beatmaprating  = BeatMapHandler::getMapRating(doc);

		cout << endl << beatmapname << endl;
		cout << "Rating: " + std::to_string(beatmaprating) << endl << endl;

		// for every <section> tag
		for (int j = 0; j < noteInfo.size(); j++) {
			cout << "section[" + std::to_string(j) + "]" << endl;
			cout << "  bpm = " + std::to_string(bpmMap[j]) << endl;
			cout << "  off = " + std::to_string(offMap[j]) << endl << endl;
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