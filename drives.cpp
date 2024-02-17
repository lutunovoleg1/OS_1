#include <vector>
#include <fileapi.h>
#include <bitset>
#include "drives.h"
std::vector<char> drives() {
    auto bit = std::bitset<32>(GetLogicalDrives());
    std::string tmp = bit.to_string();
    reverse(tmp.begin(), tmp.end());
    std::vector<char> list = {};
    for (int i = 0; i < 32; i++) {
        if (tmp[i] == '1') list.push_back(static_cast<char>('A' + i));
    }
    return list;
}