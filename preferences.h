#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>

class QGridLayout;
class QLabel;
class QLineEdit;
class QPushButton;

class preferences : public QDialog
{
    Q_OBJECT

    QGridLayout *layout;
    QLabel *lCols;
    QLabel *lRows;
    QLineEdit *editCols;
    QLineEdit *editRows;
    QPushButton *btnOk;
    QPushButton *btnQuit;

    unsigned int maxCards;

public:
    preferences(QWidget *parent = nullptr);
    ~preferences();
    unsigned int getCols();
    unsigned int getRows();
    void setCols(unsigned int val);
    void setRows(unsigned int val);
    void setMaxCards(unsigned int val);
private slots:
    void Ok_clicked();
};

#endif // PREFERENCES_H
