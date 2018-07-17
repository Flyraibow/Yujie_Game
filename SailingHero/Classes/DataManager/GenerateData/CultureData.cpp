/*
This file (CultureData.cpp) is generated
*/
#include "CultureData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include <LocalizationHelper.hpp>

using namespace std;

map<string, CultureData*>* CultureData::p_sharedDictionary = nullptr;

string CultureData::getId() const
{
	return p_cutureId;
}

string CultureData::getCutureId() const
{
	return p_cutureId;
}

string CultureData::getCultureName() const
{
	string localId = "culture_cultureName_" + p_cutureId;
	return LocalizationHelper::getLocalization(localId);
}

string CultureData::getOceanMusicPath() const
{
	static const string s_basePath = "res/base/music/";
	return s_basePath + p_oceanMusicId;
}

string CultureData::getOceanMusicId() const
{
	return p_oceanMusicId;
}

string CultureData::getCityMusicPath() const
{
	static const string s_basePath = "res/base/music/";
	return s_basePath + p_cityMusicId;
}

string CultureData::getCityMusicId() const
{
	return p_cityMusicId;
}

cocos2d::Sprite* CultureData::getPlazaStoreIcon(bool isDefaultSize)
{
	static const string s_basePath = "res/base/icon/plaza/";
	string path = s_basePath + p_plazaStoreIconId;
	auto icon = cocos2d::Sprite::create(path);
	if (!isDefaultSize) {
		icon->setScale(cocos2d::Director::getInstance()->getContentScaleFactor());
	}
	return icon;
}

string CultureData::getPlazaStoreIconId() const
{
	return p_plazaStoreIconId;
}

cocos2d::Sprite* CultureData::getPlazaBuildingIcon(bool isDefaultSize)
{
	static const string s_basePath = "res/base/icon/plaza/";
	string path = s_basePath + p_plazaBuildingIconId;
	auto icon = cocos2d::Sprite::create(path);
	if (!isDefaultSize) {
		icon->setScale(cocos2d::Director::getInstance()->getContentScaleFactor());
	}
	return icon;
}

string CultureData::getPlazaBuildingIconId() const
{
	return p_plazaBuildingIconId;
}

string CultureData::description() const
{
	string desc = "cultureData = {\n";
	desc += "\tcutureId : " + to_string(p_cutureId) + "\n";
	desc += "\tcultureName : " + getCultureName() + "\n";
	desc += "\toceanMusicId : " + to_string(p_oceanMusicId) + "\n";
	desc += "\tcityMusicId : " + to_string(p_cityMusicId) + "\n";
	desc += "\tplazaStoreIconId : " + to_string(p_plazaStoreIconId) + "\n";
	desc += "\tplazaBuildingIconId : " + to_string(p_plazaBuildingIconId) + "\n";
	desc += "}\n";
	return desc;
}

map<string, CultureData*>* CultureData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, CultureData*>();
		static string resPath = "res/base/data/culture.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				CultureData* cultureData = new CultureData();
				cultureData->p_cutureId = buffer->getString();
				cultureData->p_plazaStoreIconId = buffer->getString();
				cultureData->p_plazaBuildingIconId = buffer->getString();
				p_sharedDictionary->insert(pair<string, CultureData*>(cultureData->p_cutureId, cultureData));
			}
		}
	}
	return p_sharedDictionary;
}

CultureData* CultureData::getCultureDataById(const string& cutureId)
{
	if (CultureData::getSharedDictionary()->count(cutureId)) {
		return CultureData::getSharedDictionary()->at(cutureId);
	}
	if (cutureId.length() > 0) {
		CCLOGWARN("invalid cutureId %s", cutureId.c_str());
	}
	return nullptr;
}

