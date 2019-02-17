/*
This file (AttributeData.cpp) is generated
*/
#include "AttributeData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace SHUtil;

map<string, AttributeData*>* AttributeData::p_sharedDictionary = nullptr;

string AttributeData::getId() const
{
	return to_string(p_attributeId);
}

string AttributeData::getAttributeId() const
{
	return p_attributeId;
}

string AttributeData::getName() const
{
	string localId = "attribute_name_" + to_string(p_attributeId);
	return LocalizationHelper::getLocalization(localId);
}

int AttributeData::getValue() const
{
	return p_value;
}

void AttributeData::setValue(int value)
{
	p_value = value;
}

string AttributeData::description() const
{
	string desc = "attributeData = {\n";
	desc += "\tattributeId : " + to_string(p_attributeId) + "\n";
	desc += "\tname : " + getName() + "\n";
	desc += "\tvalue : " + to_string(p_value) + "\n";
	desc += "}\n";
	return desc;
}

const map<string, AttributeData*>* AttributeData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, AttributeData*>();
		static string resPath = "res/base/data/attribute.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				AttributeData* attributeData = new AttributeData();
				attributeData->p_attributeId = buffer->getString();
				attributeData->p_value = buffer->getInt();
				p_sharedDictionary->insert(pair<string, AttributeData*>(attributeData->p_attributeId, attributeData));
			}
		}
	}
	return p_sharedDictionary;
}

AttributeData* AttributeData::getAttributeDataById(const string& attributeId)
{
	if (AttributeData::getSharedDictionary()->count(attributeId)) {
		return AttributeData::getSharedDictionary()->at(attributeId);
	}
	return nullptr;
}

bool AttributeData::saveData(const string & path)
{
	auto filePath = path + "/AttributeData.dat";
	auto dict = AttributeData::getSharedDictionary();
	auto buffer = std::make_unique<bb::ByteBuffer>();
	buffer->putLong(dict->size());
	buffer->putInt(1);
	for (auto iter = dict->begin(); iter != dict->end(); iter++) {
		auto dataId = iter->first;
		auto data = iter->second;
		buffer->putString(dataId);
		buffer->putString("p_value");
		buffer->putString(to_string(data->p_value));
	}
	buffer->writeToFile(filePath);
	return true;
}

bool AttributeData::loadData(const string & path)
{
	auto filePath = path + "/AttributeData.dat";
	auto dict = AttributeData::getSharedDictionary();
	auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);
	if (!fileData.isNull()) {
		auto bytes = fileData.getBytes();
		auto buffer = std::make_unique<bb::ByteBuffer>(bytes, fileData.getSize());
		auto size = buffer->getLong();
		auto dataSize = buffer->getInt();
		for (int i = 0; i < size; ++i) {
			auto dataId = buffer->getString();
			AttributeData *data = nullptr;
			if (dict->count(dataId)) {
				data = dict->at(dataId);
			}
			for (int j = 0; j < dataSize; ++j) {
				string key = buffer->getString();
				string value = buffer->getString();
				if (data != nullptr) {
					if (key == "p_value") {
						data->p_value = atoi(value.c_str());
					}
				}
			}
		}
	}
	return true;
}

bool AttributeData::clearData()
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

void AttributeData::setFieldValue(const string & fieldName, const string & value)
{
	if (fieldName == "value") {
		this->setValue(atoi(value.c_str()));
	}
}

string AttributeData::getFieldValue(const string & fieldName)
{
	if (fieldName == "attributeId") {
		return to_string(this->getAttributeId());
	} else if (fieldName == "name") {
		return to_string(this->getName());
	} else if (fieldName == "value") {
		return to_string(this->getValue());
	}
	CCLOGWARN("Couldn't recognize %s in AttributeData", fieldName.c_str());
	return "";
}

