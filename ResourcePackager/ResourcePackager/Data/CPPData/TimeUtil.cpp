//
//  TimeUtil.cpp
//  ResourcePackager
//
//  Created by Yujie Liu on 5/30/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#include "TimeUtil.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <string>
#include <stdexcept>
#include <iterator>
#include <sstream>
#include <string>

using namespace std;

ostream& formatDateTime(ostream& out, const tm& t, const char* fmt) {
    const time_put<char>& dateWriter = use_facet<time_put<char> >(out.getloc());
    auto n = strlen(fmt);
    if (dateWriter.put(out, out, ' ', &t, fmt, fmt + n).failed()) {
        throw runtime_error("failure to format date time");
    }
    return out;
}

string dateTimeToString(const tm& t, const char* format) {
    stringstream s;
    formatDateTime(s, t, format);
    return s.str();
}

tm now() {
    time_t now = time(0);
    return *localtime(&now);
}
