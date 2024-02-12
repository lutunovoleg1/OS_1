#include <iostream>
#include <bitset>
#include <vector>
#include <windows.h>
#include <algorithm>

using namespace std;


void printDrives() {
    bitset<32> bit = bitset<32>(GetLogicalDrives());
    string tmp = bit.to_string();
    reverse(tmp.begin(),tmp.end());
    vector<char> list={};
    for(int i=0; i<32; i++){
        if (tmp[i] == '1') list.push_back(static_cast<CHAR>('A'+i));
    }
    for(char i: list)  cout<<i<<":\\"<<endl;
    return;
//    DWORD a = GetLogicalDrives();
//
//    WCHAR buffer[1000];
//    DWORD len = GetLogicalDriveStringsW(1000, buffer);
//    if (len == 0) {
//        cout << "Error";
//        return;
//    }
//    bitset<32> bit = bitset<32>(a);
//    cout << "GetLogicalDrives():" << a << endl;
//    cout << "bitmask: " << bit << endl;
//    wcout << "GetLogicalDrivesStringsW(1000,buffer):";

//    for (wchar_t c: buffer) {
//        if (c != '\0') { // перебираем символы в буфере до символа NULL
//            wcout<<endl<<"element:" << c;
//        } else {
//            wcout << " "; // печатаем пробел между именами дисков
//        }
//    }
//    return;
}

void printDriveInfo(LPWSTR name) {
    string description[7];
    description[0] = "DRIVE_UNKNOWN";
    description[1] = "DRIVE_NO_ROOT_DIR";
    description[2] = "DRIVE_REMOVABLE ";
    description[3] = "DRIVE_FIXED";
    description[4] = "DRIVE_REMOTE";
    description[5] = "DRIVE_CDROM";
    description[6] = "DRIVE_RAMDISK";
    cout << "\nGetDriverTypeA():" << description[GetDriveTypeW(name)];
}

void printDriveInfoMore(LPWSTR name) {

    bitset<32> bit = bitset<32>(GetLogicalDrives());
    string tmp = bit.to_string();
    reverse(tmp.begin(),tmp.end());
    vector<char> list={};
    for(int i=0; i<32; i++){
        if (tmp[i] == '1') list.push_back(static_cast<CHAR>('A'+i));
    }
//    for(char i: list)  cout<<i<<":\\"<<endl;

    printDriveInfo(name);
}

int main() {
//    cout << "1 - print list of drives\n";
//    cout << "2 - info about drive and amount of free place\n";
//    cout << "3 - creating and deleting directory\n";
//    cout << "4 - creating files in new directories\n";
//    cout << "5 - copying and moving files between directories\n";
//    cout << "6 - analysis and modification of file attributes\n";
//    cout << "Enter number:\n";
//    int a = 0;
//    cin >> a;
//    switch (a) {
//        case 1:
//            printDrives();
//            break;
//
//        case 2:
//            printDrives();
//            DWORD a = GetLogicalDrives();
//
//
//    }

//    WCHAR buffer[1000];
//    DWORD len = GetLogicalDriveStringsW(1000, buffer);
//    if (len == 0) {
//        cout << "Error";
//        return -3;
//    }
//    LPWSTR diskName = new WCHAR[3]{buffer[0], ':', '\\'};
//    printDriveInfo(diskName);
//    cout<<endl;
    LPWSTR tmp = new WCHAR[3] {'C',':','\\'} ;
    printDriveInfoMore(tmp);

    return 0;
}
