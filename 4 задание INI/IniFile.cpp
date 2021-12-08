#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include"IniFile.h"

void IniFile::Save() {
	std::fstream fs(path, std::fstream::out | std::fstream::trunc);
	if (fs.is_open()) {
		std::map<std::string, std::map<std::string, std::string>>::iterator itSect;
		std::map<std::string, std::string>::iterator itSectOfKey;

		for (itSect = data.begin();itSect != data.end();itSect++) {
			fs << "[" << itSect->first << "]\n";
			for (itSectOfKey = data[itSect->first].begin();itSectOfKey != data[itSect->first].end();itSectOfKey++) {
				fs << itSectOfKey->first << "=" << itSectOfKey->second << "\n";
			}
			fs << "\n";
		}

		fs.close();
	}

}

template<typename T> T IniFile::Read(std::string section, std::string key, T defaultValue) {

	std::string line;
	std::string sect;
	std::string keyOfSect;
	std::string keyOfSectValue;
	std::ifstream inf(path);
	T result = defaultValue;

	if (inf.is_open()) {
		while (getline(inf, line)) {
			int pointOne = 0;
			int pointTwo = 0;
			for (int i = 0;i < line.size();i++) {
				if (line[i] == '[') {
					pointOne = i;
					continue;
				}
				if (line[i] == ']') {
					pointTwo = i;
					break;
				}
				if (line[i] == '=') {
					keyOfSect = line.substr(pointOne, i);
					keyOfSectValue = line.substr(i + 1, line.size() - 1);
					data[sect][keyOfSect] = keyOfSectValue;
					if ((sect == section) && (key == keyOfSect)) {
						std::stringstream stream(keyOfSectValue);
						stream >> result;
					}
					break;
				}

			}
			if ((pointOne == 0) && (pointTwo == 0)) {
				continue;
			}

			if (line[pointOne] == '[') {
				sect = line.substr(pointOne + 1, (pointTwo - pointOne - 1));
				data[sect];
			}
		}
		inf.close();
	}
	return result;

}

template std::string IniFile::Read<std::string>(std::string section, std::string key, std::string defaultValue = " ");
template bool IniFile::Read<bool>(std::string section, std::string key, bool defaultValue = false);
template int IniFile::Read<int>(std::string section, std::string key, int defaultValue = 0);
template float IniFile::Read<float>(std::string section, std::string key, float defaultValue = 0.0f);

template<typename T> void IniFile::Write(std::string section, std::string key, T value) {
	std::stringstream ss;
	ss << value;

	std::string val = ss.str();
	data[section][key] = val;
	Save();
}

template void IniFile::Write<std::string>(std::string section, std::string key, std::string value);
template void IniFile::Write<bool>(std::string section, std::string key, bool value);
template void IniFile::Write<int>(std::string section, std::string key, int value);
template void IniFile::Write<float>(std::string section, std::string key, float value);


bool IniFile::SectionExists(std::string section) {

	std::map<std::string, std::map<std::string, std::string>>::iterator it;
	it = data.find(section);
	return (it == data.end()) ? false : true;

}


bool IniFile::KeyExists(std::string section, std::string key) {

	if (SectionExists(section)) {
		std::map<std::string, std::string>::iterator it;
		it = data[section].find(key);
		return (it == data[section].end()) ? false : true;
	}
	else {
		return false;
	}

}