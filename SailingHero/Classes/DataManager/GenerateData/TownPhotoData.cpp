/*
This file (TownPhotoData.cpp) is generated
*/
#include "TownPhotoData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"


using namespace SHUtil;

map<string, TownPhotoData*>* TownPhotoData::p_sharedDictionary = nullptr;

string TownPhotoData::getId() const
{
	return to_string(p_townPhotoId);
}

string TownPhotoData::getTownPhotoId() const
{
	return p_townPhotoId;
}

cocos2d::Sprite* TownPhotoData::getTownPhotoImage(bool isDefaultSize)
{
	static const string s_basePath = "res/base/icon/townGrp/";
	string path = s_basePath + p_townPhotoImageId;
	auto icon = cocos2d::Sprite::create(path);
	if (!isDefaultSize) {
		icon->setScale(cocos2d::Director::getInstance()->getContentScaleFactor());
	}
	return icon;
}

string TownPhotoData::getTownPhotoImagePath()
{
	static const string s_basePath = "res/base/icon/townGrp/";
	return s_basePath + p_townPhotoImageId;
}

string TownPhotoData::getTownPhotoImageId() const
{
	return p_townPhotoImageId;
}

string TownPhotoData::description() const
{
	string desc = "townPhotoData = {\n";
	desc += "\ttownPhotoId : " + to_string(p_townPhotoId) + "\n";
	desc += "\ttownPhotoImageId : " + to_string(p_townPhotoImageId) + "\n";
	desc += "}\n";
	return desc;
}

const map<string, TownPhotoData*>* TownPhotoData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, TownPhotoData*>();
		static string resPath = "res/base/data/townPhoto.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				TownPhotoData* townPhotoData = new TownPhotoData();
				townPhotoData->p_townPhotoId = buffer->getString();
				townPhotoData->p_townPhotoImageId = buffer->getString();
				p_sharedDictionary->insert(pair<string, TownPhotoData*>(townPhotoData->p_townPhotoId, townPhotoData));
			}
		}
	}
	return p_sharedDictionary;
}

TownPhotoData* TownPhotoData::getTownPhotoDataById(const string& townPhotoId)
{
	if (TownPhotoData::getSharedDictionary()->count(townPhotoId)) {
		return TownPhotoData::getSharedDictionary()->at(townPhotoId);
	}
	return nullptr;
}

string TownPhotoData::getFieldValue(const string & fieldName)
{
	if (fieldName == "townPhotoId") {
		return to_string(this->getTownPhotoId());
	} else if (fieldName == "townPhotoImageId") {
		return to_string(this->getTownPhotoImageId());
	}
	CCLOGWARN("Couldn't recognize %s in TownPhotoData", fieldName.c_str());
	return "";
}

