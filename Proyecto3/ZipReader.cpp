#include "ZipReader.h"
#include "ui_ZipReader.h"

ZipReader::ZipReader(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ZipReader){
    ui->setupUi(this);
    QStringList titulos;
    titulos<<"Tipo"<<"Nombre"<<"Tamaño KB";
    ui->ShowList->setColumnCount(3);
    ui->ShowList->setHorizontalHeaderLabels(titulos);
    ui->ShowList->setColumnWidth(0,10);
    ui->ShowList->setColumnWidth(1,290);
    ui->ShowList->setColumnWidth(2,95);
    ui->ShowList->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->ShowList->verticalHeader()->setVisible(false);
    ui->ShowList->setEditTriggers(QAbstractItemView::NoEditTriggers);
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
    countDelimiter=1;
}

void ZipReader::Read(){
    if(!OpenFile()){return;};
    ReadEndHeader();
    ReadCentralDirectory();
    Print();
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
    else if(n==9){ comment=new char[CommentLength+1]; comment[CommentLength]=0; memcpy(comment,data,CommentLength); }
}

void ZipReader::ReadEndHeader(){
    getEndDirectory();
    char buffer[22];
    FileCD.seekg(Position,ios::beg);
    FileCD.read(buffer,sizeof(buffer));
    setBuffer(buffer,3);
    UnPack(3);
    if(CommentLength>0){
       char commentChar[CommentLength];
       FileCD.read(commentChar,sizeof(commentChar));
       setBuffer(commentChar,9);
    }
    DiskR=new DiskData[NumberEntriesD];
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
   ui->Signature->setText(signatureEnd);
   ui->numberDisk->setText(QString::number(NumberDisk));
   ui->NumberEntries->setText(QString::number(NumberEntriesD));
   ui->SizeCentralDir->setText(QString::number(SizeCentralDirectory));
   ui->OffsetCentralDir->setText(QString::number(OffsetCentralDirectory));
   if(CommentLength>0){
    ui->Comments->setText(comment);
   }
   Print2();
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
        for(int x=0; x<Flength;x++){
            DiskR[i].nameD+=FilenameH[x];
        }
        DiskR[i].sizeC=CompressedSize;
        DiskR[i].sizeD=UncompressedSize;
        DiskR[i].offsetD=OffsetLocalHeader;
        DiskR[i].lengthName=Flength;
        ReleaseMemory();
     }
    ReduceName();//aqui reduzco el nombre
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
    if(FieldLength>0){
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
int countDel;
int end;
int compare=0;
    for(int x=0;x<NumberEntriesD;x++){
        countDel=0;
        end=0;
        for(int y=0;y<DiskR[x].lengthName;y++){
            if(DiskR[x].nameD[y]==47){ end=y+1; countDel++;}
        }
        if(countDel==countDelimiter){compare=countDel;}
        if(countDel==countDelimiter-1 && end!=DiskR[x].lengthName || countDel==countDelimiter && end==DiskR[x].lengthName){
        ui->ShowList->insertRow(ui->ShowList->rowCount());
        ui->ShowList->setItem(ui->ShowList->rowCount()-1,1,new QTableWidgetItem(DiskR[x].nameD.c_str()));
            if(DiskR[x].sizeD==0){
                ui->ShowList->setItem(ui->ShowList->rowCount()-1,2,new QTableWidgetItem(QString::number(SizeDir(x))));
            }else{
                 ui->ShowList->setItem(ui->ShowList->rowCount()-1,2,new QTableWidgetItem(QString::number(DiskR[x].sizeD)));
            }
            if(DiskR[x].sizeD==0) { ui->ShowList->setItem(ui->ShowList->rowCount()-1,0,new QTableWidgetItem("Dir"));}
            else {ui->ShowList->setItem(ui->ShowList->rowCount()-1,0,new QTableWidgetItem("Doc"));}
        }
    }
    if(compare==countDelimiter){countDelimiter++;}
}

void ZipReader::ReleaseMemory(){
    delete[] Filename;
    if(FieldLengthCD>0){delete[]Extrafield;}
    if(CommentLengthCD>0) {delete[]Comment;}
    delete[] FilenameH;
    if(FieldLength>0){delete[]ExtrafieldH;}
}

bool ZipReader::OpenFile(){
    FileCD.open(NameOfFile,ios::binary);
    if(FileCD.fail()){ ui->Message->setText("Error opening the file"); return 0;}
    FileLH.open(NameOfFile,ios::binary);
    if(FileLH.fail()){ui->Message->setText("Error opening the file"); return 0;}
    return 1;
}

void ZipReader::CloseFile(){
    FileLH.close();
    FileCD.close();
}


ZipReader::~ZipReader(){
    delete ui;
}


void ZipReader::on_Show_clicked(){
    ui->DirParameter->setText("");
    NameOfFile=ui->getName->toPlainText().toStdString();
    countDelimiter=1;
    if(NumberEntriesD>0){delete[] DiskR;}
    ui->ShowList->setColumnWidth(0,10);
    ui->ShowList->setColumnWidth(1,290);
    ui->ShowList->setColumnWidth(2,95);
    ui->Message->setText(" ");
    ui->ShowList->clearContents();
    ui->ShowList->setRowCount(0);
    Read();
    ui->ShowList->sortItems(0,Qt::SortOrder::AscendingOrder);
}


void ZipReader::on_Next_clicked(){
    QTableWidgetItem * itemS=ui->ShowList->item(ui->ShowList->currentRow(),1);
    QTableWidgetItem * itemS2=ui->ShowList->item(ui->ShowList->currentRow(),0);
    QString nameS=itemS->text();
    string name2=itemS2->text().toStdString();
    string compare="Dir";
    int countDel;
    int end;
    int rep=0;
    int comp=0;
    if(strcmp(name2.c_str(),"Dir")==0){
        ui->ShowList->clearContents();
        ui->ShowList->setRowCount(0);
        ui->DirParameter->setText(nameS);
        string nameIn=ui->DirParameter->toPlainText().toStdString();
        for(int x=0;x<NumberEntriesD;x++){
            countDel=0;
            end=0;
            for(int y=0;y<DiskR[x].lengthName;y++){
                if(DiskR[x].nameD[y]==47){end=y+1; countDel++;}
            }
            if(countDel==countDelimiter){comp=countDel;}
             if(DiskR[x].nameD.find(nameIn)!=string::npos){
                 if(countDel==countDelimiter && end==DiskR[x].lengthName &&x!=rep || countDel==countDelimiter-1 && end!=DiskR[x].lengthName &&x!=rep){
                     ui->ShowList->insertRow(ui->ShowList->rowCount());
                     ui->ShowList->setItem(ui->ShowList->rowCount()-1,1,new QTableWidgetItem(DiskR[x].nameD.c_str()));
                     if(DiskR[x].sizeD==0){
                         ui->ShowList->setItem(ui->ShowList->rowCount()-1,2,new QTableWidgetItem(QString::number(SizeDir(x))));
                     }else{
                          ui->ShowList->setItem(ui->ShowList->rowCount()-1,2,new QTableWidgetItem(QString::number(DiskR[x].sizeD)));
                     }
                        if(DiskR[x].sizeD==0) { ui->ShowList->setItem(ui->ShowList->rowCount()-1,0,new QTableWidgetItem("Dir"));}
                        else {ui->ShowList->setItem(ui->ShowList->rowCount()-1,0,new QTableWidgetItem("Doc"));}
                }
            }
        }
    }
        if(comp==countDelimiter){countDelimiter++;}
          ui->ShowList->sortItems(0,Qt::SortOrder::AscendingOrder);
}


void ZipReader::on_Return_clicked(){
    int countDel;
    int end;
    int count;
    string refresh=ui->DirParameter->toPlainText().toStdString();//he aqui el detalle
    string newRefresh;
    if(countDelimiter>1){
        ui->ShowList->clearContents();
        ui->ShowList->setRowCount(0);
        for(int x=0;x<NumberEntriesD;x++){
            countDel=0;
            end=0;
            for(int y=0;y<DiskR[x].lengthName;y++){
                if(DiskR[x].nameD[y]==47){end=y+1; countDel++;}
            }
                 if(countDel==countDelimiter-2 && end==DiskR[x].lengthName || countDel==countDelimiter-3 && end!=DiskR[x].lengthName){
                     ui->ShowList->insertRow(ui->ShowList->rowCount());
                     ui->ShowList->setItem(ui->ShowList->rowCount()-1,1,new QTableWidgetItem(DiskR[x].nameD.c_str()));
                     if(DiskR[x].sizeD==0){
                         ui->ShowList->setItem(ui->ShowList->rowCount()-1,2,new QTableWidgetItem(QString::number(SizeDir(x))));
                     }else{
                          ui->ShowList->setItem(ui->ShowList->rowCount()-1,2,new QTableWidgetItem(QString::number(DiskR[x].sizeD)));
                     }
                        if(DiskR[x].sizeD==0) { ui->ShowList->setItem(ui->ShowList->rowCount()-1,0,new QTableWidgetItem("Dir"));}
                        else {ui->ShowList->setItem(ui->ShowList->rowCount()-1,0,new QTableWidgetItem("Doc"));}
                }
        }
        for (int x=0;x<refresh.length();x++) {
            if(refresh[x]==47){count++;}
            if(count==countDelimiter-2){break;}
              newRefresh+=refresh[x];
        }
        ui->DirParameter->setText(QString::fromUtf8(newRefresh.c_str()));
        countDelimiter--;
    }
      ui->ShowList->sortItems(0,Qt::SortOrder::AscendingOrder);
}

void ZipReader::Decompress(const char* name,const char* nameShort){
    int err = 0;
    const char* nameZip=NameOfFile.c_str();
    std::ofstream file;
    zip *z = zip_open(nameZip, 0, &err);
    struct zip_stat st;
    zip_stat_init(&st);
    zip_stat(z, name, 0, &st);
    //Alloc memory for its uncompressed contents
    char *contents = new char[st.size];
    //Read the compressed file
    zip_file *f = zip_fopen(z, name, 0);
    zip_fread(f, contents, st.size);
    zip_fclose(f);
    std::string add="archivos/";
    std::string DirLong;
    for (int x=0;x<add.length();x++) {
        DirLong+=add[x];
    }
    for (int x=0;x<strlen(nameShort);x++) {
        DirLong+=nameShort[x];
    }
    file.open(DirLong);
    file.seekp(0,std::ios::beg);
    file.write(contents,st.size);
    file.close();
    //And close the archive
    zip_close(z);
    delete [] contents;
}

void ZipReader::on_Decompress_clicked(){
    string name;
    string type;
    QTableWidgetItem * item=ui->ShowList->item(ui->ShowList->currentRow(),1);
    QTableWidgetItem * item2=ui->ShowList->item(ui->ShowList->currentRow(),0);
    name=item->text().toStdString();
    type=item2->text().toStdString();
    int size=name.length();
        if(strcmp(type.c_str(),"Dir")==0){
            for (int x=0;x<NumberEntriesD;x++){
                    if(DiskR[x].nameD.find(name)!=string::npos && DiskR[x].sizeD>0){
                        std::string DirName;
                        std::string aux;
                            for(int i=size; i < DiskR[x].nameD.length();i++){
                                aux+=DiskR[x].nameD[i];
                            }
                            for(int i=0; i < aux.length();i++){
                                DirName+=aux[i];
                            }
                        Decompress(DiskR[x].nameD.c_str(),DirName.c_str());

                    }else if(DiskR[x].nameD.find(name)!=string::npos && DiskR[x].sizeD==0){
                            std::string DirName;
                            std::string aux;
                            std::string dirlong="archivos/";
                            for (int i=0;i<dirlong.length();i++) {
                                DirName+=dirlong[i];
                            }
                            int pos=size;
                                for(int i=pos; i < DiskR[x].nameD.length();i++){
                                    aux+=DiskR[x].nameD[i];
                                }
                                for(int i=0; i < aux.length();i++){
                                    DirName+=aux[i];
                                }
                                mkdir(DirName.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
                    }
                }
        }else{
            for (int x=0;x<NumberEntriesD;x++){
                    if(strcmp(DiskR[x].nameD.c_str(),name.c_str())==0  && DiskR[x].sizeD>0){                     
                        Decompress(DiskR[x].nameD.c_str(),DiskR[x].nameShort.c_str());
                        return;
                    }
                }
        }
}



void ZipReader::ReduceName(){
    string a;
        for (int x=0;x<NumberEntriesD;x++){
            a.clear();
            if(DiskR[x].sizeD>0){
                for (int y=DiskR[x].lengthName-1;y>=0;y--){
                    if(DiskR[x].nameD[y]==47){break;}
                        a+=DiskR[x].nameD[y];
                }
                for (int y=a.length()-1;y>=0;y--) {
                     DiskR[x].nameShort+=a[y];
                }
            }
        }
}


void ZipReader::on_DecompressAll_clicked(){
    for (int x=0;x<NumberEntriesD;x++) {
        if(DiskR[x].sizeD==0){
            std::string dirlong="archivos/";
            std::string DirName;
            for (int y=0;y<dirlong.length();y++) {
                DirName+=dirlong[y];
            }
            for (int y=0;y<DiskR[x].nameD.length();y++) {
                DirName+=DiskR[x].nameD[y];
            }
             mkdir(DirName.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        }else {
                Decompress(DiskR[x].nameD.c_str(),DiskR[x].nameD.c_str());
        }
    }
}


int ZipReader::SizeDir(int pos){
int size=0;
    for (int x=0;x<NumberEntriesD;x++) {
        if(DiskR[x].nameD.find(DiskR[pos].nameD)!=string::npos && DiskR[x].sizeD>0){
            size+=DiskR[x].sizeD;
        }
    }
return size;
}
