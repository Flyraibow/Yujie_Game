/*
This file (GuildData.cpp) is generated
*/
#include "GuildData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include <LocalizationHelper.hpp>

using namespace std;

map<string, GuildData*>* GuildData::p_sharedDictionary = nullptr;

string GuildData::getGuildId() const
{
	return p_guildId;
}

void GuildData::setGuildName(string guildName)
{
	p_guildName = guildName;
}

string GuildData::getGuildName() const
{
	if (p_guildName.length() > 0) {
		return p_guildName;
	}
	string localId = "guild_guildName_" + p_guildId;
	return LocalizationHelper::getLocalization(localId);
}

HeroData* GuildData::getHeroData() const
{
	return HeroData::getHeroDataById(p_guildLeaderId);
}

string GuildData::getGuildLeaderId() const
{
	return p_guildLeaderId;
}

int GuildData::getStyle() const
{
	return p_style;
}

int GuildData::getMoney() const
{
	return p_money;
}

void GuildData::setMoney(int money)
{
	p_money = money;
}

string GuildData::description() const
{
	string desc = "guildData = {\n";
	desc += "\tguildId : " + to_string(p_guildId) + "\n";
	desc += "\tguildName : " + getGuildName() + "\n";
	desc += "\tguildLeaderId : " + to_string(p_guildLeaderId) + "\n";
	desc += "\tstyle : " + to_string(p_style) + "\n";
	desc += "\tmoney : " + to_string(p_money) + "\n";
	desc += "}\n";
	return desc;
}

map<string, GuildData*>* GuildData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, GuildData*>();
		static string resPath = "res/base/data/guild.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				GuildData* guildData = new GuildData();
				guildData->p_guildId = buffer->getString();
				guildData->p_guildLeaderId = buffer->getString();
				guildData->p_style = buffer->getInt();
				guildData->p_money = buffer->getInt();
				p_sharedDictionary->insert(pair<string, GuildData*>(guildData->p_guildId, guildData));
			}
		}
	}
	return p_sharedDictionary;
}

GuildData* GuildData::getGuildDataById(const string& guildId)
{
	if (GuildData::getSharedDictionary()->count(guildId)) {
		return GuildData::getSharedDictionary()->at(guildId);
	}
	CCLOGERROR("invalid guildId %s", guildId.c_str());
	return nullptr;
}

bool GuildData::saveData(const string & path)
{
	auto filePath = path + "/GuildData.dat";
	auto dict = GuildData::getSharedDictionary();
	auto buffer = make_unique<bb::ByteBuffer>();
	buffer->putLong(dict->size());
	buffer->putInt(2);
	for (auto iter = dict->begin(); iter != dict->end(); iter++) {
		auto dataId = iter->first;
		auto data = iter->second;
		buffer->putString(dataId);
		buffer->putString("guildName");
		buffer->putString(to_string(data->p_guildName));
		buffer->putString("money");
		buffer->putString(to_string(data->p_money));
	}
	buffer->writeToFile(filePath);
	return true;
}

bool GuildData::loadData(const string & path)
{
	auto filePath = path + "/GuildData.dat";
	auto dict = GuildData::getSharedDictionary();
	auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);
	if (!fileData.isNull()) {
		auto bytes = fileData.getBytes();
		auto buffer = make_unique<bb::ByteBuffer>(bytes, fileData.getSize());
		auto size = buffer->getLong();
		auto dataSize = buffer->getInt();
		for (int i = 0; i < size; ++i) {
			string dataId = buffer->getString();
			GuildData *data = nullptr;
			if (dict->count(dataId)) {
				data = dict->at(dataId);
			}
			for (int j = 0; j < dataSize; ++j) {
				string key = buffer->getString();
				string value = buffer->getString();
				if (data != nullptr) {
					if (key == "guildName") {
						data->p_guildName = value;
					} else if (key == "money") {
						data->p_money = atoi(value.c_str());
					}
				}
			}
		}
	}
	return true;
}

bool GuildData::clearData()
{
	if (p_sharedDictionary != nullptr) {
		for (auto iter = p_sharedDictionary->begin(); iter != p_sharedDictionary->end(); ++iter) {
			auto data = iter->second;
			delete data;
		}
		delete p_sharedDictionary;
		p_sharedDictionary = nullptr;
	}
	return true;
}

