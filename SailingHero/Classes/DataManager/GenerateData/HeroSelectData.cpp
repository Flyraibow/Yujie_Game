/*
This file (HeroSelectData.cpp) is generated
*/
#include "HeroSelectData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include <LocalizationHelper.hpp>


using namespace std;

map<int, HeroSelectData*>* HeroSelectData::p_sharedDictionary = nullptr;

string HeroSelectData::getId() const
{
	return to_string(p_selectHeroId);
}

int HeroSelectData::getSelectHeroId() const
{
	return p_selectHeroId;
}

cocos2d::Sprite* HeroSelectData::getIcon(bool isDefaultSize)
{
	static const string s_basePath = "res/base/icon/firstGrp/";
	string path = s_basePath + p_iconId;
	auto icon = cocos2d::Sprite::create(path);
	if (!isDefaultSize) {
		icon->setScale(cocos2d::Director::getInstance()->getContentScaleFactor());
	}
	return icon;
}

string HeroSelectData::getIconPath()
{
	static const string s_basePath = "res/base/icon/firstGrp/";
	return s_basePath + p_iconId;
}

string HeroSelectData::getIconId() const
{
	return p_iconId;
}

cocos2d::Sprite* HeroSelectData::getSmallIcon(bool isDefaultSize)
{
	static const string s_basePath = "res/base/icon/firstGrp/";
	string path = s_basePath + p_smallIconId;
	auto icon = cocos2d::Sprite::create(path);
	if (!isDefaultSize) {
		icon->setScale(cocos2d::Director::getInstance()->getContentScaleFactor());
	}
	return icon;
}

string HeroSelectData::getSmallIconPath()
{
	static const string s_basePath = "res/base/icon/firstGrp/";
	return s_basePath + p_smallIconId;
}

string HeroSelectData::getSmallIconId() const
{
	return p_smallIconId;
}

GuildData* HeroSelectData::getGuildData() const
{
	return GuildData::getGuildDataById(p_guildId);
}

string HeroSelectData::getGuildId() const
{
	return p_guildId;
}

string HeroSelectData::getHeroDescription() const
{
	string localId = "heroSelect_heroDescription_" + to_string(p_selectHeroId);
	return LocalizationHelper::getLocalization(localId);
}

string HeroSelectData::description() const
{
	string desc = "heroSelectData = {\n";
	desc += "\tselectHeroId : " + to_string(p_selectHeroId) + "\n";
	desc += "\ticonId : " + to_string(p_iconId) + "\n";
	desc += "\tsmallIconId : " + to_string(p_smallIconId) + "\n";
	desc += "\tguild : " + to_string(p_guildId) + "\n";
	desc += "\theroDescription : " + getHeroDescription() + "\n";
	desc += "}\n";
	return desc;
}

map<int, HeroSelectData*>* HeroSelectData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<int, HeroSelectData*>();
		static string resPath = "res/base/data/heroSelect.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				HeroSelectData* heroSelectData = new HeroSelectData();
				heroSelectData->p_selectHeroId = buffer->getInt();
				heroSelectData->p_iconId = buffer->getString();
				heroSelectData->p_smallIconId = buffer->getString();
				heroSelectData->p_guildId = buffer->getString();
				p_sharedDictionary->insert(pair<int, HeroSelectData*>(heroSelectData->p_selectHeroId, heroSelectData));
			}
		}
	}
	return p_sharedDictionary;
}

HeroSelectData* HeroSelectData::getHeroSelectDataById(int selectHeroId)
{
	if (HeroSelectData::getSharedDictionary()->count(selectHeroId)) {
		return HeroSelectData::getSharedDictionary()->at(selectHeroId);
	}
	return nullptr;
}

HeroSelectData* HeroSelectData::getHeroSelectDataById(const string& selectHeroId)
{
	if (selectHeroId.length() == 0) return nullptr;
	return HeroSelectData::getHeroSelectDataById(atoi(selectHeroId.c_str()));
}

