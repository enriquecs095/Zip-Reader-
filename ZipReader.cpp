#include "ZipReader.h"

ZipReader::ZipReader(){
    BufferLocalFile=new char[30];//cambiara
    BufferEndHeader=new char[22];
    BufferCentralDirectory=new char[46];//cambiara
    //Local Header
    Name[0]=0;
    Version=0;
    Bitflag=0;
    CompressionM=0;
    FileT=0;
    FileD=0;
    CRC=0;
    CompressedSize=0;
    UncompressedSize=0;
    Flength=0;
    FieldLength=0;
    //Central data
    signatureCentral[0]=0; 
    VersionMade=0;
    VersionNeeded=0;
    GeneralVersionBF=0;
    CompressionMethod=0;
    LastModeFT=0;
    LasModeFD=0;
    CRC32=0;
    CompressedSizeCD=0;
    UncompressedSizeCD=0;
    FlengthCD=0;
    FieldLengthCD=0;
    CommentLengthCD=0;
    NumberDiskCD=0;
    InternalFileA=0;
    ExternalFileA=0;
    OffsetLocalHeader=0;
     //final data
    signatureEnd[0]=0;
    NumberDisk=0;
    NumberDiskS=0;
    NumberEntriesD=0;
    NumberEntries=0;
    SizeCentralDirectory=0;
    OffsetCentralDirectory=0;
    CommentLength=0;
    //
    Position=0;
}

void ZipReader::Read(){
    if(!OpenFile()){return;};
    ReadEndHeader();
    ReadCentralDirectory();
    CloseFile();
}

void ZipReader::getEndDirectory(){
    Eof();
    char a;
    char signature[5];
    signature[4]=0;
    int count=0,i=1;
    while(1){
        FileCD.seekg(Position-i-1,ios::beg);
        FileCD.get(a);
        if(count==4){Position=FileCD.tellg(); break;}
        if(a==6){signature[3]=a;count++;}
        if(a==5){signature[2]=a;count++;}
        if(a==75){signature[1]=a;count++;}
        if(a==80){signature[0]=a;count++;}
        i++;
    }
}

void ZipReader::setBuffer(const char* data, int n){
    if(n==1){ memcpy(BufferLocalFile,data,30);}
    else if(n==2){ memcpy(BufferCentralDirectory,data,46);}
    else if(n==3){ memcpy(BufferEndHeader,data,22);}
    else if(n==4){ Filename=new char[FlengthCD+1];Filename[FlengthCD]=0; memcpy(Filename,data,FlengthCD);}
    else if(n==5){ Extrafield=new char[FieldLengthCD+1];Extrafield[FieldLengthCD]=0; memcpy(Extrafield,data,FieldLengthCD);}
    else if(n==6){ Comment =new char[strlen(data)+1]; memcpy(Comment,data,CommentLengthCD);}
    else if(n==7){ FilenameH=new char[Flength+1]; FilenameH[Flength]=0; memcpy(FilenameH,data,Flength); }
    else if(n==8){ ExtrafieldH=new char[FieldLength+1];ExtrafieldH[FieldLength]=0; memcpy(ExtrafieldH,data,FieldLength); }
}

void ZipReader::ReadEndHeader(){
    getEndDirectory();
    char buffer[22];
    FileCD.seekg(Position,ios::beg);
    FileCD.read(buffer,sizeof(buffer));
    setBuffer(buffer,3);
    UnPack(3);
    Print();//imprimo solo una vez la info
}

void ZipReader::UnPack(int n){
    if(n==1){
        char* copy=BufferLocalFile;
        memcpy(&Name,copy,4);
        copy+=4;
        memcpy(&Version,copy,2);
        copy+=2;
        memcpy(&Bitflag,copy,2);
        copy+=2;
        memcpy(&CompressionM,copy,2);
        copy+=2;
        memcpy(&FileT,copy,2);
        copy+=2;
        memcpy(&FileD,copy,2);
        copy+=2;
        memcpy(&CRC,copy,4);
        copy+=4;
        memcpy(&CompressedSize,copy,4);
        copy+=4;
        memcpy(&UncompressedSize,copy,4);
        copy+=4;
        memcpy(&Flength,copy,2);
        copy+=2;
        memcpy(&FieldLength,copy,2);
        copy+=2;
    }else if(n==2){
        char *copy=BufferCentralDirectory;
        memcpy(&signatureCentral,copy,4);
        copy+=4;
        memcpy(&VersionMade,copy,2);
        copy+=2;
        memcpy(&VersionNeeded,copy,2);
        copy+=2;
        memcpy(&GeneralVersionBF,copy,2);
        copy+=2;
        memcpy(&CompressionMethod,copy,2);
        copy+=2;
        memcpy(&LastModeFT,copy,2);
        copy+=2;
        memcpy(&LasModeFD,copy,2);
        copy+=2;
        memcpy(&CRC32,copy,4);
        copy+=4;
        memcpy(&CompressedSizeCD,copy,4);
        copy+=4;
        memcpy(&UncompressedSizeCD,copy,4);
        copy+=4;
        memcpy(&FlengthCD,copy,2);
        copy+=2;
        memcpy(&FieldLengthCD,copy,2);
        copy+=2;
        memcpy(&CommentLengthCD,copy,2);
        copy+=2;
        memcpy(&NumberDiskCD,copy,2);
        copy+=2;
        memcpy(&InternalFileA,copy,2);
        copy+=2;
        memcpy(&ExternalFileA,copy,4);
        copy+=4;
        memcpy(&OffsetLocalHeader,copy,4);
        copy+=4;
    }else if(n==3){
        char *copy=BufferEndHeader;
        memcpy(&signatureEnd,copy,4);
        copy+=4;
        memcpy(&NumberDisk,copy,2);
        copy+=2;
        memcpy(&NumberDiskS,copy,2);
        copy+=2;
        memcpy(&NumberEntriesD,copy,2);
        copy+=2;
        memcpy(&NumberEntries,copy,2);
        copy+=2;
        memcpy(&SizeCentralDirectory,copy,4);
        copy+=4;
        memcpy(&OffsetCentralDirectory,copy,4);
        copy+=4;
        memcpy(&CommentLength,copy,2);
        copy+=2;
    }
}

void ZipReader::Print(){
   cout<<"Name last header: "<<signatureEnd<<"\n" 
   <<"Number of this disk: "<<NumberDisk<<"\n"
   <<"Number of the disk in the start: "<<NumberDiskS<<"\n"
   <<"Number of the entries on this disk: "<<NumberEntriesD<<"\n"
   <<"Number of the entries: "<<NumberEntries<<"\n"
   <<"Size of the central directory: "<<SizeCentralDirectory<<"\n"
   <<"Offset of the start: "<<OffsetCentralDirectory<<"\n"
   <<"Comment length: "<<CommentLength<<"\n\n";
}

int ZipReader::Eof(){
    FileCD.seekg(0,ios::end);
    return Position=FileCD.tellg();
}

void ZipReader::ReadCentralDirectory(){
    char buffer[46];
    FileCD.seekg(OffsetCentralDirectory,ios::beg);
     for (int i = 0; i < NumberEntriesD; i++){
        FileCD.read(buffer,sizeof(buffer));
        setBuffer(buffer,2);
        UnPack(2);
        char filename[FlengthCD];
        FileCD.read(filename,sizeof(filename));
        setBuffer(filename,4);
        if(FieldLengthCD>0){  
            char extraField[FieldLengthCD];
            FileCD.read(extraField,sizeof(extraField));
            setBuffer(extraField,5);
            }
        if(CommentLengthCD>0){ 
            char comment[CommentLengthCD];
            FileCD.read(comment,sizeof(comment));
            setBuffer(comment,6);
        }    
        ReadLocalHeader();
        Print2();
        ReleaseMemory();
     }
}

void ZipReader::ReadLocalHeader(){
    char buffer[30];
    FileLH.seekg(OffsetLocalHeader,ios::beg);
    FileLH.read(buffer,sizeof(buffer));
    setBuffer(buffer,1);
    UnPack(1);
    char filename[Flength];
    FileLH.read(filename,sizeof(filename));
    setBuffer(filename,7);
    //aqui voy a poner la condicion si es una carpeta
    if(Extrafield>0){ 
        char extraField[FieldLength]; 
        FileLH.read(extraField,sizeof(Extrafield));
        setBuffer(extraField,8);
    }
    if(CompressedSize>0){
        char data[CompressedSize];
        FileLH.read(data,sizeof(data));
    }
}

void ZipReader::Print2(){
    cout<<"Name central directory: "<<signatureCentral<<"\n" 
   <<"Version made: "<<VersionMade<<"\n"
   <<"Version needed: "<<VersionNeeded<<"\n"
   <<"Bit flag: "<<GeneralVersionBF<<"\n"
   <<"Compression Method: "<<CompressionMethod<<"\n"
   <<"Last modification: "<<LastModeFT<<"\n"
   <<"Last modification: "<<LasModeFD<<"\n"
   <<"CRC32: "<<CRC32<<"\n"
   <<"Compressed Size: "<<CompressedSizeCD<<"\n"
   <<"Uncompressed Size: "<<UncompressedSizeCD<<"\n"
   <<"Filename length: "<<FlengthCD<<"\n"
   <<"Field length: "<<FieldLengthCD<<"\n"
   <<"Longitud de comentarios: "<<CommentLengthCD<<"\n"
   <<"Number of disks: "<<NumberDiskCD<<"\n"
   <<"Internal file: "<<InternalFileA<<"\n"
   <<"External file: "<<ExternalFileA<<"\n"
   <<"Offset local header: "<<OffsetLocalHeader<<"\n"
   <<"Filename: "<<Filename<<"\n";
      if(FieldLengthCD>0){cout<<"Field: "<<Extrafield<<"\n";}
      if(CommentLengthCD>0){cout<<"Comments: "<<Comment<<"\n";}
      cout<<"\n";
    
   cout<<"Name: "<<Name<<"\n" 
   <<"Version: "<<Version<<"\n"
   <<"Bitflag: "<<Bitflag<<"\n"
   <<"Compression Method: "<<CompressionM<<"\n"
   <<"Last mod. file time: "<<FileT<<"\n"
   <<"Last mod. file date: "<<FileD<<"\n"
   <<"CRC: "<<CRC<<"\n"
   <<"Compressed Size: "<<CompressedSize<<"\n"
   <<"Uncompressed Size: "<<UncompressedSize<<"\n"
   <<"Filename length: "<<Flength<<"\n"
   <<"Extra field length: "<<FieldLength<<"\n"
   <<"Filename: "<<FilenameH<<"\n";
    if(FieldLength>0){cout<<"Field: "<<ExtrafieldH<<"\n";}
    cout<<"\n";
}

void ZipReader::ReleaseMemory(){
    delete[] Filename;
    if(FieldLengthCD>0){delete[]Extrafield;}
    if(CommentLengthCD>0) {delete[]Comment;}
    delete[] FilenameH;
    if(FieldLength>0){delete[]ExtrafieldH;}
}

bool ZipReader::OpenFile(){
    FileCD.open("1.zip",ios::binary);
    if(FileCD.fail()){ cout<<"Error opening the file\n"; return 0;}
    FileLH.open("1.zip",ios::binary);
    if(FileLH.fail()){cout<<"Error opening file\n"; return 0;}
    return 1;
}

void ZipReader::CloseFile(){
    FileLH.close();
    FileCD.close();
}