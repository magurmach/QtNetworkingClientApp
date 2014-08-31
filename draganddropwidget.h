#ifndef DRAGANDDROPWIDGET_H
#define DRAGANDDROPWIDGET_H

#include <QWidget>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDragLeaveEvent>

class DragAndDropWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DragAndDropWidget(QWidget *parent = 0);

signals:
    void dropDone();

public slots:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent* event);
    void dragLeaveEvent(QDragLeaveEvent* event);
    void dropEvent(QDropEvent *event);

public:
    void setImageSelectOnly();
    QPixmap getDropImage();
    QString getFileOrFolderPath();

private:
    bool imageSelectOnly;
    QPixmap catcher;
    QString fileOrFolderPath;


};

#endif // DRAGANDDROPWIDGET_H
