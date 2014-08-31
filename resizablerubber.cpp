#include "resizablerubber.h"
#include <QLayout>
#include <QSizeGrip>
#include <QDebug>
#include <QRubberBand>
#include <QResizeEvent>

ReSizableRubber::ReSizableRubber(QWidget *parent) :
    QWidget(parent)
{
    setWindowFlags(Qt::SubWindow);
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    QSizeGrip* grip1 = new QSizeGrip(this);
    QSizeGrip* grip2 = new QSizeGrip(this);
    layout->addWidget(grip1, 0, Qt::AlignLeft | Qt::AlignTop);
    layout->addWidget(grip2, 0, Qt::AlignRight | Qt::AlignBottom);
    rubber = new QRubberBand(QRubberBand::Rectangle, this);
    rubber->move(0, 0);
    rubber->show();
    setLayout(layout);
}


void ReSizableRubber::resizeEvent(QResizeEvent *e)
{
    //it changes inself in square
    QSize x=e->size();
    int s = qMax(x.height(),x.width());
    rubber->resize(QSize(s,s));
    this->resize(QSize(s,s));
}
