#ifndef ALLTEXTS_H
#define ALLTEXTS_H

#include <QObject>
#include <QVariant>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickItem>
#include <QTimer>

class AllTexts : public QObject
{
    Q_OBJECT
public:
    explicit AllTexts(QObject *parent );


    void SetHR(int val);
    void SetSpo2(int val);
    void SetNibp(int max,int min);

    int GetHR();
    int GetSpo2();
    int GetNibp_min();
    int GetNibp_max();

    void AllTextTest(bool st);

private slots:
 void AllTextRender();
signals:



private:

 QObject* _HR;
 QObject* _SPO2;
 QObject* NIBP_Min;
 QObject* NIBP_Max;

 int hr,spo2,nibp_min,nibp_max;

 int i=0;
 QTimer *ATT;
 bool _st=false;

};

#endif // ALLTEXTS_H
