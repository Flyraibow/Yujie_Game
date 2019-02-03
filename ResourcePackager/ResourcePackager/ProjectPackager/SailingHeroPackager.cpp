//
//  SailingHeroPackager.cpp
//  ResourcePackager
//
//  Created by Yujie Liu on 5/16/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#include <iostream>
#include "SailingHeroPackager.hpp"
#include "LanguageData.hpp"
#include "LanguageWriter.hpp"
#include "Utils.hpp"
#include "ExcelDataParserBase.hpp"
#include "SaveDataManagerWriter.hpp"

void SailingHeroPackager::startPackage()
{
  readBaseFiles();
}

void SailingHeroPackager::readBaseFiles()
{
  string baseLanguagePath = get_dataSourcePath() + "/Base/translation.csv";
  string baseLanguageOutput = get_outputResourcePath() + "/base/translation/";
  cout << "read base language: " << baseLanguagePath << endl;
  auto baseLanguage = LanguageData(baseLanguagePath);
  LanguageWriter langWriter;
  
  string excelFolderPath = get_dataSourcePath() + "/BaseExcel/";
  string excelExportDataFolderPath = get_outputResourcePath() + "/base/data/";
  string excelExportCodeFolderPath = get_outputCodeFolderPath();
  vector<string> files = utils::getCSVFileList(excelFolderPath);
  
  auto saveDataFile = SaveDataManagerWriter("SHDataManager", "gameData_");
  for (int i = 0; i < files.size(); ++i) {
    string fileName = files[i];
    string path = excelFolderPath + fileName;
    auto excelData = ExcelDataParserBase::createWithPath(path);
    excelData->saveData(excelExportDataFolderPath, baseLanguage);
    excelData->generateCode(excelExportCodeFolderPath);
    saveDataFile.addExcel(excelData);
  }
  // generate global excel data
  auto globalSaveDataFile = SaveDataManagerWriter("SHGlobalDataManager", "globalData");
  excelFolderPath = get_dataSourcePath() + "/GlobalExcel/";
  files = utils::getCSVFileList(excelFolderPath);
  for (int i = 0; i < files.size(); ++i) {
    string fileName = files[i];
    string path = excelFolderPath + fileName;
    auto excelData = ExcelDataParserBase::createWithPath(path);
    excelData->saveData(excelExportDataFolderPath, baseLanguage);
    excelData->generateCode(excelExportCodeFolderPath);
    globalSaveDataFile.addExcel(excelData);
  }
  
  langWriter.writeLanguageData(baseLanguage, baseLanguageOutput);
  saveDataFile.writeToPath(excelExportCodeFolderPath);
  globalSaveDataFile.writeToPath(excelExportCodeFolderPath);
}

