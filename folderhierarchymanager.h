#ifndef FOLDERHIERARCHYMANAGER_H
#define FOLDERHIERARCHYMANAGER_H

#include <QMap>
#include <QString>

class FolderHierarchyManager
{

public:
    FolderHierarchyManager();

    static FolderHierarchyManager& getInstance();

    void createFolderHierarchy(qint64 caseId);

    bool deleteFolderHierarchy(QString dirName);

    int findFolderNumber(QString str);

    bool copyFolderOrDir(QString dirName, QString destination);

    double sizeCalculator(QString dirName);


private:
    QMap<QString,int> mapper;
};

#endif // FOLDERHIERARCHYMANAGER_H
