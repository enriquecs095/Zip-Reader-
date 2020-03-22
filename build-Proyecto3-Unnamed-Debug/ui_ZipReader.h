/********************************************************************************
** Form generated from reading UI file 'ZipReader.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ZIPREADER_H
#define UI_ZIPREADER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ZipReader
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QTextEdit *getName;
    QPushButton *Decompress;
    QPushButton *DecompressAll;
    QPushButton *Show;
    QLabel *Message;
    QLabel *Metadata;
    QLabel *label_2;
    QTextEdit *Signature;
    QLabel *label_3;
    QTextEdit *numberDisk;
    QLabel *label_4;
    QTextEdit *NumberEntries;
    QLabel *label_5;
    QTextEdit *SizeCentralDir;
    QLabel *label_6;
    QTextEdit *OffsetCentralDir;
    QLabel *label_7;
    QTextEdit *Comments;
    QTableWidget *ShowList;
    QPushButton *Return;
    QPushButton *Next;
    QTextEdit *DirParameter;
    QLabel *label_8;

    void setupUi(QMainWindow *ZipReader)
    {
        if (ZipReader->objectName().isEmpty())
            ZipReader->setObjectName(QString::fromUtf8("ZipReader"));
        ZipReader->resize(803, 455);
        centralWidget = new QWidget(ZipReader);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 121, 31));
        getName = new QTextEdit(centralWidget);
        getName->setObjectName(QString::fromUtf8("getName"));
        getName->setGeometry(QRect(130, 10, 261, 31));
        Decompress = new QPushButton(centralWidget);
        Decompress->setObjectName(QString::fromUtf8("Decompress"));
        Decompress->setGeometry(QRect(150, 90, 151, 41));
        DecompressAll = new QPushButton(centralWidget);
        DecompressAll->setObjectName(QString::fromUtf8("DecompressAll"));
        DecompressAll->setGeometry(QRect(320, 90, 151, 41));
        Show = new QPushButton(centralWidget);
        Show->setObjectName(QString::fromUtf8("Show"));
        Show->setGeometry(QRect(400, 10, 71, 31));
        Message = new QLabel(centralWidget);
        Message->setObjectName(QString::fromUtf8("Message"));
        Message->setEnabled(false);
        Message->setGeometry(QRect(510, 20, 261, 17));
        Metadata = new QLabel(centralWidget);
        Metadata->setObjectName(QString::fromUtf8("Metadata"));
        Metadata->setEnabled(true);
        Metadata->setGeometry(QRect(600, 50, 71, 41));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(490, 120, 121, 31));
        Signature = new QTextEdit(centralWidget);
        Signature->setObjectName(QString::fromUtf8("Signature"));
        Signature->setEnabled(false);
        Signature->setGeometry(QRect(620, 120, 171, 31));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(490, 170, 121, 31));
        numberDisk = new QTextEdit(centralWidget);
        numberDisk->setObjectName(QString::fromUtf8("numberDisk"));
        numberDisk->setEnabled(false);
        numberDisk->setGeometry(QRect(620, 170, 171, 31));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(490, 220, 131, 31));
        NumberEntries = new QTextEdit(centralWidget);
        NumberEntries->setObjectName(QString::fromUtf8("NumberEntries"));
        NumberEntries->setEnabled(false);
        NumberEntries->setGeometry(QRect(620, 220, 171, 31));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(490, 270, 131, 31));
        SizeCentralDir = new QTextEdit(centralWidget);
        SizeCentralDir->setObjectName(QString::fromUtf8("SizeCentralDir"));
        SizeCentralDir->setEnabled(false);
        SizeCentralDir->setGeometry(QRect(620, 270, 171, 31));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(490, 320, 131, 31));
        OffsetCentralDir = new QTextEdit(centralWidget);
        OffsetCentralDir->setObjectName(QString::fromUtf8("OffsetCentralDir"));
        OffsetCentralDir->setEnabled(false);
        OffsetCentralDir->setGeometry(QRect(620, 320, 171, 31));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(490, 360, 131, 31));
        Comments = new QTextEdit(centralWidget);
        Comments->setObjectName(QString::fromUtf8("Comments"));
        Comments->setEnabled(false);
        Comments->setGeometry(QRect(620, 360, 171, 70));
        ShowList = new QTableWidget(centralWidget);
        ShowList->setObjectName(QString::fromUtf8("ShowList"));
        ShowList->setGeometry(QRect(10, 140, 461, 311));
        Return = new QPushButton(centralWidget);
        Return->setObjectName(QString::fromUtf8("Return"));
        Return->setGeometry(QRect(10, 90, 61, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../build-Proyecto3-Unnamed-Debug/regresar.png"), QSize(), QIcon::Normal, QIcon::Off);
        Return->setIcon(icon);
        Next = new QPushButton(centralWidget);
        Next->setObjectName(QString::fromUtf8("Next"));
        Next->setGeometry(QRect(80, 90, 61, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../build-Proyecto3-Unnamed-Debug/next.png"), QSize(), QIcon::Normal, QIcon::Off);
        Next->setIcon(icon1);
        DirParameter = new QTextEdit(centralWidget);
        DirParameter->setObjectName(QString::fromUtf8("DirParameter"));
        DirParameter->setEnabled(false);
        DirParameter->setGeometry(QRect(50, 50, 421, 31));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 50, 31, 31));
        ZipReader->setCentralWidget(centralWidget);

        retranslateUi(ZipReader);

        QMetaObject::connectSlotsByName(ZipReader);
    } // setupUi

    void retranslateUi(QMainWindow *ZipReader)
    {
        ZipReader->setWindowTitle(QApplication::translate("ZipReader", "ZipReader", nullptr));
        label->setText(QApplication::translate("ZipReader", "Nombre Archivo:", nullptr));
        Decompress->setText(QApplication::translate("ZipReader", "Descomprimir", nullptr));
        DecompressAll->setText(QApplication::translate("ZipReader", "Descomprimir Todo", nullptr));
        Show->setText(QApplication::translate("ZipReader", "Mostrar", nullptr));
        Message->setText(QApplication::translate("ZipReader", ".", nullptr));
        Metadata->setText(QApplication::translate("ZipReader", "Metadata", nullptr));
        label_2->setText(QApplication::translate("ZipReader", "Signature End:", nullptr));
        label_3->setText(QApplication::translate("ZipReader", "Number of Disks:", nullptr));
        label_4->setText(QApplication::translate("ZipReader", "Number of entries:", nullptr));
        label_5->setText(QApplication::translate("ZipReader", "Size central dir:", nullptr));
        label_6->setText(QApplication::translate("ZipReader", "Offset Central dir:", nullptr));
        label_7->setText(QApplication::translate("ZipReader", "Comments:", nullptr));
        Return->setText(QString());
        Next->setText(QString());
        label_8->setText(QApplication::translate("ZipReader", "Dir:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ZipReader: public Ui_ZipReader {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ZIPREADER_H
