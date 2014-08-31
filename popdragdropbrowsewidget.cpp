#include "popdragdropbrowsewidget.h"
#include "ui_popdragdropbrowsewidget.h"
#include "resizablerubber.h"
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QStringList>
#include <QListView>
#include <QTreeView>
#include <QFileInfo>
#include <QFileIconProvider>
#include <QDateTime>
#include <folderhierarchymanager.h>

PopDragDropBrowseWidget::PopDragDropBrowseWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PopDragDropBrowseWidget)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    connect(ui->DragAndDrop,SIGNAL(dropDone()),this,SLOT(atDropDone()));
    imageSpecific=false;
    isList=false;
    ui->SelectButton->setEnabled(false);

}

PopDragDropBrowseWidget::~PopDragDropBrowseWidget()
{
    delete ui;
}

void PopDragDropBrowseWidget::setImageSpecific()
{
    ui->DragAndDrop->setImageSelectOnly();
    imageSpecific=true;
}

void PopDragDropBrowseWidget::setImageOnEdit(QPixmap x)
{
    ui->stackedWidget->setCurrentIndex(1);
    int w=ui->PorPicEditPage->width();
    int h=ui->PorPicEditPage->height();
    image=x;
    image=image.scaled(w,h,Qt::KeepAspectRatioByExpanding);
    ui->ProPicLabel->setPixmap(image);
    rubber=new ReSizableRubber(ui->ProPicLabel);
    rubber->move(0, 0);
    rubber->resize(350,350);
    rubber->setMinimumSize(350, 350);
    rubber->show();
}

void PopDragDropBrowseWidget::showFolderSelectOption()
{
    QFileInfo info(folderOrFilePath);
    QIcon x=QFileIconProvider().icon(info);
    ui->FileIconShower->setIcon(x);
    ui->FileIconShower->setIconSize(QSize(75,75));
    double num=0.0;
    num=FolderHierarchyManager::getInstance().sizeCalculator(info.absoluteFilePath());

    if(!info.isDir())
    {
        num=info.size();
    }
    else
    {

    }

    num/=1024;

    ui->FileNameLabel->setText(info.fileName());

    if(num<1024)
    {
        ui->SizeLabel->setText(QString::number(num,'f',1)+QString(" KB"));
    }
    else
    {
        num/=1024;
        if(num<1024)
        {
            ui->SizeLabel->setText(QString::number(num,'f',1)+QString(" MB"));
        }
        else
        {
            num/=1024;
            ui->SizeLabel->setText(QString::number(num,'f',2)+QString(" GB"));
        }
    }

    ui->LastModifiedDateLabel->setText(info.lastModified().toString("dd MMM yyyy"));
    if(info.completeSuffix()!="")
    {
        ui->FileNameSuffix->setText(info.completeSuffix());
    }
    else
    {
        ui->FileNameSuffix->setText("Folder");
    }
    ui->stackedWidget->setCurrentIndex(2);
}

void PopDragDropBrowseWidget::atDropDone()
{
    ui->SelectButton->setEnabled(true);
    if(imageSpecific)
    {
        setImageOnEdit(ui->DragAndDrop->getDropImage());
    }
    else
    {
        folderOrFilePath=ui->DragAndDrop->getFileOrFolderPath();
        qDebug()<<folderOrFilePath<<endl;
        showFolderSelectOption();
    }
}


void PopDragDropBrowseWidget::on_CancleButton_clicked()
{
    done(0);
}

void PopDragDropBrowseWidget::on_SelectButton_clicked()
{
    if(imageSpecific)
    {
        QPixmap save=image.copy(rubber->geometry());
        save.save(QString("Core").append(QDir::separator()).append("Elements")
                .append(QDir::separator()).append("LLPP.PNG"),"PNG",100);
        done(1);
    }
    else
    {
        qDebug()<<folderOrFilePath<<endl;
        FolderHierarchyManager::getInstance().copyFolderOrDir(folderOrFilePath,copyDir);
        done(1);
    }
}

QPixmap PopDragDropBrowseWidget::getDroppedImage()
{
    return image;
}



void PopDragDropBrowseWidget::on_BrowseButton_clicked()
{
    QFileDialog x;
    //QIcon icn("://Images/icon.png");
    //x.setWindowIcon(icn);
    if(imageSpecific)
    {
        QString fileName = x.getOpenFileName(this,
         tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
        QPixmap p(fileName);
        if(!p.isNull())
        {
            setImageOnEdit(p);
        }
    }
    else
    {
        fileNames=x.getOpenFileNames(this,tr("Open File(s)"),"",tr("All files (*.*)"));
        isList=true;
        foreach(QString str, fileNames)
        {
            FolderHierarchyManager::getInstance().copyFolderOrDir(str,copyDir);
        }

        done(1);

    }

}

bool PopDragDropBrowseWidget::getIsList() const
{
    return isList;
}

void PopDragDropBrowseWidget::setCopyDir(QString x)
{
    copyDir=x;
}




