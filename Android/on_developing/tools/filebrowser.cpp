#include "filebrowser.h"



FileBrowser::FileBrowser(QString path)
{
    QDir dir(path);
    _path = path;
    ff = dir.entryInfoList(QDir::Files);

    for(int i=0;i<ff.size();i++)
    {
       //s=ff.at(i).filePath();
       lst << ff.at(i).filePath();
       //s+="##**##" ;
       //qDebug()<<s ;
      // qDebug()<<"######################" ;
    }
}

void FileBrowser::SetPath(QString path)
{
     QDir dir(path);
     _path = path;
     ff = dir.entryInfoList(QDir::Files);
     for(int i=0;i<ff.size();i++)
     {
        lst << ff.at(i).filePath();

     }
}

QStringList FileBrowser::GetAllFiles()
{
    return lst;
}

QStringList FileBrowser::GetAllFiles(QString format)
{
    QStringList flst;
    for(int i=0;i<ff.size();i++)
    {
       if(lst.at(i).contains(format))
       {
         flst << lst.at(i);
       }
    }
    return flst;

}

QString FileBrowser::ReadFile(QString filePath)
{

    QFile file2(filePath);
    QByteArray line;
    if (!file2.open(QIODevice::ReadOnly | QIODevice::Text))
    {
           qDebug() << " file not found\n";
    }


    while (!file2.atEnd())
    {
            line = file2.readAll();
    }
    file2.close();
    QString output(line);
    //qDebug()<<output;
  return output;
}

void FileBrowser::WriteFile(QString filePath, QString content)
{

    QString filename = filePath;
    QFile file1(filename);
    if (file1.open(QIODevice::WriteOnly))
     {
         QTextStream stream(&file1);
         stream << content.toUtf8();
     }
     file1.close();
}
