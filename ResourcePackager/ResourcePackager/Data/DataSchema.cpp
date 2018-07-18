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
});

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

DataSchema::DataSchema(const string &name, const string &type, const string &subType, bool isWritable)
{
  p_name = name;
  p_subType = subType;
  string lower_type = type;
  transform(lower_type.begin(), lower_type.end(), lower_type.begin(), ::tolower);
  p_typeString = lower_type;
  p_type = s_type_map.at(lower_type);
  p_isWritable = isWritable;
}

