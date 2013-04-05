#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include "ui_finddialog.h"

class FindDialog : public QDialog ,public Ui::FindDialog
{
    Q_OBJECT
    
public:
    explicit FindDialog(QWidget *parent = 0);

signals:
    void findNext(const QString &str , Qt::CaseSensitivity cs);
    void findPrev(const QString &str , Qt::CaseSensitivity cs);

private slots :
    void findButtonClicked();
    void enableFindButton(const QString &text);


};

#endif // FINDDIALOG_H
