//
//  ExcelParserMap.cpp
//  ResourcePackager
//
//  Created by Yujie Liu on 10/20/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#include "ExcelParserMap.hpp"
#include "Utils.hpp"

ExcelParserMap::ExcelParserMap(const DataSchema *schema,const string & idSchemaName) : ExcelParserBase(schema, idSchemaName)
{
  string subType = schema->getSubtype();
  auto keys = utils::split(subType, ';');
  assert(keys.size() == 2);
  p_valueType = keys[1];
  p_keyType = keys[0];
}

string ExcelParserMap::getVariableName() const
{
  return "p_" + p_schema->getName() + "Map";
}

string ExcelParserMap::getVariableGetterName() const
{
  return this->ExcelParserBase::getVariableGetterName() + "Map";
}

string ExcelParserMap::getVariableSetterName() const
{
  return this->ExcelParserBase::getVariableSetterName() + "Map";
}

string ExcelParserMap::getVariableType() const
{
  return "map<"+ p_keyType + ", " + p_valueType + ">";
}

string ExcelParserMap::convertMapLine(const string &value) const
{
  return "map<"+ p_keyType + "," + p_valueType + "> " + convertMapDefine() + "(" + value + ".begin(), " + value + ".end());";
}

string ExcelParserMap::convertMapDefine() const
{
  return p_schema->getName() + "Map";
}

string ExcelParserMap::getDescription() const
{
  string descriptState_1 = "\n\tdesc += \"\\t" + p_schema->getName() + " : \" + ";
  string descriptState_2 = "to_string(" + this->getVariableName() +")";
  string descriptState_3 = "+ \"\\n\";";
  
  return descriptState_1 + descriptState_2 + descriptState_3;
}

string ExcelParserMap::getType() const
{
  assert(p_schema->getType() == MAP);
  return TYPE_MAP(p_keyType, p_valueType);
}

void ExcelParserMap::addSaveFuncBody(CPPFunction *saveFunc, const string dataName, int level) const
{
  auto schemaName = getVariableName();
  
  saveFunc->addBodyStatementsList({
    "buffer->putString(\"" + schemaName + "\");",
    "buffer->putString(to_string(" + dataName+ "->"+ schemaName + "));",
  }, 1);
}

void ExcelParserMap::addLoadFuncBody(CPPFunction *loadFunc, bool isFirstOne, const string dataName, int level) const
{
  auto schemaName = getVariableName();
  string prefix = isFirstOne ? "": "} else ";
  auto list = p_schema->getName() + "List";
  auto dataMap = convertMapDefine();
  loadFunc->addBodyStatementsList({
    make_pair(prefix + "if (key == \"" + schemaName + "\") {", level),
    make_pair(getVariableType() + " " + dataMap + ";", level + 1),
    make_pair("auto " + list +" = atomap(value);", level + 1),
    make_pair("for (auto mapData : " + list + ") {", level + 1),
    make_pair(dataMap + ".insert(make_pair(mapData.first, " + castFromStringToValue(s_subtype_map.at(p_valueType), "mapData.second") + "));", level + 2),
    make_pair("}", level + 1),
    make_pair(dataName + "->" + schemaName + " = " + dataMap + ";", level + 1),
  });
}

void ExcelParserMap::addSetFieldValueFuncBody(CPPFunction *setFieldFunc)
{
  int level = 0;
  auto schemaName = getVariableName();
  auto list = p_schema->getName() + "List";
  auto dataMap = convertMapDefine();
  setFieldFunc->addBodyStatementsList({
    make_pair(getVariableType() + " " + dataMap + ";", level + 1),
    make_pair("auto " + list +" = atomap(value);", level + 1),
    make_pair("for (auto mapData : " + list + ") {", level + 1),
    make_pair(dataMap + ".insert(make_pair(mapData.first, " + castFromStringToValue(s_subtype_map.at(p_valueType), "mapData.second") + "));", level + 2),
    make_pair("}", level + 1),
    make_pair("this->" + getVariableSetterName() + "(" + dataMap + ");", level + 1),
  });
}

void ExcelParserMap::addInitFuncBody(CPPFunction *func,const string &variableName, int level) const
{
  string schemaName = this->getVariableName();
  func->addBodyStatementsList({
    make_pair("auto " + p_schema->getName() + "Count = buffer->getLong();", level),
    make_pair("for (int j = 0; j < " + p_schema->getName() + "Count; ++j) {", level),
    make_pair("auto key = buffer->" + getBufferGetString(s_subtype_map.at(p_keyType)) + ";", level +1),
    make_pair("auto val = buffer->" + getBufferGetString(s_subtype_map.at(p_valueType)) + ";", level +1),
    make_pair(variableName + "->" + schemaName + ".insert(make_pair(key" + ", val));", level + 1),
    make_pair("}", level),
  });
}
