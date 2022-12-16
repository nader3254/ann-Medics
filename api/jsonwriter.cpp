#include "jsonwriter.h"

JsonWriter::JsonWriter(QObject *parent)
    : QObject{parent}
{

}

void JsonWriter::CreateJson()
{
    jsonSTR  ="{\n";
    jsonSTR +="##KEY##";



}

QString JsonWriter::SaveJson()
{
    jsonSTR.remove(",\n##KEY##");
    jsonSTR +="\n}";
    FileBrowser *fb = new FileBrowser("");
    fb->WriteFile("annMedics.json",jsonSTR);
    return jsonSTR;

}

void JsonWriter::AddKey_value(QString key, int value)
{
      QString replacment ="\t\""+key+"\": " +QString::number(value)+",\n##KEY##";
      jsonSTR.replace("##KEY##",replacment);
}

void JsonWriter::AddKey_value(QString key, QString value)
{

}
