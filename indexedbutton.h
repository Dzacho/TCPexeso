#ifndef INDEXEDBUTTON_H
#define INDEXEDBUTTON_H

#include <QPushButton>

class indexedButton : public QPushButton
{
    Q_OBJECT
    unsigned int index;
public:
    indexedButton(unsigned int index);
    ~indexedButton();
public slots:
    void click();
signals:
    void clicked_index(unsigned int index);
};

#endif // INDEXEDBUTTON_H
