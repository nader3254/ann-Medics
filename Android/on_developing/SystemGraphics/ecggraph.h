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

#define ECG_RX1    0
#define ECG_RTime  10   /* 40 milli second */



class EcgGraph : public QQuickPaintedItem
{
    Q_PROPERTY(int rx  READ getrx  WRITE setrx  NOTIFY rxChanged    );
    Q_PROPERTY(int ry  READ getry  WRITE setry  NOTIFY ryChanged    );

    Q_OBJECT
public:
    EcgGraph(QQuickItem *parent = nullptr,QObject *obj=nullptr);

    void  paint(QPainter *painter);

    int   getrx();
    void  setrx(int mv);

    int   getry();
    void  setry(int mv);
    void isConnection(bool st);
    void setEcgAdv(int x);

public slots:
    void setCoords(int x,int y);
private slots:
    void EcgRender();
    void bpmTask();

signals:
void rxChanged();
void ryChanged();


private:
//int test[10]={55,90,30,-52,67,-50,-20,-100,77,-16};
//int test[10]={55,10,10,-52,10,10,20,10,10,-16};
 float m_volt=0.0;
 int   _x=0;
 int   _y=0;

 int i=0;
 float normalization;
bool buzz=false,connection=false;
int adcValue;

 EcgGraph *ecg_graphics_ptr;
 QTimer *ecg_t,*buzzTimer;
 QList <QPoint> points;
 QPoint pt;
void ConnectPoints(QPainter *painter);
void getECG();
void makeBuzz();

int ECG_RX2;
int ECG_Ry ;

};

#endif // ECGGRAPH_H
