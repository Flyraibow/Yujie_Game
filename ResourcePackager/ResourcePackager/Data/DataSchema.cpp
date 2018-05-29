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
});

string DataSchema::getName() const
{
    return m_name;
}

DataType DataSchema::getType() const
{
    return m_type;
}

string DataSchema::getSubtype() const
{
    return m_subType;
}

DataSchema::DataSchema(const string &name, const string &type, const string &subType)
{
    m_name = name;
    m_subType = subType;
    string lower_type = type;
    transform(lower_type.begin(), lower_type.end(), lower_type.begin(), ::tolower);
    m_typeString = lower_type;
    m_type = s_type_map.at(lower_type);
}
