#include "indexedbutton.h"

indexedButton::indexedButton(unsigned int index)
{
    this->index = index;
    this->setFocusPolicy(Qt::NoFocus);
    connect(this, SIGNAL(clicked()), this, SLOT(click()));
}

void indexedButton::click()
{
    emit clicked_index(index);
}

indexedButton::~indexedButton()
{
}
