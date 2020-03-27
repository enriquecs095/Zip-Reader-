#ifndef ZIPREADER_H
#define ZIPREADER_H

#include <QMainWindow>
#include <fstream>
#include <cstring>
#include <ctime>
#include <zip.h>
#include <zlib.h>
#include "DiskData.h"
#include <sys/stat.h>

using namespace std;

namespace Ui {
class ZipReader;
}

class ZipReader : public QMainWindow{
    Q_OBJECT

public:
    explicit ZipReader(QWidget *parent = nullptr);
    ~ZipReader();
    void Read();


private slots:
    void on_Show_clicked();

    void on_Next_clicked();

    void on_Return_clicked();

    void on_Decompress_clicked();

    void on_DecompressAll_clicked();

private:
    Ui::ZipReader *ui;
    //
    DiskData* DiskR;
    int countDelimiter;
    string NameOfFile;
    //Local Header
    char Name[5];
    uint16_t Version;
    uint16_t Bitflag;
    uint16_t CompressionM;
    uint16_t FileT;
    uint16_t FileD;
    uint32_t CRC;
    uint32_t CompressedSize;
    uint32_t UncompressedSize;
    uint16_t Flength;
    uint16_t FieldLength;
    char*  FilenameH;
    char* ExtrafieldH;
    char* CompressData;//no la estoy usando aun
    //Local Header
    /////
    //Central directory
    char signatureCentral[5];
    uint16_t VersionMade;
    uint16_t VersionNeeded;
    uint16_t GeneralVersionBF;
    uint16_t CompressionMethod;
    uint16_t LastModeFT;
    uint16_t LasModeFD;
    uint32_t CRC32;
    uint32_t CompressedSizeCD;
    uint32_t UncompressedSizeCD;
    uint16_t FlengthCD;//esto lo necesito
    uint16_t FieldLengthCD;//esto tambien
    uint16_t CommentLengthCD;//esto tambien
    uint16_t NumberDiskCD;
    uint16_t InternalFileA;
    uint32_t ExternalFileA;
    uint32_t OffsetLocalHeader;
    char* Filename;
    char* Extrafield;
    char* Comment;
    //Central directory
    /////
    //end of central directory
    char signatureEnd[5];
    uint16_t NumberDisk;
    uint16_t NumberDiskS;
    uint16_t NumberEntriesD;//esto es la cantidad de archivos
    uint16_t NumberEntries;//esto es la cantidad de archivos
    uint32_t SizeCentralDirectory;
    uint32_t OffsetCentralDirectory;
    uint16_t CommentLength;
    char* comment;
    //end of cetral directory
    char* BufferLocalFile;
    char* BufferEndHeader;
    char* BufferCentralDirectory;
    int Position;
    //
    ifstream FileCD;
    ifstream FileLH;
    ofstream NewFile;
    void UnPack(int);
    void setBuffer(const char*,int);
    int Eof();
    void getEndDirectory();
    void ReadEndHeader();
    void ReadCentralDirectory();
    void ReadLocalHeader();
    void Print2();
    void ReleaseMemory();
    bool OpenFile();
    void CloseFile();
    void Print();
    void Decompress(const char*,const char*);
    void ReduceName();
    int SizeDir(int);
    std::string ReduceNameDir(int,const char*);
};

#endif // ZIPREADER_H
