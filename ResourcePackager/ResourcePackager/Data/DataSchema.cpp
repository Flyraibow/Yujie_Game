//
//  ObjectData.cpp
//  ResourcePackager
//
//  Created by Yujie Liu on 5/16/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#include "DataSchema.hpp"
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include "Utils.hpp"
#include "CPPVariable.hpp"

using namespace std;

const static unordered_map<string, DataType> s_type_map({
  {"id",ID},
  {"bool", BOOL},
  {"int", INT},
  {"long", LONG},
  {"float", FLOAT},
  {"double", DOUBLE},
  {"icon", ICON},
  {"music", MUSIC},
  {"effect", EFFECT},
  {"string", STRING},
  {"vector", VECTOR},
  {"comment", COMMENT},
  {"language", LANGUAGE},
  {"friend_id", FRIEND_ID},
  {"set", SET},
  {"friend_id_set", FRIEND_ID_SET},
  {"friend_id_vector", FRIEND_ID_VECTOR},
  {"enum", ENUM},
  {"friend_id_map", FRIEND_ID_MAP},
});

const static unordered_set<DataType> s_friend_type_set({
  FRIEND_ID, FRIEND_ID_VECTOR, FRIEND_ID_SET, FRIEND_ID_MAP
});

void addAutoTypeToBuffer(std::unique_ptr<bb::ByteBuffer> &buffer, DataType type, const string &val)
{
  switch (type) {
    case BOOL:
      buffer->putChar(atoi(val.c_str()));
      break;
    case INT:
      buffer->putInt(atoi(val.c_str()));
      break;
    case DOUBLE:
      buffer->putDouble(atof(val.c_str()));
      break;
    case LONG:
      buffer->putLong(atoll(val.c_str()));
      break;
    case STRING:
      buffer->putString(val);
      break;
    case FLOAT:
      buffer->putFloat(atof(val.c_str()));
      break;
    default:
      // unknown type
      assert(false);
      break;
  }
}

void addVectorToBuffer(std::unique_ptr<bb::ByteBuffer> &buffer, const vector<string> &vals, const string &type)
{
  buffer->putLong(vals.size());
  DataType subType = s_subtype_map.at(type);
  for (int i = 0; i < vals.size(); ++i) {
    addAutoTypeToBuffer(buffer, subType, vals.at(i));
  }
}

string DataSchema::getName() const
{
  return p_name;
}

DataType DataSchema::getType() const
{
  return p_type;
}

string DataSchema::getSubtype() const
{
  return p_subType;
}

bool DataSchema::isWritable() const
{
  return p_isWritable;
}

bool DataSchema::isWeak() const
{
  return p_isWeak;
}

DataSchema::DataSchema(const string &name, const string &type, const string &subType, bool isWritable)
{
  p_name = name;
  string lower_type = type;
  transform(lower_type.begin(), lower_type.end(), lower_type.begin(), ::tolower);
  p_typeString = lower_type;
  p_type = s_type_map.at(lower_type);
  p_isWritable = isWritable;
  if (s_friend_type_set.count(p_type) > 0 && subType.size() > 4 && subType.substr(0, 4) == "weak") {
    p_subType = subType.substr(4, subType.size() - 4);
    p_isWeak = true;
  } else {
    p_subType = subType;
    p_isWeak = false;
  }
}

void DataSchema::addValueIntoBuffer(std::unique_ptr<bb::ByteBuffer> &buffer, const string& value)
{
  switch (p_type) {
    case ID:
      if (p_subType == TYPE_INT) {
        buffer->putInt(atoi(value.c_str()));
      } else {
        buffer->putString(value);
      }
      break;
    case FRIEND_ID:
    case STRING:
    case ICON:
    case MUSIC:
    case EFFECT:
      buffer->putString(value);
      break;
    case BOOL:
      buffer->put(atoi(value.c_str()));
      break;
    case INT:
      buffer->putInt(atoi(value.c_str()));
      break;
    case LONG:
      buffer->putLong(atoll(value.c_str()));
      break;
    case DOUBLE:
      buffer->putDouble(atof(value.c_str()));
      break;
    case FLOAT:
      buffer->putLong(atof(value.c_str()));
      break;
    case FRIEND_ID_SET:
    case FRIEND_ID_VECTOR: {
      auto vals = utils::split(value, ';');
      addVectorToBuffer(buffer, vals, TYPE_STRING);
      break;
    }
    case VECTOR:
    case SET:{
      auto vals = utils::split(value, ';');
      addVectorToBuffer(buffer, vals, p_subType);
      break;
    }
    case FRIEND_ID_MAP: {
      auto vals = utils::split(value, ';');
      auto valueType = utils::split(p_subType, ';')[1];
      buffer->putLong(vals.size());
      for (int k = 0; k < vals.size(); ++k) {
        auto pairStr = vals.at(k);
        auto pairList = utils::split(pairStr, ',');
        buffer->putString(pairList[0]);
        addAutoTypeToBuffer(buffer, s_subtype_map.at(valueType), pairList[1]);
      }
      break;
    }
    case COMMENT:
    case ENUM:
    case LANGUAGE:
      // skip
      break;
    default:
      // doesn't support other type
      assert(false);
      break;
  }
}
