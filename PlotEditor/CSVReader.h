#ifndef _CSV_READER_H_
#define _CSV_READER_H_

#include <vector>
#include <string>
#include <fstream>

#include "StringParser.h"

class CSVReader {
public:
    typedef std::vector<std::vector<std::wstring>>::iterator iterator;

    CSVReader(const std::wstring & file) {
        std::wifstream ifs(file, std::wifstream::in);
        std::wstring line;
        // skip first line
        std::getline(ifs, line);
        while (std::getline(ifs, line)) {
            data.emplace_back(SplitString(line));
        }
    }

    iterator begin() {
        return data.begin();
    }

    iterator end() {
        return data.end();
    }

private:
    std::vector<std::vector<std::wstring>> data;
};

#endif