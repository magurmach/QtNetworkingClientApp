#ifndef RESIZABLERUBBER_H
#define RESIZABLERUBBER_H

#include <QWidget>
#include <QRubberBand>

class ReSizableRubber : public QWidget
{
    Q_OBJECT
public:
    explicit ReSizableRubber(QWidget *parent = 0);

signals:

public slots:
    void resizeEvent(QResizeEvent *e);

private:
    QRubberBand *rubber;
};

#endif // RESIZABLERUBBER_H
