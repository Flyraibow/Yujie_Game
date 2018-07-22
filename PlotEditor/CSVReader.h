#ifndef _CSV_READER_H_
#define _CSV_READER_H_

#include <vector>
#include <string>
#include <fstream>

std::vector<std::wstring> SplitString(const std::wstring & input) {
    std::vector<std::wstring> output;
    std::wstring::const_iterator left, right;
    left = right = input.begin();
    while (right != input.end()) {
        if (*right == L',') {
            output.emplace_back(left, right);
            left = right;
            ++left;
        }
        ++right;
    }
    output.emplace_back(left, right);
    return output;
}

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