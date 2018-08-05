//
//  ExcelData2DBasedParser.cpp
//  ResourcePackager
//
//  Created by Yujie Liu on 8/4/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#include "ExcelData2DBasedParser.hpp"
#include "ReadCSV.hpp"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "CPPFile.hpp"
#include "CPPFunction.hpp"

#include "ExcelParserBase.hpp"

CPPFileComplete* ExcelData2DBasedParser::getMainCppFile() const
{
  CPPFileComplete* file = new CPPFileComplete(p_className);
  file->addHeaders("map", false, true);
  file->addHeaders("ByteBuffer.hpp", true, false);
  file->addNamespaces("using namespace std;", true, false);
  return file;
}

CPPClass* ExcelData2DBasedParser::getMainCppClass() const
{
  CPPClass* cppClass = new CPPClass(p_className);
  return cppClass;
}


ExcelData2DBasedParser::ExcelData2DBasedParser(const vector<vector<string>> &excelData):ExcelDataParserBase()
{
  assert(excelData.size() >= 3 && excelData.at(0).size() >= 3);
  string rowIdName = excelData.at(1).at(0);
  rowIdName.erase(remove_if(rowIdName.begin(),rowIdName.end(), invalidChar), rowIdName.end());
  string rowIdType = excelData.at(2).at(0);
  rowIdType.erase(remove_if(rowIdType.begin(),rowIdType.end(), invalidChar), rowIdType.end());
  p_rowIdSchema = new DataSchema(rowIdName, rowIdType, "", false);
  p_rowIdName = rowIdName;
  
  string colIdName = excelData.at(0).at(1);
  colIdName.erase(remove_if(colIdName.begin(),colIdName.end(), invalidChar), colIdName.end());
  string colIdType = excelData.at(0).at(2);
  colIdType.erase(remove_if(colIdType.begin(),colIdType.end(), invalidChar), colIdType.end());
  p_colIdSchema = new DataSchema(colIdName, colIdType, "", false);
  p_colIdName = colIdName;
  
  string isWritable = excelData.at(1).at(2);
  isWritable.erase(remove_if(isWritable.begin(),isWritable.end(), invalidChar), isWritable.end());
  string returnType = excelData.at(1).at(1);
  returnType.erase(remove_if(returnType.begin(),returnType.end(), invalidChar), returnType.end());
  string returnSubType = excelData.at(2).at(2);
  returnSubType.erase(remove_if(returnSubType.begin(),returnSubType.end(), invalidChar), returnSubType.end());
  p_returnSchema = new DataSchema("value", returnType, returnSubType, isWritable == "Y");
  
  for (int i = 3; i < excelData.at(0).size(); ++i) {
    p_colIds.push_back(excelData.at(0).at(i));
  }
  
  for (int i = 3; i < excelData.size(); ++i) {
    p_rowIds.push_back(excelData.at(i).at(0));
    auto row = excelData.at(i);
    vector<string> newVec(row.begin() + 3, row.end());
    p_values.push_back(newVec);
  }
  auto parser = ExcelParserBase::createWithSchema(p_returnSchema, "");
  p_returnType = parser->getType();
  sanityCheck();
}

void ExcelData2DBasedParser::sanityCheck() const
{
  for (int i = 0; i < p_values.size(); ++i) {
    assert(p_values.at(i).size() == p_colIds.size());
  }
  assert(p_colIdSchema->getType() == INT || p_colIdSchema->getType() == STRING);
  assert(p_rowIdSchema->getType() == INT || p_rowIdSchema->getType() == STRING);
}

void ExcelData2DBasedParser::saveData(const string& folderPath,LanguageData &langData)
{
  p_resDataFileName = p_fileNameWithoutExt + ".dat";
  auto buffer = std::make_unique<bb::ByteBuffer>();
  buffer->putLong(p_rowIds.size());
  for (int i = 0; i < p_rowIds.size(); ++i) {
    auto value = p_rowIds.at(i);
    p_rowIdSchema->addValueIntoBuffer(buffer, value);
  }
  
  buffer->putLong(p_colIds.size());
  for (int i = 0; i < p_colIds.size(); ++i) {
    auto value = p_colIds.at(i);
    p_colIdSchema->addValueIntoBuffer(buffer, value);
  }
  for (int i = 0; i < p_values.size(); ++i) {
    auto row = p_values.at(i);
    for (int j = 0; j < p_colIds.size(); ++j) {
      auto value = row.at(j);
      p_returnSchema->addValueIntoBuffer(buffer, value);
    }
  }
  utils::writeBufferToFile(buffer, folderPath, p_resDataFileName);
}

static string staticMapName = "p_sharedDictionary";

void ExcelData2DBasedParser::setInitFunction()
{
  auto rowParser = ExcelParserBase::createWithSchema(p_rowIdSchema, "");
  auto colParser = ExcelParserBase::createWithSchema(p_colIdSchema, "");
  auto returnParser = ExcelParserBase::createWithSchema(p_returnSchema, "");
  string mapDicType = "map<"+ rowParser->getType() + ", map<" + colParser->getType() + "," + p_returnType + ">>";
  string mapDicPointerType = mapDicType + "*";
  auto staticMapVariable = new CPPVariable(staticMapName, mapDicPointerType, true);
  staticMapVariable->setInitialValue("nullptr");
  p_class->addVariable(staticMapVariable, true);
  
  auto initFunction = new CPPFunction("getSharedDictionary", "const " + mapDicPointerType, true);
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
    "vector<" +  rowParser->getType() + "> rowValues;",
    "auto rowCount = buffer->getLong();",
    "for (int i = 0; i < rowCount; ++i) {",
    "\trowValues.push_back(buffer->" + rowParser->getBufferGetString(p_rowIdSchema->getType()) + ");",
    "}",
    "vector<" +  colParser->getType() + "> colValues;",
    "auto colCount = buffer->getLong();",
    "for (int i = 0; i < colCount; ++i) {",
    "\tcolValues.push_back(buffer->" + colParser->getBufferGetString(p_colIdSchema->getType()) + ");",
    "}",
    
    "for (int i = 0; i < rowCount; ++i) {",
    "\tmap<" + colParser->getType() + ", " + p_returnType + "> rowMap;",
    "\tfor (int j = 0; j < colCount; ++j) {",
    "\t\tint value = buffer->" + colParser->getBufferGetString(p_returnSchema->getType()) + ";",
    "\t\trowMap.insert(make_pair(colValues[j], value));",
    "\t}",
    "\tp_sharedDictionary->insert(make_pair(rowValues[i], rowMap));",
    "}",
  }, 2);
  initFunction->addBodyStatements("}", 1);
  initFunction->addBodyStatements("}");
  initFunction->addBodyStatements("return " + staticMapName + ";");
  p_class->addFunction(initFunction, false);
  
  
  locale loc;
  string first_capital_file_name = p_fileNameWithoutExt;
  first_capital_file_name[0] = toupper(first_capital_file_name[0], loc);
  auto rowVariable = new CPPVariable(p_rowIdSchema->getName(), p_rowIdSchema->getStringType());
  auto colVariable = new CPPVariable(p_colIdSchema->getName(), p_colIdSchema->getStringType());
  auto getterFunction = new CPPFunction("get" + first_capital_file_name, returnParser->getType(), {rowVariable, colVariable}, true, false);
  getterFunction->addBodyStatementsList({
    make_pair("auto dict = getSharedDictionary();", 0),
    make_pair("if (dict->count("+ p_rowIdName + ")) {", 0),
    make_pair("if (dict->at(" + p_rowIdName + ").count(" + p_colIdName + ")) {", 1),
    make_pair("return dict->at(" + p_rowIdName + ").at(" + p_colIdName + ");", 2),
    make_pair("} else {", 1),
    make_pair("CCLOGWARN(\"Couldn't find "+ p_colIdName + ": %s in " + first_capital_file_name + "\", to_string(" + p_colIdName + ").c_str());", 2),
    make_pair("}", 1),
    make_pair("} else {", 0),
    make_pair("CCLOGWARN(\"Couldn't find " + p_rowIdName + ": %s in "+first_capital_file_name+"\", to_string(" + p_rowIdName + ").c_str());", 1),
    make_pair("}", 0),
    make_pair("return 0;", 0),
  });
  p_class->addFunction(getterFunction, false);
  
  this->addDataLoadFunction(p_class);
}

string ExcelData2DBasedParser::getInstanceCode() const
{
  return "auto dict = " + getClassName() + "::getSharedDictionary();";
}

void ExcelData2DBasedParser::setLoadFunction(const CPPVariable* pathVar)
{
}

void ExcelData2DBasedParser::setSaveFunction(const CPPVariable* pathVar)
{
}


void ExcelData2DBasedParser::setClearFunction()
{
  
}

void ExcelData2DBasedParser::addDataLoadFunction(CPPClass* dataManager) const
{
}

void ExcelData2DBasedParser::addRegisterDataFunction()
{
}
