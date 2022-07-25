#include "preferences.h"
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>

preferences::preferences(QWidget *parent) : QDialog(parent)
{
    setWindowTitle(tr("Settings"));

    lCols = new QLabel(tr("Number of columns:"));
    editCols = new QLineEdit();
    lRows = new QLabel(tr("Number of rows:"));
    editRows = new QLineEdit();
    btnQuit = new QPushButton(tr("Quit"));
    btnOk = new QPushButton(tr("OK"));
    layout = new QGridLayout();
    layout->addWidget(lCols,1,1);
    layout->addWidget(editCols,1,2);
    layout->addWidget(lRows,2,1);
    layout->addWidget(editRows,2,2);
    layout->addWidget(btnQuit,3,1);
    layout->addWidget(btnOk,3,2);

    btnOk->setDefault(true);

    connect(btnQuit, SIGNAL(clicked()), this, SLOT(reject()));
    connect(btnOk, SIGNAL(clicked()), this, SLOT(Ok_clicked()));

    setLayout(layout);
}

unsigned int preferences::getCols()
{
    return editCols->text().toUInt();
}

unsigned int preferences::getRows()
{
    return editRows->text().toUInt();
}

void preferences::Ok_clicked()
{
    unsigned int cards = editCols->text().toUInt() * editRows->text().toUInt();
    if(cards > maxCards)
    {
        QMessageBox::warning(this, tr("Too much cards"), tr("Only up to %1 cards are possible.").arg(maxCards));
        return;
    }
    else if(cards%2)
    {
        QMessageBox::warning(this, tr("Bad grid dimensions"), tr("Number of cards must be an even number."));
        return;
    }
    accept();
}

void preferences::setCols(unsigned int val)
{
    editCols->setText(QString("%1").arg(val));
}
void preferences::setMaxCards(unsigned int val)
{
    maxCards = val;
}

void preferences::setRows(unsigned int val)
{
    editRows->setText(QString("%1").arg(val));
}

preferences::~preferences()
{

}

