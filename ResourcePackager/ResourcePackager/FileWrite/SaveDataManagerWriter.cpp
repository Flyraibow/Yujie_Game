//
//  SaveDataManagerWriter.cpp
//  ResourcePackager
//
//  Created by Yujie Liu on 6/27/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#include "SaveDataManagerWriter.hpp"
#include "CPPFile.hpp"

using namespace std;

SaveDataManagerWriter::SaveDataManagerWriter(const string &fileName, const string &prefix)
{
  p_file = new CPPFileComplete(fileName);
  p_mainClass = new CPPClass(fileName);
  //(const string &funcName, const string &returnType,const vector<const CPPVariable *> &arguments, bool isStatic, bool isConst)
  auto indexVar = new CPPVariable("fileName", TYPE_STRING);
  indexVar->setInitialValue("");
  p_saveFunc = new CPPFunction("saveData", TYPE_BOOL, {indexVar}, true, false);
  p_loadFunc = new CPPFunction("loadData", TYPE_BOOL, {indexVar}, true, false);
  p_clearFunc = new CPPFunction("clearData", TYPE_BOOL, {}, true, false);
  
  auto dataSet = new CPPVariable("dataSet", "const string &");
  auto idVariable = new CPPVariable("id", "const string &");
  auto fieldName = new CPPVariable("fieldName", "const string &");
  auto valueVariable = new CPPVariable("value", "const string &");
  p_setFieldFunc = new CPPFunction("setDataField", TYPE_VOID, {dataSet, idVariable, fieldName, valueVariable}, true, false);
  
  p_getFieldFunc = new CPPFunction("getDataField", TYPE_STRING, {dataSet, idVariable, fieldName}, true, false);
  p_getFieldFunc->addBodyStatements("auto data = getData(dataSet, id);");
  p_getFieldFunc->addBodyStatements("if (data != nullptr) {");
  p_getFieldFunc->addBodyStatements("return data->getFieldValue(fieldName);", 1);
  
  p_getDataFunc = new CPPFunction("getData", "BaseData *", {dataSet, idVariable}, true, false);
  p_getDataListFunc = new CPPFunction("getDataList", "vector<BaseData *>", {dataSet}, true, false);
  p_getDataListFunc->addBodyStatements("vector<BaseData *> result;");
  
  p_file->addHeaders("sys/types.h", false, false);
  p_file->addHeaders("sys/stat.h", false, false);
  p_file->addHeaders("unistd.h", false, false);
  p_file->addHeaders("cocos2d.h", true, false);
  
  p_saveFunc->addBodyStatementsList({
    "string path = cocos2d::FileUtils::getInstance()->getWritablePath() + \"/" + prefix + "\" + fileName;",
    "struct stat st = {0};",
    "if (stat(path.c_str(), &st) == -1) {",
  }, 0);
  p_saveFunc->addBodyStatements("mkdir(path.c_str(), 0700);", 1);
  p_saveFunc->addBodyStatements("}", 0);
  
  
  p_loadFunc->addBodyStatementsList({
    "string path = cocos2d::FileUtils::getInstance()->getWritablePath() + \"/" + prefix + "\" + fileName;",
    "struct stat st = {0};",
    "if (stat(path.c_str(), &st) == -1) {",
  }, 0);
  p_loadFunc->addBodyStatements("CCLOG(\"Failed to load data, there is no folder %s\", path.c_str());", 1);
  p_loadFunc->addBodyStatements("return false;", 1);
  p_loadFunc->addBodyStatements("}", 0);
}

void SaveDataManagerWriter::addExcel(const ExcelDataParserBase *excel)
{
  p_file->addHeaders(excel->getClassName() + ".hpp", true, true);
  excel->addDataLoadFunction(p_mainClass);
  string fileName = excel->getClassName();
  if (excel->containWritableData()) {
    p_file->addHeaders(fileName +".hpp", true, false);
    p_saveFunc->addBodyStatements("if (!" + fileName + "::saveData(path)) {");
    p_saveFunc->addBodyStatements("CCLOG(\"Failed to save " + fileName+ ", %s\", path.c_str());", 1);
    p_saveFunc->addBodyStatements("return false;", 1);
    p_saveFunc->addBodyStatements("}");
    
    p_loadFunc->addBodyStatements("if (!" + fileName + "::loadData(path)) {");
    p_loadFunc->addBodyStatements("CCLOG(\"Failed to load " + fileName+ ", %s\", path.c_str());", 1);
    p_loadFunc->addBodyStatements("return false;",1);
    p_loadFunc->addBodyStatements("}");
    
    p_clearFunc->addBodyStatements(fileName + "::clearData();");
    excel->addSetFieldFunction(p_setFieldFunc);
  }
  if (excel->getType() == EXCEL_TYPE_2D) {
    excel->addGetFieldFunction(p_getFieldFunc);
  } else {
    excel->addGetFieldFunction(p_getDataFunc);
  }
  excel->addGetDataListFunction(p_getDataListFunc);
}

void SaveDataManagerWriter::writeToPath(const std::string &path)
{
  p_saveFunc->addBodyStatements("return true;");
  p_loadFunc->addBodyStatements("return true;");
  p_clearFunc->addBodyStatements("return true;");
  
  p_getDataFunc->addBodyStatements("}");
  p_setFieldFunc->addBodyStatements("}");
  p_getDataFunc->addBodyStatements("CCLOGWARN(\"Couldn't recognize %s file\", dataSet.c_str());");
  p_getDataFunc->addBodyStatements("return nullptr;");
  p_setFieldFunc->addBodyStatements("CCLOGWARN(\"Couldn't recognize %s file\", dataSet.c_str());");
  
  p_getDataListFunc->addBodyStatements("} else {");
  p_getDataListFunc->addBodyStatements("CCLOGWARN(\"Couldn't recognize %s file\", dataSet.c_str());", 1);
  p_getDataListFunc->addBodyStatements("}");
  p_getDataListFunc->addBodyStatements("return result;");
  
  p_getFieldFunc->addBodyStatements("}");
  p_getFieldFunc->addBodyStatements("return \"\";");
  
  p_mainClass->addFunction(p_saveFunc, false);
  p_mainClass->addFunction(p_loadFunc, false);
  p_mainClass->addFunction(p_clearFunc, false);
  p_mainClass->addFunction(p_getDataFunc, false);
  p_mainClass->addFunction(p_getFieldFunc, false);
  p_mainClass->addFunction(p_setFieldFunc, false);
  p_mainClass->addFunction(p_getDataListFunc, false);
  p_file->addClass(p_mainClass);
  p_file->saveFiles(path);
}
