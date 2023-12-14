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
       while (bytes<=length)
    {
        Archive OurRar={};
        OurRar.header_crc[0]=buff[bytes];
        OurRar.header_crc[1]=buff[bytes+1];
        OurRar.header_type=buff[bytes+2];
        OurRar.header_flags[0]=buff[bytes+3];
        OurRar.header_flags[1]=buff[bytes+4];
        OurRar.header_size[0]=buff[bytes+5];
        OurRar.header_size[1]=buff[bytes+6];
        int razmer=(int)OurRar.header_size[0]+(int)OurRar.header_size[1];
        if (OurRar.header_type==0x74)
        {
            FILE_HEAD name={};
            int name_len=(int)buff[bytes+26]+(int)buff[bytes+27];
            name.PackSize[0]=buff[bytes+7];
            name.PackSize[1]=buff[bytes+8];
            name.PackSize[2]=buff[bytes+9];
            name.PackSize[3]=buff[bytes+10];
            int size_of_packaged_data=(int)(name.PackSize[0])+(int)(name.PackSize[1])+(int)(name.PackSize[2])+(int)(name.PackSize[3]);
            bytes=bytes+razmer+size_of_packaged_data;
            k+=1;
        }
        else
        {
            bytes=bytes+razmer;
        }
        if (k==3)
        {
            break;
        }
    }
}