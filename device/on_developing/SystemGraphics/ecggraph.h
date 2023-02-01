#ifndef ECGGRAPH_H
#define ECGGRAPH_H

#include <QObject>
#include <QQuickPaintedItem>
#include <QString>
#include <QPainter>
#include <QPen>
#include <QtMath>
#include <QTimer>
#include <QList>
#include <QPoint>
#include "SystemGraphics/alltexts.h"
#include "tools/filebrowser.h"
#include "tools/systemerrors.h"
#include "tools/scriptrunner.h"


#define ECG_RX1    0
#define ECG_RX2    527
#define ECG_Ry     162
#define ECG_RTime  10   /* 40 milli second */



class EcgGraph : public QQuickPaintedItem
{
        Q_PROPERTY(int voltage_mv  READ getVoltage  WRITE setVolyage  NOTIFY voltageChanged    );

    Q_OBJECT
public:
    EcgGraph(QQuickItem *parent = nullptr,QObject *obj=nullptr);

    void  paint(QPainter *painter);

    float getVoltage();
    void  setVolyage(float mv);
    void isConnection(bool st);
    int  getEcgAdc();

private slots:
    void EcgRender();
    void bpmTask();

signals:
void voltageChanged();



private:
//int test[10]={55,90,30,-52,67,-50,-20,-100,77,-16};
//int test[10]={55,10,10,-52,10,10,20,10,10,-16};
 float m_volt=0.0;
 int   _x=0;
 int   _y=0;
 int i=0;
 float normalization;
bool buzz=false,connection=false;
 EcgGraph *ecg_graphics_ptr;
 QTimer *ecg_t,*buzzTimer;
 QList <QPoint> points;
 QPoint pt;
 scriptRunner *ecgscr;
 scriptRunner *buzzscr;
FileBrowser *ecf;
 int adcValue;

typedef enum {p,q,r,t}state;
state curr_state=p;


void ConnectPoints(QPainter *painter);
void getECG();
void makeBuzz();

};

#endif // ECGGRAPH_H
