#ifndef TEXTEDITORMAINWINDOW_H
#define TEXTEDITORMAINWINDOW_H

#include <QMainWindow>

class QString;

namespace Ui {
class TextEditorMainWindow;
}

class TextEditorMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit TextEditorMainWindow(QWidget *parent = 0);
    ~TextEditorMainWindow();


private slots:
    void about();
    void newFile();
    void open();
    void somethingChanged();
    bool save();
//    void saveAs();
//    void exit();
//    void copy();
//    void cut();
//    void paste();
    void find();

private:
    QString fileName;
    Ui::TextEditorMainWindow *ui;
    void setCurrentFile(const QString &filePath);
    bool warningBox();
    void closeEvent(QCloseEvent *event);
    void loadFile(const QString &filePath);
    void setupConnections();
    void setuoContextMenu();
};

#endif // TEXTEDITORMAINWINDOW_H
