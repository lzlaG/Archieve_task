#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Archive
{
    unsigned char header_crc[2];
    unsigned char header_type;
    unsigned char header_flags[2];
    unsigned char header_size[2];
};


struct FILE_HEAD
{
    char PackSize[4];
    char UnpSize[4];
    char HostOs;
    char FileCRC[4];
    char FileTime[4];
    char UnpVer;
    char Method;
    unsigned char NameSize[2];
    char FileAttr[4];
};


int main()
{
    ifstream file("Example.rar",ios::binary);
    if (!file)
    {
        cout << "Файл не открыт";
    }
    cout << "Файл успешно открылся" << "\n";
    file.seekg(0, ios::end);
    int length=file.tellg();
    file.seekg(0, ios::beg);
    unsigned char* buff = new unsigned char[length];
    file.read((char*)buff, length);
    file.close();
    int bytes=0;
    int k=0;
}