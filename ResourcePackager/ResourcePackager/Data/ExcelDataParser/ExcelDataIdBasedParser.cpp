//
//  ExcelData.cpp
//  ResourcePackager
//
//  Created by Yujie Liu on 5/28/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#include "ExcelDataIdBasedParser.hpp"
#include "ReadCSV.hpp"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "CPPFile.hpp"
#include "CPPFunction.hpp"

#include "ExcelParserBase.hpp"

CPPFileComplete* ExcelDataIdBasedParser::getMainCppFile() const
{
  CPPFileComplete* file = new CPPFileComplete(p_className);
  file->addHeaders("map", false, true);
  file->addHeaders("BaseData.h", true, true);
  file->addHeaders("cocos2d.h", true, false);
  file->addHeaders("ByteBuffer.hpp", true, false);
  file->addHeaders("Utils.hpp", true, false);
  file->addNamespaces("using namespace SHUtil;", false, true);
  return file;
}

CPPClass* ExcelDataIdBasedParser::getMainCppClass() const
{
  CPPClass* cppClass = new CPPClass(p_className);
  cppClass->setFatherClass("BaseData");
  return cppClass;
}


ExcelDataIdBasedParser::ExcelDataIdBasedParser(const DataSchema *idSchema):ExcelDataParserBase()
{
  assert(idSchema != nullptr);
  p_idSchema = idSchema;
  p_idName = idSchema->getName();
}

void ExcelDataIdBasedParser::sanityCheck() const
{
  
}

void ExcelDataIdBasedParser::saveData(const string& folderPath,LanguageData &langData)
{
  p_resDataFileName = p_fileNameWithoutExt + ".dat";
  auto buffer = std::make_unique<bb::ByteBuffer>();
  buffer->putLong(p_values.size());
  for (int i = 0; i < p_values.size(); ++i) {
    auto row = p_values.at(i);
    string id;
    for (int j = 0; j < p_dataSchemas.size(); ++j) {
      DataSchema *schema = p_dataSchemas.at(j);
      auto value = row.at(j);
      schema->addValueIntoBuffer(buffer, value);
      if (schema->getType() == ID) {
        id = value;
      } else if (schema->getType() == LANGUAGE) {
        string localId = p_fileNameWithoutExt + "_" + schema->getName() + "_" + id;
        langData.addTranslation(schema->getSubtype(), localId, value);
      }
    }
  }
  utils::writeBufferToFile(buffer, folderPath, p_resDataFileName);
}

void ExcelDataIdBasedParser::setPrepareFunction()
{
  ExcelDataParserBase::setPrepareFunction();
  
  auto id_schema_type = p_idSchema->getSubtype();
  assert(id_schema_type == TYPE_STRING || id_schema_type == TYPE_INT);
  auto getIdFunc = new CPPFunction("getId", TYPE_STRING, {}, false, true, true);
  getIdFunc->addBodyStatements("return to_string(p_" + p_idName + ");");
  p_class->addFunction(getIdFunc, false);
  bool containLanguage = false;
  for (auto schema : p_dataSchemas) {
    if (schema->getType() == LANGUAGE) {
      containLanguage = true;
    } else if (schema->getType() == ENUM) {
      assert(!schema->isWritable());
      this->addEnum(p_file, schema);
    }
  }

  if (containLanguage) {
    p_file->addHeaders("LocalizationHelper.hpp", true, false);
  }
}

void ExcelDataIdBasedParser::addEnum(CPPFileComplete *cppFile, const DataSchema *schema) const
{
  auto id_schema_type = p_idSchema->getSubtype();
  auto enumClass = new CPPEnumClass(schema->getName(), id_schema_type);
  cppFile->addEnumClass(enumClass, true);
  
  for (int i = 0; i < p_values.size(); ++i) {
    auto row = p_values.at(i);
    string id;
    string initialValue = "";
    for (int j = 0; j < p_dataSchemas.size(); ++j) {
      DataSchema *sche = p_dataSchemas.at(j);
      auto value = row.at(j);
      switch (sche->getType()) {
        case ID:
          initialValue = value;
          break;
        case ENUM:
          if (schema->getName() == sche->getName()) {
            auto var = new CPPVariable(value, id_schema_type);
            var->setInitialValue(initialValue);
            enumClass->addVariable(var);
          }
          break;
        default:
          break;
      }
    }
  }
}

static string staticMapName = "p_sharedDictionary";

void ExcelDataIdBasedParser::setInitFunction()
{
  auto id_schema_type = p_idSchema->getSubtype();
  string mapDicType = "map<"+ id_schema_type + ", " + p_classTypeName + ">";
  string mapDicPointerType = mapDicType + "*";
  auto staticMapVariable = new CPPVariable(staticMapName, mapDicPointerType, true);
  staticMapVariable->setInitialValue("nullptr");
  p_class->addVariable(staticMapVariable, true);
  
  auto initFunction = new CPPFunction("getSharedDictionary", "const " + mapDicPointerType, true);
  auto descFunction = new CPPFunction("description", TYPE_STRING);
  descFunction->addBodyStatements("string desc = \"" + p_variableName + " = {\\n\";");
  const string filePath = "res/base/data/" + p_resDataFileName;
  initFunction->addBodyStatementsList({
    "if (!" + staticMapName + ") {"
    
  }, 0);
  initFunction->addBodyStatementsList({
    staticMapName + " = new " + mapDicType + "();",
    "static string resPath = \"" + filePath + "\";",
    "auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);",
    "if (!data.isNull()) {",
  }, 1);
  initFunction->addBodyStatementsList({
    "auto bytes = data.getBytes();",
    "auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());",
    "auto count = buffer->getLong();",
    "for (int i = 0; i < count; ++i) {"
  }, 2);
  initFunction->addBodyStatements(p_classTypeName + " " + p_variableName + " = new " + p_className + "();", 3);
  
  for (auto schema : p_dataSchemas) {
    if (schema->getType() != COMMENT && schema->getType() != ENUM) {
      auto parser = ExcelParserBase::createWithSchema(schema, p_idName);
      parser->setFileNameWithoutExt(p_fileNameWithoutExt);
      parser->addFunctionsInclass(p_class);
      parser->addHeaders(p_file);
      descFunction->addBodyStatements(parser->getDescription());
      parser->addInitFuncBody(initFunction, p_variableName);
      delete parser;
    }
  }
  
  descFunction->addBodyStatements("desc += \"}\\n\";");
  descFunction->addBodyStatements("return desc;");
  p_class->addFunction(descFunction, false);
  
  string id_string_name = "p_" + p_idName;  // p_goodsId;
  initFunction->addBodyStatements(staticMapName + "->insert(pair<"+id_schema_type+", " + p_classTypeName+ ">("+ p_variableName + "->p_"+ p_idName +", " + p_variableName +"));", 3);
  initFunction->addBodyStatements("}", 2);
  initFunction->addBodyStatements("}", 1);
  initFunction->addBodyStatements("}");
  initFunction->addBodyStatements("return " + staticMapName + ";");
  p_class->addFunction(initFunction, false);
  
  this->addDataLoadFunction(p_class);
  
  if (p_idSchema->isWritable()) {
    addRegisterDataFunction();
  }
}

string ExcelDataIdBasedParser::getInstanceCode() const
{
  return "auto dict = " + getClassName() + "::getSharedDictionary();";
}

void ExcelDataIdBasedParser::setLoadFunction(const CPPVariable* pathVar)
{
  auto loadFunc = new CPPFunction("loadData", TYPE_BOOL, {pathVar}, true, false);
  
  string getID = p_idSchema->getSubtype() == TYPE_INT ? "getInt" : "getString";
  loadFunc->addBodyStatementsList({
    getSaveLoadPathCode(),
    getInstanceCode(),
    "auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);",
    "if (!fileData.isNull()) {",
  }, 0);
  loadFunc->addBodyStatementsList({
    "auto bytes = fileData.getBytes();",
    "auto buffer = std::make_unique<bb::ByteBuffer>(bytes, fileData.getSize());",
    "auto size = buffer->getLong();",
    "auto dataSize = buffer->getInt();",
    "for (int i = 0; i < size; ++i) {",
  }, 1);
  loadFunc->addBodyStatementsList({
    "auto dataId = buffer->" + getID +"();",
    getClassName() + " *data = nullptr;",
    "if (dict->count(dataId)) {",
    "\tdata = dict->at(dataId);",
    "}", "for (int j = 0; j < dataSize; ++j) {",
    "\tstring key = buffer->getString();",
    "\tstring value = buffer->getString();",
    "\tif (data != nullptr) {",
    
  }, 2);
  
  
  int count = 0;
  for (auto schema : p_dataSchemas) {
    if (schema->isWritable() && schema->getType() != ID) {
      auto parser = ExcelParserBase::createWithSchema(schema, p_idName);
      parser->addLoadFuncBody(loadFunc, count == 0);
      count++;
      delete parser;
    }
  }
    
  loadFunc->addBodyStatementsList({
    "\t\t\t\t}","\t\t\t}", "\t\t}", "\t}", "}", "return true;"
  }, 0);
  
  p_class->addFunction(loadFunc, false);
}

void ExcelDataIdBasedParser::setSaveFunction(const CPPVariable* pathVar)
{
  auto saveFunc = new CPPFunction("saveData", TYPE_BOOL, {pathVar}, true, false);
  saveFunc->addBodyStatementsList({
    getSaveLoadPathCode(),
    getInstanceCode(),
    "auto buffer = std::make_unique<bb::ByteBuffer>();",
    "buffer->putLong(dict->size());",
    "buffer->putInt(" + to_string(p_needSaveDataNumber) + ");",
    "for (auto iter = dict->begin(); iter != dict->end(); iter++) {"
  }, 0);
  string putID = p_idSchema->getSubtype() == TYPE_INT ? "putInt" : "putString";
  saveFunc->addBodyStatementsList({
    "auto dataId = iter->first;",
    "auto data = iter->second;",
    "buffer->" + putID + "(dataId);",
  }, 1);
  
  int count = 0;
  for (auto schema : p_dataSchemas) {
    if (schema->isWritable() && schema->getType() != ID) {
      auto parser = ExcelParserBase::createWithSchema(schema, p_idName);
      parser->addSaveFuncBody(saveFunc);
      count++;
      delete parser;
    }
  }
  
  saveFunc->addBodyStatementsList({
    "}","buffer->writeToFile(filePath);", "return true;",
  }, 0);
  p_class->addFunction(saveFunc, false);
}


void ExcelDataIdBasedParser::setClearFunction()
{
  // clear data
  auto clearFunc = new CPPFunction("clearData", TYPE_BOOL, {}, true, false);
  clearFunc->addBodyStatementsList({
    "if (" + staticMapName + " != nullptr) {",
    "\tfor (auto iter = " + staticMapName + "->begin(); iter != " + staticMapName + "->end(); ++iter) {",
    "\t\tauto data = iter->second;",
    "\t\tdelete data;",
    "\t}",
    "\tdelete " + staticMapName + ";",
    "\t" + staticMapName + " = nullptr;",
    "}",
    "return true;",
  }, 0);
  p_class->addFunction(clearFunc, false);
}

void ExcelDataIdBasedParser::addDataLoadFunction(CPPClass* dataManager) const
{
  string retrieveFuncName = "get" + p_className + "ById";
  CPPVariable* retrieveArg = nullptr;
  
  auto id_schema_type = p_idSchema->getSubtype();
  if (id_schema_type == TYPE_INT) {
    retrieveArg = new CPPVariable(p_idName, id_schema_type);
  } else {
    retrieveArg = new CPPVariable(p_idName, "const string&");
  }
  
  auto retrieveFunc = new CPPFunction(retrieveFuncName, p_classTypeName, {retrieveArg}, true, false);
  retrieveFunc->addBodyStatementsList({
    make_pair("if (" + p_className + "::getSharedDictionary()->count(" + p_idName + ")) {", 0),
    make_pair("return " + p_className + "::getSharedDictionary()->at(" + p_idName + ");", 1),
    make_pair("}", 0),
    make_pair("return nullptr;", 0),
  });
  dataManager->addFunction(retrieveFunc, false);
  
  if (id_schema_type == TYPE_INT) {
    retrieveArg = new CPPVariable(p_idName, "const string&");
    retrieveFunc= new CPPFunction(retrieveFuncName, p_classTypeName, {retrieveArg}, true, false);
    retrieveFunc->addBodyStatementsList({
      "if (" + p_idName + ".length() == 0) return nullptr;",
      "return " + p_className + "::" + retrieveFuncName + "(atoi(" + p_idName + ".c_str()));",
    }, 0);
    dataManager->addFunction(retrieveFunc, false);
  }
}


void ExcelDataIdBasedParser::addRegisterDataFunction()
{
  auto id_schema_type = p_idSchema->getSubtype();
  vector<const CPPVariable *> variables;
  vector<pair<std::string, int>> registerBodyList;
  registerBodyList.push_back(make_pair("if (!getSharedDictionary()) {", 0));
  registerBodyList.push_back(make_pair("return nullptr;", 1));
  registerBodyList.push_back(make_pair("}", 0));
  if (id_schema_type == TYPE_STRING) {
    variables.push_back(new CPPVariable(p_idName, "const string&"));
    registerBodyList.push_back(make_pair("if (p_sharedDictionary->count(" + p_idName + ") > 0) {", 0));
    registerBodyList.push_back(make_pair("return nullptr;", 1));
    registerBodyList.push_back(make_pair("}", 0));
    registerBodyList.push_back(make_pair("auto data = new " + p_className + "();", 0));
    registerBodyList.push_back(make_pair("data->p_" + p_idName + " = " + p_idName + ";", 0));
  } else {
    registerBodyList.push_back(make_pair("int maxId = 0;", 0));
    registerBodyList.push_back(make_pair("if (p_sharedDictionary->size() > 0) {", 0));
    registerBodyList.push_back(make_pair("for (auto iter : *p_sharedDictionary) {", 1));
    registerBodyList.push_back(make_pair("if (iter.first >= maxId) {", 2));
    registerBodyList.push_back(make_pair("maxId = iter.first + 1;", 3));
    registerBodyList.push_back(make_pair("}", 2));
    registerBodyList.push_back(make_pair("}", 1));
    registerBodyList.push_back(make_pair("}", 0));
    registerBodyList.push_back(make_pair("auto data = new " + p_className + "();", 0));
    registerBodyList.push_back(make_pair("data->p_" + p_idName + " = maxId;", 0));
  }
  
  for (auto schema : p_dataSchemas) {
    if (schema->getType() != ID) {
      auto parser = ExcelParserBase::createWithSchema(schema, p_idName);
      variables.push_back(new CPPVariable(schema->getName(), parser->getType()));
      registerBodyList.push_back(make_pair("data->" + parser->getVariableName() + " = " + schema->getName()+";", 0));
      delete parser;
    }
  }
  
  if (id_schema_type == TYPE_STRING) {
    registerBodyList.push_back(make_pair("p_sharedDictionary->insert(make_pair(data->getId(), data));", 0));
  } else {
    registerBodyList.push_back(make_pair("p_sharedDictionary->insert(make_pair(maxId, data));", 0));
  }
  registerBodyList.push_back(make_pair("return data;", 0));
  
  auto registerFunc = new CPPFunction("register" + p_className, p_classTypeName, variables, true, false);
  registerFunc->addBodyStatementsList(registerBodyList);
  p_class->addFunction(registerFunc, false);
  
  CPPVariable* retrieveArg = nullptr;
  if (id_schema_type == TYPE_INT) {
    retrieveArg = new CPPVariable(p_idName, id_schema_type);
  } else {
    retrieveArg = new CPPVariable(p_idName, "const string&");
  }
  auto unregisterFunc = new CPPFunction("remove" + p_className + "ById", TYPE_BOOL, {retrieveArg}, true, false);
  unregisterFunc->addBodyStatementsList({
    make_pair("if (getSharedDictionary() != nullptr && p_sharedDictionary->count(" + p_idName + ")) {", 0),
    make_pair("p_sharedDictionary->erase(" + p_idName + ");", 1),
    make_pair("return true;", 1),
    make_pair("}", 0),
    make_pair("return false;", 0),
  });
  p_class->addFunction(unregisterFunc, false);
}

void ExcelDataIdBasedParser::addSetFieldFunction(CPPFunction* setFieldFunc) const
{
  string prefix = setFieldFunc->flag++ == 0 ? "" : "} else ";
  setFieldFunc->addBodyStatements(prefix + "if (dataSet == \"" + p_className + "\") {");
  setFieldFunc->addBodyStatements("auto data = " + p_className + "::get" + p_className + "ById(id);", 1);
  setFieldFunc->addBodyStatements("data->setFieldValue(fieldName, value);", 1);
}

void ExcelDataIdBasedParser::addGetFieldFunction(CPPFunction* getFieldFunc) const
{
  string prefix = getFieldFunc->flag++ == 0 ? "" : "} else ";
  getFieldFunc->addBodyStatements(prefix + "if (dataSet == \"" + p_className + "\") {");
  getFieldFunc->addBodyStatements("return " + p_className + "::get" + p_className + "ById(id);", 1);
}
