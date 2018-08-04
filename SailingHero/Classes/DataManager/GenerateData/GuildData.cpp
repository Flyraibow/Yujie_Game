/*
This file (GuildData.cpp) is generated
*/
#include "GuildData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include <LocalizationHelper.hpp>


using namespace SHUtil;

map<int, GuildData*>* GuildData::p_sharedDictionary = nullptr;

string GuildData::getId() const
{
	return to_string(p_guildId);
}

int GuildData::getGuildId() const
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
	string localId = "guild_guildName_" + to_string(p_guildId);
	return LocalizationHelper::getLocalization(localId);
}

HeroData* GuildData::getLeaderData() const
{
	return HeroData::getHeroDataById(p_leaderId);
}

string GuildData::getLeaderId() const
{
	return p_leaderId;
}

vector<ShipTeamData*> GuildData::getShipTeamDataVector() const
{
	vector<ShipTeamData*> resultVector;
	for (auto objId : p_shipTeamIdVector) {
		resultVector.push_back(ShipTeamData::getShipTeamDataById(objId));
	}
	return resultVector;
}

vector<string> GuildData::getShipTeamIdVector() const
{
	return p_shipTeamIdVector;
}

void GuildData::setShipTeamIdVector(vector<string> shipTeam)
{
	p_shipTeamIdVector = shipTeam;
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
	desc += "\tleader : " + to_string(p_leaderId) + "\n";
	desc += "\tshipTeam : " + to_string(p_shipTeamIdVector) + "\n";
	desc += "\tstyle : " + to_string(p_style) + "\n";
	desc += "\tmoney : " + to_string(p_money) + "\n";
	desc += "}\n";
	return desc;
}

map<int, GuildData*>* GuildData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<int, GuildData*>();
		static string resPath = "res/base/data/guild.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				GuildData* guildData = new GuildData();
				guildData->p_guildId = buffer->getInt();
				guildData->p_leaderId = buffer->getString();
				auto shipTeamCount = buffer->getLong();
				for (int j = 0; j < shipTeamCount; ++j) {
					guildData->p_shipTeamIdVector.push_back(buffer->getString());
				}
				guildData->p_style = buffer->getInt();
				guildData->p_money = buffer->getInt();
				p_sharedDictionary->insert(pair<int, GuildData*>(guildData->p_guildId, guildData));
			}
		}
	}
	return p_sharedDictionary;
}

GuildData* GuildData::getGuildDataById(int guildId)
{
	if (GuildData::getSharedDictionary()->count(guildId)) {
		return GuildData::getSharedDictionary()->at(guildId);
	}
	return nullptr;
}

GuildData* GuildData::getGuildDataById(const string& guildId)
{
	if (guildId.length() == 0) return nullptr;
	return GuildData::getGuildDataById(atoi(guildId.c_str()));
}

bool GuildData::saveData(const string & path)
{
	auto filePath = path + "/GuildData.dat";
	auto dict = GuildData::getSharedDictionary();
	auto buffer = std::make_unique<bb::ByteBuffer>();
	buffer->putLong(dict->size());
	buffer->putInt(3);
	for (auto iter = dict->begin(); iter != dict->end(); iter++) {
		auto dataId = iter->first;
		auto data = iter->second;
		buffer->putInt(dataId);
		buffer->putString("p_guildName");
		buffer->putString(to_string(data->p_guildName));
		buffer->putString("p_shipTeamIdVector");
		buffer->putString(to_string(data->p_shipTeamIdVector));
		buffer->putString("p_money");
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
		auto buffer = std::make_unique<bb::ByteBuffer>(bytes, fileData.getSize());
		auto size = buffer->getLong();
		auto dataSize = buffer->getInt();
		for (int i = 0; i < size; ++i) {
			auto dataId = buffer->getInt();
			GuildData *data = nullptr;
			if (dict->count(dataId)) {
				data = dict->at(dataId);
			}
			for (int j = 0; j < dataSize; ++j) {
				string key = buffer->getString();
				string value = buffer->getString();
				if (data != nullptr) {
					if (key == "p_guildName") {
						data->p_guildName = value;
					} else if (key == "p_shipTeamIdVector") {
						data->p_shipTeamIdVector = atovector(value);
					} else if (key == "p_money") {
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

