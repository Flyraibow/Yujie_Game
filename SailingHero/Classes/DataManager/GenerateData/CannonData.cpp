/*
This file (CannonData.cpp) is generated
*/
#include "CannonData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include <LocalizationHelper.hpp>

using namespace std;

map<string, CannonData*>* CannonData::p_sharedDictionary = nullptr;

string CannonData::getId() const
{
	return p_cannonId;
}

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

cocos2d::Sprite* CannonData::getIcon(bool isDefaultSize)
{
	static const string s_basePath = "res/base/icon/cannon";
	string path = s_basePath + p_iconId;
	auto icon = cocos2d::Sprite::create(path);
	if (!isDefaultSize) {
		icon->setScale(cocos2d::Director::getInstance()->getContentScaleFactor());
	}
	return icon;
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

map<string, CannonData*>* CannonData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, CannonData*>();
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
				p_sharedDictionary->insert(pair<string, CannonData*>(cannonData->p_cannonId, cannonData));
			}
		}
	}
	return p_sharedDictionary;
}

CannonData* CannonData::getCannonDataById(const string& cannonId)
{
	if (CannonData::getSharedDictionary()->count(cannonId)) {
		return CannonData::getSharedDictionary()->at(cannonId);
	}
	if (cannonId.length() > 0) {
		CCLOGWARN("invalid cannonId %s", cannonId.c_str());
	}
	return nullptr;
}

