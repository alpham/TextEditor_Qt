#include "finddialog.h"
#include "ui_finddialog.h"

FindDialog::FindDialog(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    connect(lineEdit,SIGNAL(textChanged(const QString &)),this,SLOT(enableFindButton(const QString &)));

}

void FindDialog::findButtonClicked()
{
    Qt::CaseSensitivity cs = caseBox->isChecked() ? Qt::CaseSensitive
                                                  : Qt::CaseInsensitive;
    if(backBox->isChecked())
        emit findPrev(lineEdit->text() , cs);
    else
        emit findNext(lineEdit->text() , cs);
}

void FindDialog::enableFindButton(const QString &text)
{
    findButton->setEnabled(!text.isEmpty());
}

