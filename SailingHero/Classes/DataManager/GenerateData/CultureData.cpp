/*
This file (CultureData.cpp) is generated
*/
#include "CultureData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace SHUtil;

map<int, CultureData*>* CultureData::p_sharedDictionary = nullptr;

string CultureData::getId() const
{
	return to_string(p_cutureId);
}

int CultureData::getCutureId() const
{
	return p_cutureId;
}

string CultureData::getCultureName() const
{
	string localId = "culture_cultureName_" + to_string(p_cutureId);
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

string CultureData::getPlazaStoreIconPath()
{
	static const string s_basePath = "res/base/icon/plaza/";
	return s_basePath + p_plazaStoreIconId;
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

string CultureData::getPlazaBuildingIconPath()
{
	static const string s_basePath = "res/base/icon/plaza/";
	return s_basePath + p_plazaBuildingIconId;
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

const map<int, CultureData*>* CultureData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<int, CultureData*>();
		static string resPath = "res/base/data/culture.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				CultureData* cultureData = new CultureData();
				cultureData->p_cutureId = buffer->getInt();
				cultureData->p_oceanMusicId = buffer->getString();
				cultureData->p_cityMusicId = buffer->getString();
				cultureData->p_plazaStoreIconId = buffer->getString();
				cultureData->p_plazaBuildingIconId = buffer->getString();
				p_sharedDictionary->insert(pair<int, CultureData*>(cultureData->p_cutureId, cultureData));
			}
		}
	}
	return p_sharedDictionary;
}

CultureData* CultureData::getCultureDataById(int cutureId)
{
	if (CultureData::getSharedDictionary()->count(cutureId)) {
		return CultureData::getSharedDictionary()->at(cutureId);
	}
	return nullptr;
}

CultureData* CultureData::getCultureDataById(const string& cutureId)
{
	if (cutureId.length() == 0) return nullptr;
	return CultureData::getCultureDataById(atoi(cutureId.c_str()));
}

string CultureData::getFieldValue(const string & fieldName)
{
	if (fieldName == "cutureId") {
		return to_string(this->getCutureId());
	} else if (fieldName == "cultureName") {
		return to_string(this->getCultureName());
	} else if (fieldName == "oceanMusicId") {
		return to_string(this->getOceanMusicId());
	} else if (fieldName == "getOceanMusicPath") {
		return to_string(this->getOceanMusicPath());
	} else if (fieldName == "cityMusicId") {
		return to_string(this->getCityMusicId());
	} else if (fieldName == "getCityMusicPath") {
		return to_string(this->getCityMusicPath());
	} else if (fieldName == "plazaStoreIconId") {
		return to_string(this->getPlazaStoreIconId());
	} else if (fieldName == "getPlazaStoreIconPath") {
		return to_string(this->getPlazaStoreIconPath());
	} else if (fieldName == "plazaBuildingIconId") {
		return to_string(this->getPlazaBuildingIconId());
	} else if (fieldName == "getPlazaBuildingIconPath") {
		return to_string(this->getPlazaBuildingIconPath());
	}
	CCLOGWARN("Couldn't recognize %s in CultureData", fieldName.c_str());
	return "";
}

