#include "../include/BeatMapHandler.h"

/////////////////////////////////////////////////////////////////
   /////////////////      Private Methods      ///////////////
/////////////////////////////////////////////////////////////////
void BeatMapHandler::getPaths(const fs::path &root, const string &ext, vector<fs::path> &ret) {
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

//--------------------------------------------------------------------------------------
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

////////////////////////////////////////////////////////////////
   /////////////////      Public Methods      ///////////////
////////////////////////////////////////////////////////////////
vector<ofXml> BeatMapHandler::getXml() {
	vector<fs::path> paths_;
	BeatMapHandler::getPaths(ofToDataPath("beatmaps"), ".xml", paths_);

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

//--------------------------------------------------------------------------------------
vector<string> BeatMapHandler::getMapNames() {
	vector<string> names;
	vector<ofXml> xmlDocs = BeatMapHandler::getXml();

	for (ofXml &doc : xmlDocs) {
		names.push_back(BeatMapHandler::getMapName(doc));
	}

	return names;
}

//--------------------------------------------------------------------------------------
int BeatMapHandler::getMapRating(ofXml &doc) {
	return ofToInt(doc.getValue("rating"));
}

//--------------------------------------------------------------------------------------
string BeatMapHandler::getMapName(ofXml &doc) {
	return doc.getValue("name");
}

//--------------------------------------------------------------------------------------
note_info BeatMapHandler::getNoteVals(ofXml doc) {
	note_info ret;
	int sectionNum = BeatMapHandler::getNumOfTags(doc, "section");

	//------------------------------------------------------
	for (int i = 0; i < sectionNum; i++) {

		doc.setTo("section[" + std::to_string(i) + "]");
		int noteNum = BeatMapHandler::getNumOfTags(doc, "note");
		//--------------------------------------------------
		for (int j = 0; j < noteNum; j++) {

			doc.setTo("note[" + std::to_string(j) + "]");
			//----------------------------------------------
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

	return ret;
}

//--------------------------------------------------------------------------------------
ofXml BeatMapHandler::getMap(const string & mapName) {
	vector<ofXml> xmlDocs = BeatMapHandler::getXml();

	for (ofXml &doc : xmlDocs)
		if (BeatMapHandler::getMapName(doc).compare(mapName) == 0)
			return doc;

	return ofXml();
}

//--------------------------------------------------------------------------------------
val_map BeatMapHandler::getSectionVals(ofXml &doc, string value) {
	val_map res;
	for (int i = 0; i < BeatMapHandler::getNumOfTags(doc, "section"); i++)
		res[i] = ofToInt(doc.getValue("section[" + std::to_string(i) + "]/" + value));
	
	return res;
}


