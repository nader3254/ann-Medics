#ifndef JSONWRITER_H
#define JSONWRITER_H

#include <QObject>
#include "filebrowser.h"
class JsonWriter : public QObject
{
    Q_OBJECT
public:
    explicit JsonWriter(QObject *parent = nullptr);
    void     CreateJson();
    QString  SaveJson();
    void     AddKey_value(QString key ,int value);
    void     AddKey_value(QString key ,QString value);


private:
   QString jsonSTR;

};

#endif // JSONWRITER_H
