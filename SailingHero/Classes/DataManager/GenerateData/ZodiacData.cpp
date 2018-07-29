/*
This file (ZodiacData.cpp) is generated
*/
#include "ZodiacData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include <LocalizationHelper.hpp>


using namespace SHUtil;

map<int, ZodiacData*>* ZodiacData::p_sharedDictionary = nullptr;

string ZodiacData::getId() const
{
	return to_string(p_zodiacId);
}

int ZodiacData::getZodiacId() const
{
	return p_zodiacId;
}

string ZodiacData::getZodiacName() const
{
	string localId = "zodiac_zodiacName_" + to_string(p_zodiacId);
	return LocalizationHelper::getLocalization(localId);
}

cocos2d::Sprite* ZodiacData::getIcon(bool isDefaultSize)
{
	static const string s_basePath = "res/base/icon/zodiac/";
	string path = s_basePath + p_iconId;
	auto icon = cocos2d::Sprite::create(path);
	if (!isDefaultSize) {
		icon->setScale(cocos2d::Director::getInstance()->getContentScaleFactor());
	}
	return icon;
}

string ZodiacData::getIconPath()
{
	static const string s_basePath = "res/base/icon/zodiac/";
	return s_basePath + p_iconId;
}

string ZodiacData::getIconId() const
{
	return p_iconId;
}

int ZodiacData::getStartMonth() const
{
	return p_startMonth;
}

int ZodiacData::getStartDate() const
{
	return p_startDate;
}

int ZodiacData::getEndMonth() const
{
	return p_endMonth;
}

int ZodiacData::getEndDate() const
{
	return p_endDate;
}

string ZodiacData::description() const
{
	string desc = "zodiacData = {\n";
	desc += "\tzodiacId : " + to_string(p_zodiacId) + "\n";
	desc += "\tzodiacName : " + getZodiacName() + "\n";
	desc += "\ticonId : " + to_string(p_iconId) + "\n";
	desc += "\tstartMonth : " + to_string(p_startMonth) + "\n";
	desc += "\tstartDate : " + to_string(p_startDate) + "\n";
	desc += "\tendMonth : " + to_string(p_endMonth) + "\n";
	desc += "\tendDate : " + to_string(p_endDate) + "\n";
	desc += "}\n";
	return desc;
}

map<int, ZodiacData*>* ZodiacData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<int, ZodiacData*>();
		static string resPath = "res/base/data/zodiac.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				ZodiacData* zodiacData = new ZodiacData();
				zodiacData->p_zodiacId = buffer->getInt();
				zodiacData->p_iconId = buffer->getString();
				zodiacData->p_startMonth = buffer->getInt();
				zodiacData->p_startDate = buffer->getInt();
				zodiacData->p_endMonth = buffer->getInt();
				zodiacData->p_endDate = buffer->getInt();
				p_sharedDictionary->insert(pair<int, ZodiacData*>(zodiacData->p_zodiacId, zodiacData));
			}
		}
	}
	return p_sharedDictionary;
}

ZodiacData* ZodiacData::getZodiacDataById(int zodiacId)
{
	if (ZodiacData::getSharedDictionary()->count(zodiacId)) {
		return ZodiacData::getSharedDictionary()->at(zodiacId);
	}
	return nullptr;
}

ZodiacData* ZodiacData::getZodiacDataById(const string& zodiacId)
{
	if (zodiacId.length() == 0) return nullptr;
	return ZodiacData::getZodiacDataById(atoi(zodiacId.c_str()));
}

