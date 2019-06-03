/*
This file (PlotData.cpp) is generated
*/
#include "PlotData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace Utils;

map<string, PlotData*>* PlotData::p_sharedDictionary = nullptr;

string PlotData::getId() const
{
	return to_string(p_plotId);
}

string PlotData::getPlotId() const
{
	return p_plotId;
}

ConditionData* PlotData::getConditionData() const
{
	return ConditionData::getConditionDataById(p_conditionId);
}

string PlotData::getConditionId() const
{
	return p_conditionId;
}

DateData* PlotData::getDateData() const
{
	return DateData::getDateDataById(p_dateId);
}

string PlotData::getDateId() const
{
	return p_dateId;
}

bool PlotData::getRepeatable() const
{
	return p_repeatable;
}

bool PlotData::getExperienced() const
{
	return p_experienced;
}

void PlotData::setExperienced(bool experienced)
{
	p_experienced = experienced;
}

string PlotData::getPlotStory() const
{
	return p_plotStory;
}

string PlotData::getText() const
{
	string localId = "plot_text_" + to_string(p_plotId);
	return LocalizationHelper::getLocalization(localId);
}

string PlotData::description() const
{
	string desc = "plotData = {\n";
	desc += "\tplotId : " + to_string(p_plotId) + "\n";
	desc += "\tcondition : " + to_string(p_conditionId) + "\n";
	desc += "\tdate : " + to_string(p_dateId) + "\n";
	desc += "\trepeatable : " + to_string(p_repeatable) + "\n";
	desc += "\texperienced : " + to_string(p_experienced) + "\n";
	desc += "\tplotStory : " + to_string(p_plotStory) + "\n";
	desc += "\ttext : " + getText() + "\n";
	desc += "}\n";
	return desc;
}

const map<string, PlotData*>* PlotData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, PlotData*>();
		static string resPath = "res/base/data/plot.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				PlotData* plotData = new PlotData();
				plotData->p_plotId = buffer->getString();
				plotData->p_conditionId = buffer->getString();
				plotData->p_dateId = buffer->getString();
				plotData->p_repeatable = buffer->getChar();
				plotData->p_experienced = buffer->getChar();
				plotData->p_plotStory = buffer->getString();
				p_sharedDictionary->insert(pair<string, PlotData*>(plotData->p_plotId, plotData));
			}
		}
	}
	return p_sharedDictionary;
}

PlotData* PlotData::getPlotDataById(const string& plotId)
{
	if (PlotData::getSharedDictionary()->count(plotId)) {
		return PlotData::getSharedDictionary()->at(plotId);
	}
	return nullptr;
}

bool PlotData::saveData(const string & path)
{
	auto filePath = path + "/PlotData.dat";
	auto dict = PlotData::getSharedDictionary();
	auto buffer = std::make_unique<bb::ByteBuffer>();
	buffer->putLong(dict->size());
	buffer->putInt(1);
	for (auto iter = dict->begin(); iter != dict->end(); iter++) {
		auto dataId = iter->first;
		auto data = iter->second;
		buffer->putString(dataId);
		buffer->putString("p_experienced");
		buffer->putString(to_string(data->p_experienced));
	}
	buffer->writeToFile(filePath);
	return true;
}

bool PlotData::loadData(const string & path)
{
	auto filePath = path + "/PlotData.dat";
	auto dict = PlotData::getSharedDictionary();
	auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);
	if (!fileData.isNull()) {
		auto bytes = fileData.getBytes();
		auto buffer = std::make_unique<bb::ByteBuffer>(bytes, fileData.getSize());
		auto size = buffer->getLong();
		auto dataSize = buffer->getInt();
		for (int i = 0; i < size; ++i) {
			auto dataId = buffer->getString();
			PlotData *data = nullptr;
			if (dict->count(dataId)) {
				data = dict->at(dataId);
			}
			for (int j = 0; j < dataSize; ++j) {
				string key = buffer->getString();
				string value = buffer->getString();
				if (data != nullptr) {
					if (key == "p_experienced") {
						data->p_experienced = (atoi(value.c_str()) != 0);
					}
				}
			}
		}
	}
	return true;
}

bool PlotData::clearData()
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

void PlotData::setFieldValue(const string & fieldName, const string & value)
{
	if (fieldName == "experienced") {
		this->setExperienced((atoi(value.c_str()) != 0));
	}
}

string PlotData::getFieldValue(const string & fieldName) const
{
	if (fieldName == "plotId") {
		return to_string(this->getPlotId());
	} else if (fieldName == "condition") {
		return to_string(this->getConditionId());
	} else if (fieldName == "date") {
		return to_string(this->getDateId());
	} else if (fieldName == "repeatable") {
		return to_string(this->getRepeatable());
	} else if (fieldName == "experienced") {
		return to_string(this->getExperienced());
	} else if (fieldName == "plotStory") {
		return to_string(this->getPlotStory());
	} else if (fieldName == "text") {
		return to_string(this->getText());
	}
	CCLOGWARN("Couldn't recognize %s in PlotData", fieldName.c_str());
	return "";
}

BaseData* PlotData::getDataByField(const string & fieldName) const
{
	if (fieldName == "condition") {
		return this->getConditionData();
	} else if (fieldName == "date") {
		return this->getDateData();
	}
	CCLOGWARN("Couldn't recognize %s in PlotData", fieldName.c_str());
	return nullptr;
}

vector<BaseData *> PlotData::getFieldDataList(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in PlotData", fieldName.c_str());
	return vector<BaseData *>();
}

