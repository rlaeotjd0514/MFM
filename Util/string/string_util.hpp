#pragma once
#include <string_view>
#include <string>
using namespace std;
namespace string_util {
    inline string_view findjsonstring(const string_view rawdata, const string_view key) {
        const auto startidx = rawdata.find(key);
        if(startidx == std::string_view::npos) return {};
        const auto start = rawdata.substr(startidx + key.size());
        const auto endidx = start.find("\"");
        if(endidx == std::string_view::npos) return {};
        const std::string_view _ret = start.substr(0, endidx);
        return _ret;
    }
}
