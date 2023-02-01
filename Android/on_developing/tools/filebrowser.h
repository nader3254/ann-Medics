#ifndef FILEBROWSER_H
#define FILEBROWSER_H

#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QList>
#include <QStringList>
#include <QFile>

/*
 * this class will be used to read and write files
 * and show all files on specific directory or with specific format
*/
class FileBrowser
{
public:
    FileBrowser(QString path );
    void        SetPath(QString path);
    QStringList GetAllFiles();
    QStringList GetAllFiles(QString format);
    QString     ReadFile(QString filePath);
    void        WriteFile(QString filePath,QString content );

private:
    QList<QFileInfo> ff;
    QString s;
    QStringList lst;
    QString _path;

};

#endif // FILEBROWSER_H
