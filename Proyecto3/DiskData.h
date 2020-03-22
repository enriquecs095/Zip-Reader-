#ifndef DISKDATA_H
#define DISKDATA_H
#include <QMainWindow>
using namespace std;

class DiskData{
public:
    DiskData(){}
    string nameD;
    string nameShort;
    uint16_t lengthName;
    uint32_t offsetD;
    uint32_t sizeD;
    uint32_t sizeC;
};

#endif // DISKDATA_H
