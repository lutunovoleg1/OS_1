#include <iostream>
#include <bitset>
#include <vector>
#include <windows.h>
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

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

vector<string> ls(const string& path) {
    vector<string> directories = {};
    try {
        for (const auto &entry: fs::directory_iterator(path)) {

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

void printDriveInfo(LPCSTR name) {
    string description[7];
    description[0] = "The drive type cannot be determined";
    description[1] = "The root path is invalid";
    description[2] = "The drive has removable media; for example, a floppy drive, thumb drive, or flash card reader.";
    description[3] = "The drive has fixed media; for example, a hard disk drive or flash drive.";
    description[4] = "The drive is a remote (network) drive.";
    description[5] = "The drive is a CD-ROM drive.";
    description[6] = "The drive is a RAM disk.";
    cout << description[GetDriveTypeA(name)];
}

void printDriveInfoMore(LPWSTR name) {


}

void menu() {
    cout << "1 - print list of drives\n";
    cout << "2 - info about drive and amount of free place\n";
    cout << "3 - creating and deleting directory\n";
    cout << "4 - creating files in new directories\n";
    cout << "5 - copying and moving files between directories\n";
    cout << "6 - analysis and modification of file attributes\n";
    cout << "7 - exit from program\n";
    cout << "Enter number:";
    int a;
    cin >> a;
    vector<char> list;
    switch (a) {
        case 1: {
            list = drives();
            for (char i: list) cout << i << ":\\" << endl;
            break;
        }

        case 2: {
            list = drives();
            cout << "Choose drive to see more info";
            for (int j = 1; char i: list) {
                cout << endl << j << ": " << i << ":\\";
                j++;
            }
            cout << endl << "Enter number: ";
            string tmp;
            cin >> tmp;
            int b;
            try {
                b = stoi(tmp);
            }
            catch (const invalid_argument &e) {
                cout << "invalid number";
            }

            char drive[4] = {list[b], ':', '\\', '\0'};
            DWORD serialNumber;
            char systemName[100];
            bool flag = GetVolumeInformationA(drive, nullptr, 0, &serialNumber, nullptr, nullptr, systemName, 100);
            DWORD sectorsPerCluster, bytesPerSector, numberOfFreeClusters, totalNumberOfClusters;
            bool flag1 = GetDiskFreeSpaceA(drive, &sectorsPerCluster, &bytesPerSector, &numberOfFreeClusters,
                                           &totalNumberOfClusters);
            if (!flag || !flag1) {
                cout << "can't get volume information or info about free space";
            } else {
                cout << endl << "serial number: " << serialNumber << endl;
                cout << "system name: " << systemName << endl;
                printDriveInfo(drive);
                cout << endl;
                cout << "sectors per cluster: " << sectorsPerCluster << endl;
                cout << "bytes per sector: " << bytesPerSector << endl;
                cout << "number of free clusters: " << numberOfFreeClusters << endl;
                cout << "total number of clusters: " << totalNumberOfClusters << endl;

            }
        }
            break;
        case 3: {
            list = drives();
            cout << "Select drive to see it's contents";
            for (int j = 1; char i: list) {
                cout << endl << j << ": " << i << ":\\";
                j++;
            }
            cout << endl << "Enter number: ";
            string tmp;
            cin >> tmp;
            int b;
            try {
                b = stoi(tmp) - 1;
            }
            catch (const invalid_argument &e) {
                cout << "invalid number";
                return;
            }
            string path = {list[b], ':', '\\'};
            vector<string> directories = ls(path);
                cout<<"0: Create in this directory";
            for(int j= 0; const string& str: directories){
                cout<< j+1<<": "<<str<<endl;
                j++;
            }
            cout << endl << "Enter number: ";
            string tmp1;
            cin >> tmp1;
            int c;
            try {
                c = stoi(tmp) ;
            }
            catch (const invalid_argument &e) {
                cout << "invalid number";
                return;
            }
            vector<string> list1=ls(&list[c]);
            for(int j= 0; const string& str: directories){
                cout<< j+1<<": "<<str<<endl;
                j++;
            }
            break;
        }
        default:
            cout << "you chose wrong number";
            break;


    }


}

int main() {
    menu();

    return 0;
}
