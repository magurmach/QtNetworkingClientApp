#include "folderhierarchymanager.h"
#include <QMap>
#include <QString>
#include <QDir>
#include <QDebug>

FolderHierarchyManager::FolderHierarchyManager()
{

}

FolderHierarchyManager& FolderHierarchyManager::getInstance()
{
    static FolderHierarchyManager staticInstance;
    return staticInstance;
}

void FolderHierarchyManager::createFolderHierarchy(qint64 caseId)
{
    QString str=QString("Core").append(QDir::separator()).append("Data").append(QDir::separator());//.append(QString("%1").arg(caseId).append(QDir::separator()));
    if(!QDir(str).exists())
    {
        QDir().mkdir(str);
    }
    str=QString("Core").append(QDir::separator()).append("Data").append(QDir::separator()).append(QString("%1").arg(caseId).append(QDir::separator()));
    //qDebug()<<str<<endl;
    if(!QDir(str).exists())
    {
        QDir().mkdir(str);
    }

    QMap<QString,int>::iterator it;

    for(it=mapper.begin();it!=mapper.end();it++)
    {
        QDir().mkdir(QString(str).append(QDir::separator()).append(QString("%1").arg(it.value())));
    }
}

bool FolderHierarchyManager::deleteFolderHierarchy(QString dirName, bool parent)
{
    QFileInfo x(dirName);
    if(x.isFile())
    {
        return QFile::remove(x.absoluteFilePath());
    }
    bool result = true;
    QDir dir(dirName);
    if (dir.exists())
    {
        foreach(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst))
        {
            if (info.isDir())
            {
                result = deleteFolderHierarchy(info.absoluteFilePath(),false);
            }
            else
            {
                result = QFile::remove(info.absoluteFilePath());
            }

            if (!result)
            {
                return result;
            }
        }
        if(!parent)
        {
            result = dir.rmdir(dir.absolutePath());
        }
        else
        {

        }
    }

    return result;
}

int FolderHierarchyManager::findFolderNumber(QString str)
{
    return mapper[str];
}

bool FolderHierarchyManager::copyFolderOrDir(QString dirName, QString destination)
{
    bool result=false;
    QDir dir(dirName);
    QFileInfo x(dirName);
    if(x.isFile())
    {
        //excuted when copying only a file
        QString newDestination=destination+"/"+x.fileName();
        int cnt=1;
        while(QFile(newDestination).exists())
        {
            //renaming if the current file to be copied already exists

            newDestination=destination+"/"+QString("(%1)").arg(cnt)+x.fileName();
            cnt++;

        }

        result=QFile().copy(x.absoluteFilePath(),newDestination);
    }
    else if(dir.exists())
    {
        //directory copy
        destination=destination+"/"+x.fileName();
        if(!QDir(destination).exists())
        {
            // if the directory doesn't exists then making the directory

            QDir().mkdir(destination);
        }

        foreach(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst))
        {
            if(info.isDir())
            {
                QString newDestination=destination+"/"+info.fileName();
                if(!QDir(newDestination).exists())
                {
                    QDir().mkdir(newDestination);
                }
                result=copyFolderOrDir(info.absoluteFilePath(),newDestination);
            }
            else
            {
                QString newDestination=destination+"/"+info.fileName();
                int cnt=1;
                while(QFile(newDestination).exists())
                {
                    newDestination=destination+"/"+QString("(%1)").arg(cnt)+info.fileName();
                    cnt++;
                }
                result=QFile().copy(info.absoluteFilePath(),newDestination);
            }
        }

        if(result==false)
        {
            return result;
        }

    }
    return result;
}


double FolderHierarchyManager::sizeCalculator(QString dirName)
{
    QFileInfo x(dirName);
    if(x.isFile())
    {
        return x.size();
    }
    double result=0.0;
    QDir dir(dirName);

    if(dir.exists())
    {
        foreach(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst))
        {
            if(info.isDir())
            {
                result+=sizeCalculator(info.absoluteFilePath());
            }
            else
            {
                result+=info.size();
            }
        }
    }
    return result;
}
