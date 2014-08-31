#include "draganddropwidget.h"
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDragLeaveEvent>
#include <QDebug>
#include <QMimeData>
#include <QList>
#include <QUrl>
#include <QPixmap>


DragAndDropWidget::DragAndDropWidget(QWidget *parent) :
    QWidget(parent)
{
    imageSelectOnly=false;
}

void DragAndDropWidget::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void DragAndDropWidget::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}

void DragAndDropWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
    event->accept();
}

void DragAndDropWidget::dropEvent(QDropEvent *event)
{
    const QMimeData *x=event->mimeData();
    if(imageSelectOnly)
    {
        QList<QUrl> lst=x->urls();
        QPixmap pic(lst.at(0).toLocalFile());
        if(pic.isNull())
        {
            //no drop for non image or other image problem
            event->ignore();

        }
        else
        {
            catcher=pic;
            emit dropDone();
        }
    }
    else
    {
        fileOrFolderPath=x->urls().at(0).toLocalFile();
        emit dropDone();
    }
}

QString DragAndDropWidget::getFileOrFolderPath()
{
    return fileOrFolderPath;
}


void DragAndDropWidget::setImageSelectOnly()
{
    imageSelectOnly=true;
}

QPixmap DragAndDropWidget::getDropImage()
{
    return catcher;
}
