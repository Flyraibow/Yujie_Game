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
#include "ExcelData.hpp"

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
    for (int i = 0; i < files.size(); ++i) {
        string fileName = files[i];
        string path = excelFolderPath + fileName;
        string fileNameWithoutExt = fileName.substr(0, fileName.find_last_of("."));
        string saveFileName = fileNameWithoutExt + ".dat";
        auto excelData = ExcelData::createWithPath(path);
        excelData->saveData(excelExportDataFolderPath, saveFileName, baseLanguage);
        excelData->generateCode(excelExportCodeFolderPath, fileNameWithoutExt);
    }

    langWriter.writeLanguageData(baseLanguage, baseLanguageOutput);
}
