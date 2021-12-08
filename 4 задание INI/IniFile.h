#include<string>
#include<map>
#include<vector>
#include<cstdlib>
#include<cassert>
class IniFile {
	std::string path;
public:
	std::map<std::string, std::map<std::string, std::string>> data;

	IniFile(std::string pathh) {
		path = pathh;
	}

	void Save();//for adding in map	

	template<typename T> T Read(std::string section, std::string key, T defaultValue = T{});//output key one

	template<typename T> void Write(std::string section, std::string key, T value);//write second value

	bool SectionExists(std::string section);

	bool KeyExists(std::string section, std::string key);//second key exist

	std::vector<std::string> sections();

	std::vector<std::string> keys(std::string section);//key keys


	~IniFile() {}
};