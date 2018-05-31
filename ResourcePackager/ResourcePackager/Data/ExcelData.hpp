//
//  ExcelData.hpp
//  ResourcePackager
//
//  Created by Yujie Liu on 5/28/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#ifndef ExcelData_hpp
#define ExcelData_hpp

#include <string>
#include <vector>
#include <unordered_map>
#include "DataSchema.hpp"
#include "LanguageData.hpp"

using namespace std;

class ExcelData
{
private:
    string m_filePath;
    vector<DataSchema *> m_dataSchemas;
    vector<vector<string>> m_values;
public:
    string getFilePath() const;
    vector<DataSchema *> getDataSchemas() const;

    void saveData(const string& folderPath, const string& fileName, LanguageData &langData) const;
    void generateCode(const string& folderPath, const string& fileName) const;
    
    static ExcelData* createWithPath(const string &filePath);
};

#endif /* ExcelData_hpp */
