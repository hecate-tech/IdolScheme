//#include "../include/BeatMaps.h"

/*
vector<string> BeatMapReader::getBeatList(const string &path) {
    vector<string> m_file_list;
    
    if(!path.empty()) {
        namespace fs = boost::filesystem;

        fs::path apkPath(path);
        fs::recursive_directory_iterator end;

        for(fs::recursive_directory_iterator i(apkPath); i != end; ++i) {
            const fs::path cp = (*i);
            m_file_list.push_back(cp.string());
        }
    }
    
    return m_file_list;
}
*/