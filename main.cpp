#include <iostream>
#include <bitset>
#include <vector>
#include <windows.h>
//#include <algorithm>
#include "ls.h"
#include "cdd.h"
#include "drives.h"
#include <filesystem>

namespace fs = std::filesystem;

using namespace std;

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

void printDriveInfoMore(vector<char> list, int b) {
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

    switch (a) {
        case 1: {
            vector<char> list;
            list = drives();
            for (char i: list) cout << i << ":\\" << endl;
            break;
        }

        case 2: {
            vector<char> list;
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
                return;
            }
            printDriveInfoMore(list, b);

        }
            break;
//        case 3: {
//            cdd();
//            break;
//        }
        case 3: {
            cout << "what you want?";
            cout << "1 - create directory\n";
            cout << "2 - remove directory\n";
            string mod;
            cin >> mod;
            for (auto c: mod) {
                if (!isdigit(c)) {
                    throw invalid_argument("it's not number");
                }
            }
            CHAR path[100];
            bool flag1;
            int mod_int = stoi(mod);
            if (mod_int == 1) {
                cout << "Enter path to directory";
                cin >> path;

                flag1 = CreateDirectoryA(path, nullptr);
                if (flag1) {
                    cout << "success";
                } else cout << "smth went wrong" << &GetLastError;
            }
            if (mod_int == 2) {
                cout << "Enter path to directory";
                cin >> path;
                ls(path);
                cout << "Enter path to directory remove directory";
                flag1 = RemoveDirectoryA(path);
                if (flag1) {
                    cout << "success";
                } else cout << "smth went wrong" << &GetLastError;


            }
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
