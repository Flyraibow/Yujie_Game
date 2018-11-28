/*
This file (StoryData.cpp) is generated
*/
#include "StoryData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"


using namespace SHUtil;

map<string, StoryData*>* StoryData::p_sharedDictionary = nullptr;

string StoryData::getId() const
{
	return to_string(p_storyId);
}

string StoryData::getStoryId() const
{
	return p_storyId;
}

StoryEventData* StoryData::getStoryEventData() const
{
	return StoryEventData::getStoryEventDataById(p_storyEventId);
}

string StoryData::getStoryEventId() const
{
	return p_storyEventId;
}

HeroData* StoryData::getHeroData() const
{
	return HeroData::getHeroDataById(p_heroId);
}

string StoryData::getHeroId() const
{
	return p_heroId;
}

vector<string> StoryData::getGameSwitch() const
{
	return p_gameSwitch;
}

CityData* StoryData::getCityData() const
{
	return CityData::getCityDataById(p_cityId);
}

string StoryData::getCityId() const
{
	return p_cityId;
}

CityBuildingData* StoryData::getBuildingData() const
{
	return CityBuildingData::getCityBuildingDataById(p_buildingId);
}

string StoryData::getBuildingId() const
{
	return p_buildingId;
}

bool StoryData::getRepeated() const
{
	return p_repeated;
}

int StoryData::getPriority() const
{
	return p_priority;
}

string StoryData::description() const
{
	string desc = "storyData = {\n";
	desc += "\tstoryId : " + to_string(p_storyId) + "\n";
	desc += "\tstoryEvent : " + to_string(p_storyEventId) + "\n";
	desc += "\thero : " + to_string(p_heroId) + "\n";
	desc += "\tgameSwitch : " + to_string(p_gameSwitch) + "\n";
	desc += "\tcity : " + to_string(p_cityId) + "\n";
	desc += "\tbuilding : " + to_string(p_buildingId) + "\n";
	desc += "\trepeated : " + to_string(p_repeated) + "\n";
	desc += "\tpriority : " + to_string(p_priority) + "\n";
	desc += "}\n";
	return desc;
}

const map<string, StoryData*>* StoryData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, StoryData*>();
		static string resPath = "res/base/data/story.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				StoryData* storyData = new StoryData();
				storyData->p_storyId = buffer->getString();
				storyData->p_storyEventId = buffer->getString();
				storyData->p_heroId = buffer->getString();
				auto gameSwitchCount = buffer->getLong();
				for (int j = 0; j < gameSwitchCount; ++j) {
					storyData->p_gameSwitch.push_back(buffer->getString());
				}
				storyData->p_cityId = buffer->getString();
				storyData->p_buildingId = buffer->getString();
				storyData->p_repeated = buffer->getChar();
				storyData->p_priority = buffer->getInt();
				p_sharedDictionary->insert(pair<string, StoryData*>(storyData->p_storyId, storyData));
			}
		}
	}
	return p_sharedDictionary;
}

StoryData* StoryData::getStoryDataById(const string& storyId)
{
	if (StoryData::getSharedDictionary()->count(storyId)) {
		return StoryData::getSharedDictionary()->at(storyId);
	}
	return nullptr;
}

string StoryData::getFieldValue(const string & fieldName)
{
	if (fieldName == "storyId") {
		return to_string(this->getStoryId());
	} else if (fieldName == "storyEvent") {
		return to_string(this->getStoryEventId());
	} else if (fieldName == "hero") {
		return to_string(this->getHeroId());
	} else if (fieldName == "gameSwitch") {
		return to_string(this->getGameSwitch());
	} else if (fieldName == "city") {
		return to_string(this->getCityId());
	} else if (fieldName == "building") {
		return to_string(this->getBuildingId());
	} else if (fieldName == "repeated") {
		return to_string(this->getRepeated());
	} else if (fieldName == "priority") {
		return to_string(this->getPriority());
	}
	CCLOGWARN("Couldn't recognize %s in StoryData", fieldName.c_str());
	return "";
}

