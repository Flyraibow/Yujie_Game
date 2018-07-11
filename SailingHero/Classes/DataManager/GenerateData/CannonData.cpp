/*
This file (CannonData.cpp) is generated at 2018-07-11 14:19:57
*/
#include "CannonData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include <LocalizationHelper.hpp>

using namespace std;
string CannonData::getCannonId() const
{
	return p_cannonId;
}

string CannonData::getCannonName() const
{
	string localId = "cannon_cannonName_" + p_cannonId;
	return LocalizationHelper::getLocalization(localId);
}

string CannonData::getCannonDescription() const
{
	string localId = "cannon_cannonDescription_" + p_cannonId;
	return LocalizationHelper::getLocalization(localId);
}

cocos2d::Sprite* CannonData::getIcon() const
{
	static const string s_basePath = "res/base/icon/cannon";
	string path = s_basePath + p_iconId;
	return cocos2d::Sprite::create(path);
}

string CannonData::getIconId() const
{
	return p_iconId;
}

int CannonData::getMilltaryValue() const
{
	return p_milltaryValue;
}

int CannonData::getPrice() const
{
	return p_price;
}

int CannonData::getRange() const
{
	return p_range;
}

int CannonData::getPower() const
{
	return p_power;
}

string CannonData::description() const
{
	string desc = "cannonData = {\n";
	desc += "\tcannonId : " + to_string(p_cannonId) + "\n";
	desc += "\tcannonName : " + getCannonName() + "\n";
	desc += "\tcannonDescription : " + getCannonDescription() + "\n";
	desc += "\ticonId : " + to_string(p_iconId) + "\n";
	desc += "\tmilltaryValue : " + to_string(p_milltaryValue) + "\n";
	desc += "\tprice : " + to_string(p_price) + "\n";
	desc += "\trange : " + to_string(p_range) + "\n";
	desc += "\tpower : " + to_string(p_power) + "\n";
	desc += "}\n";
	return desc;
}

unordered_map<string, CannonData*>* CannonData::getSharedDictionary()
{
	static unordered_map<string, CannonData*>* sharedDictionary = nullptr;
	if (!sharedDictionary) {
		sharedDictionary = new unordered_map<string, CannonData*>();
		static string resPath = "res/base/data/cannon.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				CannonData* cannonData = new CannonData();
				cannonData->p_cannonId = buffer->getString();
				cannonData->p_iconId = buffer->getString();
				cannonData->p_milltaryValue = buffer->getInt();
				cannonData->p_price = buffer->getInt();
				cannonData->p_range = buffer->getInt();
				cannonData->p_power = buffer->getInt();
				sharedDictionary->insert(pair<string, CannonData*>(cannonData->p_cannonId, cannonData));
			}
		}
	}
	return sharedDictionary;
}

CannonData* CannonData::getCannonDataById(const string& cannonId)
{
	if (CannonData::getSharedDictionary()->count(cannonId)) {
		return CannonData::getSharedDictionary()->at(cannonId);
	}
	CCLOGERROR("invalid cannonId %s", cannonId.c_str());
	return nullptr;
}

