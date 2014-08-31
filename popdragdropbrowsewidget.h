#ifndef POPDRAGDROPBROWSEWIDGET_H
#define POPDRAGDROPBROWSEWIDGET_H

#include <QDialog>
#include "resizablerubber.h"

namespace Ui {
class PopDragDropBrowseWidget;
}

class PopDragDropBrowseWidget : public QDialog
{
    Q_OBJECT

public:
    explicit PopDragDropBrowseWidget(QWidget *parent = 0);
    ~PopDragDropBrowseWidget();
    void setImageSpecific();

    void setImageOnEdit(QPixmap x);

    bool getIsList() const;

    void showFolderSelectOption();

    void setCopyDir(QString x);


private slots:
    void atDropDone();

    void on_CancleButton_clicked();

    void on_SelectButton_clicked();

    QPixmap getDroppedImage();

    void on_BrowseButton_clicked();

private:
    Ui::PopDragDropBrowseWidget *ui;
    bool imageSpecific;
    ReSizableRubber *rubber;
    QPixmap image;
    QString folderOrFilePath;
    QStringList fileNames;
    QString copyDir;
    bool isList;
};

#endif // POPDRAGDROPBROWSEWIDGET_H
