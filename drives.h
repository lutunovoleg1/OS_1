#include <iostream>
#include <vector>
#include <fileapi.h>
#include <bitset>

using namespace std;
vector<char> drives() {
    auto bit = bitset<32>(GetLogicalDrives());
    string tmp = bit.to_string();
    reverse(tmp.begin(), tmp.end());
    vector<char> list = {};
    for (int i = 0; i < 32; i++) {
        if (tmp[i] == '1') list.push_back(static_cast<char>('A' + i));
    }
    return list;
}