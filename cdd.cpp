#include "cdd.h"
#include <iostream>
#include <vector>
#include "drives.h"
#include "ls.h"

using namespace std;

void cdd() {
    vector<char> list;
    list = drives();
    bool flag = true;
    string path;
    vector<string> directories;
    cout << "Select drive to see it's contents";

    cout << endl << "Enter number: ";
    string tmp, tmp1;
    cin >> tmp;
    int b;
    bool flag1 = true;
    for (auto c: tmp) {
        if (!isdigit(c)) {
            flag1 = false;
            break;
        }
    }
    if (flag1) {
        b = stoi(tmp) - 1;
        path = {list[b], ':', '\\'};
    } else {
        cout << "invalid number";
        flag = false;
    }

    while (flag) {

        directories = ls(path);
        cout << "0: Create in this directory";
        for (int j = 1; const string &str: directories) {
            cout << j << ": " << str << endl;
            j++;
        }
        cout << directories.size() + 1 << ": " << "exit";
        cout << endl << "Enter number: ";

        cin >> tmp1;
        int c;
        try {
            c = stoi(tmp1);
        }
        catch (const invalid_argument &e) {
            cout << "invalid number";
            return;
        }
        vector<string> list1 = ls(&list[c]);
        for (int j = 0; const string &str: directories) {
            cout << j + 1 << ": " << str << endl;
            j++;
        }
    }
}