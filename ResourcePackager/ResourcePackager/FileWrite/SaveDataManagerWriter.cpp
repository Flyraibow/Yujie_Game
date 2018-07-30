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

SaveDataManagerWriter::SaveDataManagerWriter(const string &fileName)
{
  p_file = new CPPFileComplete(fileName);
  p_mainClass = new CPPClass(fileName);
  //(const string &funcName, const string &returnType,const vector<const CPPVariable *> &arguments, bool isStatic, bool isConst)
  auto indexVar = new CPPVariable("index", TYPE_INT);
  p_saveFunc = new CPPFunction("saveData", TYPE_BOOL, {indexVar}, true, false);
  p_loadFunc = new CPPFunction("loadData", TYPE_BOOL, {indexVar}, true, false);
  p_clearFunc = new CPPFunction("clearData", TYPE_BOOL, {}, true, false);
  p_file->addHeaders("sys/types.h", false, false);
  p_file->addHeaders("sys/stat.h", false, false);
  p_file->addHeaders("unistd.h", false, false);
  p_file->addHeaders("cocos2d.h", true, false);
  
  p_saveFunc->addBodyStatementsList({
    "string path = cocos2d::FileUtils::getInstance()->getWritablePath() + \"/\" + to_string(index);",
    "struct stat st = {0};",
    "if (stat(path.c_str(), &st) == -1) {",
  }, 0);
  p_saveFunc->addBodyStatements("mkdir(path.c_str(), 0700);", 1);
  p_saveFunc->addBodyStatements("}", 0);
  
  
  p_loadFunc->addBodyStatementsList({
    "string path = cocos2d::FileUtils::getInstance()->getWritablePath() + \"/\" + to_string(index);",
    "struct stat st = {0};",
    "if (stat(path.c_str(), &st) == -1) {",
  }, 0);
  p_loadFunc->addBodyStatements("CCLOG(\"Failed to load data, there is no folder %s\", path.c_str());", 1);
  p_loadFunc->addBodyStatements("return false;", 1);
  p_loadFunc->addBodyStatements("}", 0);
}

void SaveDataManagerWriter::addExcel(const ExcelDataParserBase *excel)
{
  if (excel->containWritableData()) {
    string fileName = excel->getClassName();
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
  }
}

void SaveDataManagerWriter::writeToPath(const std::string &path)
{
  p_saveFunc->addBodyStatements("return true;");
  p_loadFunc->addBodyStatements("return true;");
  p_clearFunc->addBodyStatements("return true;");
  p_mainClass->addFunction(p_saveFunc, false);
  p_mainClass->addFunction(p_loadFunc, false);
  p_mainClass->addFunction(p_clearFunc, false);
  p_file->addClass(p_mainClass);
  p_file->saveFiles(path);
}
