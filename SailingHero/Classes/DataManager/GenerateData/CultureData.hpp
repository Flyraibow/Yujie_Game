/*
This file (CultureData.hpp) is generated at 2018-07-11 01:50:01
*/
#ifndef CultureData_hpp
#define CultureData_hpp
#include <unordered_map>

using namespace std;
class CultureData
{
private:
	string p_cutureId;
	string p_oceanMusicId;
	string p_cityMusicId;
	string p_plazaStoreIconId;
	string p_plazaBuildingIconId;
public:
	string getCutureId() const;
	string getCultureName() const;
	string getOceanMusicPath() const;
	string getOceanMusicId() const;
	string getCityMusicPath() const;
	string getCityMusicId() const;
	cocos2d::Sprite* getPlazaStoreIcon() const;
	string getPlazaStoreIconId() const;
	cocos2d::Sprite* getPlazaBuildingIcon() const;
	string getPlazaBuildingIconId() const;
	string description() const;
	static unordered_map<string, CultureData*>* getSharedDictionary();
	static CultureData* getCultureDataById(const string& cutureId);
};
#endif
