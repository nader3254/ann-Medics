#ifndef FILEBROWSER_H
#define FILEBROWSER_H

/*
C:\Users\Nader\Downloads\Anne-Medics-company2\29_11\AnneMedics_API\filebrowser.h:4: error: QDebug: No such file or directory
In file included from ../AnneMedics_API/filebrowser.cpp:1:
../AnneMedics_API/filebrowser.h:4:10: fatal error: QDebug: No such file or directory
    4 | #include <QDebug>
      |          ^~~~~~~~
*/
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
