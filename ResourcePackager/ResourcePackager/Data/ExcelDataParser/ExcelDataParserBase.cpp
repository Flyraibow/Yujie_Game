//
//  ExcelDataParserBase.cpp
//  ResourcePackager
//
//  Created by Yujie Liu on 7/21/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#include "ExcelDataParserBase.hpp"
#include "ExcelDataIdBasedParser.hpp"
#include "ExcelData2DBasedParser.hpp"

#include "ReadCSV.hpp"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "CPPFile.hpp"
#include "ExcelParserBase.hpp"

bool invalidChar (char c)
{
  return !isprint( static_cast<unsigned char>( c ) );
}

DataSchema* isExcelIdBased(const vector<DataSchema *> &schemaList)
{
  for (auto schema : schemaList) {
    if (schema->getType() == ID) {
      return schema;
    }
  }
  return nullptr;
}

string getFileNameWithExt(const string &filePath)
{
  return utils::split(filePath, '/').back();
}

string getFileNameWithoutExt(const string &filePath)
{
  return utils::split(getFileNameWithExt(filePath), '.').front();
}

ExcelDataParserBase* ExcelDataParserBase::createWithPath(const string &filePath)
{
  auto excelData = readCVSBylines(filePath);
  locale loc;
  auto fileName = getFileNameWithoutExt(filePath);
  string first_capital_file_name = fileName;
  first_capital_file_name[0] = toupper(fileName[0], loc);
  // check is it 2d excel
  assert(excelData.size() > 0 && excelData[1].size() > 0);
  static const string TWO_DIMENTION = "2D";
  string firstGrid = excelData.at(0).at(0);
  firstGrid.erase(remove_if(firstGrid.begin(),firstGrid.end(), invalidChar), firstGrid.end());
  if (firstGrid == TWO_DIMENTION) {
    auto data = new ExcelData2DBasedParser(excelData);
    data->p_filePath = filePath;
    data->p_fileNameWithoutExt = fileName;
    data->p_className = first_capital_file_name + "Data";
    data->p_classTypeName = first_capital_file_name + "Data*";
    data->p_variableName = fileName + "Data";
    return data;
  }
  
  // First four lines are defines.
  assert(excelData.size() >= 4);
  auto names = excelData.at(0);
  auto types = excelData.at(1);
  auto subtypes = excelData.at(2);
  auto writables = excelData.at(3);
  assert(names.size() == types.size() && types.size() == subtypes.size() && types.size() == writables.size());
  vector<DataSchema *> schemaList;
  for (int i = 0; i < names.size(); ++i) {
    string schemaName = names[i];
    string schemaType = types[i];
    string writable = writables[i];
    schemaName.erase(remove_if(schemaName.begin(),schemaName.end(), invalidChar), schemaName.end());
    schemaType.erase(remove_if(schemaType.begin(),schemaType.end(), invalidChar), schemaType.end());
    writable.erase(remove_if(writable.begin(),writable.end(), invalidChar), writable.end());
    DataSchema* schema = new DataSchema(schemaName, schemaType, subtypes[i], toupper(writable.at(0)) == 'Y');
    schemaList.push_back(schema);
  }
  
  ExcelDataParserBase* data = nullptr;
  auto idSchema = isExcelIdBased(schemaList);
  if (idSchema != nullptr) {
    data = new ExcelDataIdBasedParser(idSchema);
  } else {
    data = new ExcelDataParserBase();
  }
  vector<vector<string>> values;
  for (int rowIndex = 4; rowIndex < excelData.size(); ++rowIndex) {
    auto row = excelData.at(rowIndex);
    values.push_back(row);
  }
  data->p_filePath = filePath;
  data->p_dataSchemas = schemaList;
  data->p_values = values;
  data->p_fileNameWithoutExt = fileName;
  
  data->p_className = first_capital_file_name + "Data";
  data->p_classTypeName = first_capital_file_name + "Data*";
  data->p_variableName = fileName + "Data";
  return data;
}

string ExcelDataParserBase::getFilePath() const
{
  return p_filePath;
}

string ExcelDataParserBase::getClassName() const
{
  return p_className;
}

vector<DataSchema*> ExcelDataParserBase::getDataSchemas() const
{
  return p_dataSchemas;
}

bool ExcelDataParserBase::containWritableData() const
{
  for (int i = 0; i < p_dataSchemas.size(); ++i) {
    if (p_dataSchemas.at(i)->isWritable()) {
      return true;
    }
  }
  return false;
}

CPPFileComplete* ExcelDataParserBase::getMainCppFile() const
{
  CPPFileComplete* file = new CPPFileComplete(p_className);
  file->addHeaders("cocos2d.h", true, false);
  file->addHeaders("ByteBuffer.hpp", true, false);
  file->addHeaders("Utils.hpp", true, false);
  file->addNamespaces("using namespace Utils;", false, true);
  file->addHeaders("BaseData.h", true, true);
  return file;
}

CPPClass* ExcelDataParserBase::getMainCppClass() const
{
  CPPClass* cppClass = new CPPClass(p_className);
  cppClass->setFatherClass("BaseData");
  return cppClass;
}

void ExcelDataParserBase::generateCode(const string& folderPath)
{
  p_file = this->getMainCppFile();
  p_class = this->getMainCppClass();
  this->setPrepareFunction();
  this->setInitFunction();
  if (p_needSaveDataNumber > 0) {
    auto pathVar = new CPPVariable("path", "const string &");
    this->setSaveFunction(pathVar);
    this->setLoadFunction(pathVar);
    this->setClearFunction();
    this->setSetFieldFunction();
  }
  this->setGetFieldFunction();
  this->setGetFieldDataFunction();
  p_file->addClass(p_class);
  p_file->saveFiles(folderPath);
  delete p_class;
  delete p_file;
  p_file = nullptr;
  p_class = nullptr;
}


void ExcelDataParserBase::saveData(const string& folderPath,LanguageData &langData)
{
  p_resDataFileName = p_fileNameWithoutExt + ".dat";
  auto buffer = std::make_unique<bb::ByteBuffer>();
  for (int i = 0; i < p_values.size(); ++i) {
    auto row = p_values.at(i);
    string id;
    for (int j = 0; j < p_dataSchemas.size(); ++j) {
      DataSchema *schema = p_dataSchemas.at(j);
      auto value = row.at(j);
      schema->addValueIntoBuffer(buffer, value);
    }
  }
  utils::writeBufferToFile(buffer, folderPath, p_resDataFileName);
}

void ExcelDataParserBase::setPrepareFunction()
{
  bool containSet = false;
  bool containVector = false;
  int needSaveDataNumber = 0;
  
  string id_schema_name;  // goodsId;
  string id_schema_type;  // int or string;
  string fileNameWithoutExt = p_resDataFileName.substr(0, p_resDataFileName.find_last_of("."));
  for (auto schema : p_dataSchemas) {
    if (schema->getType() == VECTOR || schema->getType() == FRIEND_ID_VECTOR) {
      containVector = true;
    } else if (schema->getType() == SET || schema->getType() == FRIEND_ID_SET) {
      containSet = true;
    }
    if (schema->getType() != ID && schema->isWritable()) {
      needSaveDataNumber++;
    }
  }
  if (containSet) {
    p_file->addHeaders("set", false, true);
  }
  if (containVector) {
    p_file->addHeaders("vector", false, true);
  }
  p_needSaveDataNumber = needSaveDataNumber;
}

void ExcelDataParserBase::sanityCheck() const
{
  for (auto schema : p_dataSchemas) {
    if (schema->getType() == ID || schema->getType() == LANGUAGE || schema->getType() == ENUM) {
      assert(false);
    }
  }
  if (p_values.size() > 1) {
    assert(false);
  }
}

static string kStaticDataName = "p_sharedData";

void ExcelDataParserBase::setInitFunction()
{
  auto staticMapVariable = new CPPVariable(kStaticDataName, p_classTypeName, true);
  staticMapVariable->setInitialValue("nullptr");
  p_class->addVariable(staticMapVariable, true);
  
  auto initFunction = new CPPFunction("getSharedInstance", p_classTypeName, true);
  auto descFunction = new CPPFunction("description", TYPE_STRING);
  descFunction->addBodyStatements("string desc = \"" + p_variableName + " = {\\n\";");
  const string filePath = "res/base/data/" + p_resDataFileName;
  initFunction->addBodyStatementsList({
    "if (!" + kStaticDataName + ") {"
    
  }, 0);
  initFunction->addBodyStatementsList({
    kStaticDataName + " = new " + p_className + "();",
    "static string resPath = \"" + filePath + "\";",
    "auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);",
    "if (!data.isNull()) {",
  }, 1);
  initFunction->addBodyStatementsList({
    "auto bytes = data.getBytes();",
    "auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());",
  }, 2);
  
  for (auto schema : p_dataSchemas) {
    if (schema->getType() != COMMENT && schema->getType() != ENUM) {
      auto parser = ExcelParserBase::createWithSchema(schema, "");
      parser->setFileNameWithoutExt(p_fileNameWithoutExt);
      parser->addFunctionsInclass(p_class);
      parser->addHeaders(p_file);
      descFunction->addBodyStatements(parser->getDescription());
      parser->addInitFuncBody(initFunction, kStaticDataName, 2);
      delete parser;
    }
  }
  
  descFunction->addBodyStatements("desc += \"}\\n\";");
  descFunction->addBodyStatements("return desc;");
  p_class->addFunction(descFunction, false);
  
  initFunction->addBodyStatements("}", 1);
  initFunction->addBodyStatements("}");
  initFunction->addBodyStatements("return " + kStaticDataName + ";");
  p_class->addFunction(initFunction, false);
}

string ExcelDataParserBase::getSaveLoadPathCode() const
{
  return "auto filePath = path + \"/" + getClassName() + ".dat\";";
}

string ExcelDataParserBase::getInstanceCode() const
{
  return "auto data = " + getClassName() + "::getSharedInstance();";
}

void ExcelDataParserBase::setGetFieldFunction()
{
  auto fieldVar = new CPPVariable("fieldName", "const string &");
  p_getFieldFunction = new CPPFunction("getFieldValue", TYPE_STRING, {fieldVar}, false, true);
  int count = 0;
  for (auto schema : p_dataSchemas) {
    if (schema->getType() != COMMENT && schema->getType() != ENUM) {
      auto parser = ExcelParserBase::createWithSchema(schema, "");
      string prefix = (count > 0) ? "} else " : "";
      p_getFieldFunction->addBodyStatements(prefix + "if (fieldName == \"" + schema->getName() + "\") {");
      parser->addGetFieldValueFuncBody(p_getFieldFunction);
      delete parser;
      ++count;
    }
  }
  if (count > 0) {
    p_getFieldFunction->addBodyStatements("}");
  }
  p_getFieldFunction->addBodyStatements("CCLOGWARN(\"Couldn't recognize %s in " + p_class->getClassName() + "\", fieldName.c_str());");
  p_getFieldFunction->addBodyStatements("return \"\";");
  p_class->addFunction(p_getFieldFunction, false);
}

void ExcelDataParserBase::setSetFieldFunction()
{
  auto fieldVar = new CPPVariable("fieldName", "const string &");
  auto value = new CPPVariable("value", "const string &");
  p_setFieldFunction = new CPPFunction("setFieldValue", TYPE_VOID, {fieldVar, value}, false, false);
  int count = 0;
  for (auto schema : p_dataSchemas) {
    if (schema->isWritable() && schema->getType() != ID) {
      auto parser = ExcelParserBase::createWithSchema(schema, "");
      string prefix = (count > 0) ? "} else " : "";
      p_setFieldFunction->addBodyStatements(prefix + "if (fieldName == \"" + schema->getName() + "\") {");
      parser->addSetFieldValueFuncBody(p_setFieldFunction);
      delete parser;
      ++count;
    }
  }
  if (count > 0) {
    p_setFieldFunction->addBodyStatements("}");
  }
  
  p_class->addFunction(p_setFieldFunction, false);
}

void ExcelDataParserBase::setGetFieldDataFunction()
{
  auto fieldVar = new CPPVariable("fieldName", "const string &");
  p_getFieldDataFunction = new CPPFunction("getDataByField", "BaseData*", {fieldVar}, false, true);
  int count = 0;
  for (auto schema : p_dataSchemas) {
    if (schema->getType() == FRIEND_ID) {
      auto parser = ExcelParserBase::createWithSchema(schema, "");
      string prefix = (count > 0) ? "} else " : "";
      p_getFieldDataFunction->addBodyStatements(prefix + "if (fieldName == \"" + schema->getName() + "\") {");
      parser->addGetFieldDataValueFuncBody(p_getFieldDataFunction);
      delete parser;
      ++count;
    }
  }
  if (count > 0) {
    p_getFieldDataFunction->addBodyStatements("}");
  }
  p_getFieldDataFunction->addBodyStatements("CCLOGWARN(\"Couldn't recognize %s in " + p_class->getClassName() + "\", fieldName.c_str());");
  p_getFieldDataFunction->addBodyStatements("return nullptr;");
  p_class->addFunction(p_getFieldDataFunction, false);
}

void ExcelDataParserBase::setLoadFunction(const CPPVariable* pathVar)
{
  auto loadFunc = new CPPFunction("loadData", TYPE_BOOL, {pathVar}, true, false);
  
  loadFunc->addBodyStatementsList({
    getSaveLoadPathCode(),
    getInstanceCode(),
    "auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);",
    "if (!fileData.isNull()) {",
  }, 0);
  loadFunc->addBodyStatementsList({
    "auto bytes = fileData.getBytes();",
    "auto buffer = std::make_unique<bb::ByteBuffer>(bytes, fileData.getSize());",
    "auto dataSize = buffer->getInt();",
  }, 1);
  loadFunc->addBodyStatementsList({
    "for (int j = 0; j < dataSize; ++j) {",
    "\tstring key = buffer->getString();",
    "\tstring value = buffer->getString();",
    "\tif (data != nullptr) {",
    
  }, 1);
  
  
  int count = 0;
  for (auto schema : p_dataSchemas) {
    if (schema->isWritable()) {
      assert(schema->getType() != ID);
      auto parser = ExcelParserBase::createWithSchema(schema, "");
      parser->addLoadFuncBody(loadFunc, count == 0, "data", 3);
      count++;
      delete parser;
    }
  }
  
  loadFunc->addBodyStatementsList({
    "\t\t\t}", "\t\t}", "\t}", "}", "return true;"
  }, 0);
  
  p_class->addFunction(loadFunc, false);
}

void ExcelDataParserBase::setSaveFunction(const CPPVariable* pathVar)
{
  auto saveFunc = new CPPFunction("saveData", TYPE_BOOL, {pathVar}, true, false);
  saveFunc->addBodyStatementsList({
    getSaveLoadPathCode(),
    getInstanceCode(),
    "auto buffer = std::make_unique<bb::ByteBuffer>();",
    "buffer->putInt(" + to_string(p_needSaveDataNumber) + ");",
  }, 0);
  int count = 0;
  for (auto schema : p_dataSchemas) {
    if (schema->isWritable()) {
      assert(schema->getType() != ID);
      auto parser = ExcelParserBase::createWithSchema(schema, "");
      parser->addSaveFuncBody(saveFunc, "data", 0);
      count++;
      delete parser;
    }
  }
  
  saveFunc->addBodyStatementsList({
    "buffer->writeToFile(filePath);", "return true;",
  }, 0);
  p_class->addFunction(saveFunc, false);
}

void ExcelDataParserBase::setClearFunction()
{
  // clear data
  auto clearFunc = new CPPFunction("clearData", TYPE_BOOL, {}, true, false);
  clearFunc->addBodyStatementsList({
    "if (" + kStaticDataName + " != nullptr) {",
    "\tdelete " + kStaticDataName + ";",
    "\t" + kStaticDataName + " = nullptr;",
    "}",
    "return true;",
  }, 0);
  p_class->addFunction(clearFunc, false);
}

void ExcelDataParserBase::addDataLoadFunction(CPPClass* dataManager) const
{
  auto loadDataFunc = new CPPFunction("get" + p_className, p_classTypeName, {}, true, false);
  loadDataFunc->addBodyStatements("return " + p_className + "::getSharedInstance();");
  dataManager->addFunction(loadDataFunc, false);
}

void ExcelDataParserBase::addSetFieldFunction(CPPFunction* setFieldFunc) const
{
  string prefix = setFieldFunc->getIsEmpty() ? "" : "} else ";
  setFieldFunc->setIsEmpty(false);
  setFieldFunc->addBodyStatements(prefix + "if (dataSet == \"" + p_className + "\") {");
  setFieldFunc->addBodyStatements("auto data = " + p_className + "::getSharedInstance();", 1);
  setFieldFunc->addBodyStatements("data->setFieldValue(fieldName, value);", 1);
}

void ExcelDataParserBase::addGetFieldFunction(CPPFunction* getFieldFunc) const
{
  string prefix = getFieldFunc->getIsEmpty() ? "" : "} else ";
  getFieldFunc->setIsEmpty(false);
  getFieldFunc->addBodyStatements(prefix + "if (dataSet == \"" + p_className + "\") {");
  getFieldFunc->addBodyStatements("return " + p_className + "::getSharedInstance();", 1);
}

void ExcelDataParserBase::addGetDataListFunction(CPPFunction* getDataListFunc) const
{
  
}
