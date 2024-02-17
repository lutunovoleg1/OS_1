#include <iostream>
#include <vector>
#include <filesystem>
#include "ls.h"

using namespace std;
namespace fs = std::filesystem;

std::vector<std::string> ls(const std::string &path) {
    vector<string> directories = {};
    try {
        for (int j = 1; const auto &entry: fs::directory_iterator(path)) {
            cout << j << ": " << entry.path() << endl;
            directories.push_back(entry.path().string());
        }
    }
    catch (const fs::filesystem_error &e) {
        cout << "Filesystem error: " << e.what() << endl;

    }
    catch (const std::exception &e) {
        cout << "An error occurred: " << e.what() << endl;
    }
    return directories;
}