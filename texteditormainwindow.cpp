#include <QtGui>
#include <fstream>
#include <iostream>
#include "texteditormainwindow.h"
#include "ui_texteditormainwindow.h"

#include "finddialog/finddialog.h"


using namespace std;

TextEditorMainWindow::TextEditorMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TextEditorMainWindow)
{
    ui->setupUi(this);
    setupConnections();
    setWindowIcon(QIcon(":/icons/mainIcon"));
    setWindowTitle(tr("[*] Text Editor"));
    setCurrentFile("");
}

TextEditorMainWindow::~TextEditorMainWindow()
{
    delete ui;
}


void TextEditorMainWindow::about()
{
    QMessageBox::about(this,
                       tr("About Text Editor"),
                       tr("Text Editor is a simple application created by <font color=\"red\"><b>Ahmed Magdy</b></font>."
                          "<b>[ahmed.magdy40@gmail.com]</b>"));
}


void TextEditorMainWindow::setupConnections()
{
    connect(ui->aboutAction,SIGNAL(triggered()),this,SLOT(about()));
    connect(ui->aboutQtAction,SIGNAL(triggered()),qApp,SLOT(aboutQt()));
    connect(ui->textArea,SIGNAL(textChanged()),this,SLOT(somethingChanged()));
    connect(ui->openAction,SIGNAL(triggered()),this,SLOT(open()));
    connect(ui->exitAction,SIGNAL(triggered()),qApp,SLOT(quit()));
    connect(ui->saveAction,SIGNAL(triggered()),this,SLOT(save()));
    connect(ui->newAction,SIGNAL(triggered()),this,SLOT(newFile()));
    connect(ui->findAction,SIGNAL(triggered()),this,SLOT(find()));
    connect(ui->copyAction,SIGNAL(triggered()),ui->textArea,SLOT(copy()));
    connect(ui->cutAction,SIGNAL(triggered()),ui->textArea,SLOT(cut()));
    connect(ui->pasteAction,SIGNAL(triggered()),ui->textArea,SLOT(paste()));

}


void TextEditorMainWindow::open()
{
    if(warningBox()){
        QString fileName=QFileDialog::getOpenFileName(this,
                                                      tr("Open TEXT file"),
                                                      ".",
                                                      tr("Text files (*.txt)"));
        setCurrentFile(fileName);
        setWindowModified(false);
        this->fileName=fileName;
    }

}


void TextEditorMainWindow::newFile()
{
    if(warningBox())
        ui->textArea->clear();
    setCurrentFile("");
    setWindowModified(false);

}


void TextEditorMainWindow::somethingChanged()
{
    setWindowModified(true);
}


void TextEditorMainWindow::setCurrentFile(const QString &filePath)
{
    QString shownName="Untitled";
    if (!filePath.isEmpty()){
        shownName=QFileInfo(filePath).fileName();
        loadFile(filePath);
        fileName=filePath;
    }
    setWindowTitle(tr("[*]%1 - %2")
                   .arg(shownName)
                   .arg("Text Editor"));
    setWindowModified(false);
}


bool TextEditorMainWindow::save()
{
    QString filePath;
    if(fileName.isEmpty()){
        filePath=QFileDialog::getSaveFileName(this,
                                              tr("Save"),
                                              tr("%1.txt").arg("Untitled"),
                                              tr("Text files *.txt"));
        fileName=filePath;
    }

    if (!fileName.isEmpty()){
        string path=fileName.toStdString();
        char *path1=new char[5000];
        for(int i=0;path[i]!='\0';i++)
            path1[i]=path[i];
        ofstream file(path1);
        if(file.is_open()){
            file << ui->textArea->toPlainText().toStdString();
            setCurrentFile(fileName);
            return true;
        }
    }

    return false;

}


bool TextEditorMainWindow::warningBox()
{
    if (isWindowModified()){
        int ans=QMessageBox::warning(this,
                             tr("Text Editor"),
                             tr("This file has being modified.\n"
                                "Do you want to save it first ?"),
                             QMessageBox::Yes | QMessageBox::Default,
                             QMessageBox::No,
                             QMessageBox::Cancel | QMessageBox::Escape);
        if (ans==QMessageBox::Yes)
            return save();
        else if (ans==QMessageBox::Cancel)
            return false;
    }
    return true;
}


void TextEditorMainWindow::closeEvent(QCloseEvent *event)
{
    if(warningBox())
        event->accept();
    else
        event->ignore();
}



void TextEditorMainWindow::find()
{
    FindDialog *findDialog= new FindDialog(this);
    findDialog->show();
}


void TextEditorMainWindow::loadFile(const QString &filePath)
{
    QFile textDocument(filePath);
    if (textDocument.open(QFile::ReadOnly | QFile::Text))
    {
        ui->textArea->setPlainText(textDocument.readAll());
    } else {
        QMessageBox::critical(this,
                              tr("Text Editor"),
                              tr("ERROR \nCan NOT read file %1 : %2.")
                              .arg(filePath)
                              .arg(textDocument.errorString()));
    }
}


void TextEditorMainWindow::setuoContextMenu()
{
    ui->textArea->addAction(ui->copyAction);
    ui->textArea->addAction(ui->cutAction);
    ui->textArea->addAction(ui->pasteAction);
    ui->textArea->setContextMenuPolicy(Qt::ActionsContextMenu);
}
