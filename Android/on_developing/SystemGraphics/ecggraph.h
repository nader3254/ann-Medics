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
<<<<<<< HEAD
#define ECG_RTime  10   /* 40 milli second */
=======
#define ECG_RX2    527
#define ECG_Ry     162
#define ECG_RTime  50   /* 40 milli second */
>>>>>>> aa1f01b9d0f3590d9575e9dc1a536fe2aee0f813



class EcgGraph : public QQuickPaintedItem
{
<<<<<<< HEAD
    Q_PROPERTY(int rx  READ getrx  WRITE setrx  NOTIFY rxChanged    );
    Q_PROPERTY(int ry  READ getry  WRITE setry  NOTIFY ryChanged    );
=======
        Q_PROPERTY(int voltage_mv  READ getVoltage  WRITE setVolyage  NOTIFY voltageChanged    );
>>>>>>> aa1f01b9d0f3590d9575e9dc1a536fe2aee0f813

    Q_OBJECT
public:
    EcgGraph(QQuickItem *parent = nullptr,QObject *obj=nullptr);

    void  paint(QPainter *painter);

<<<<<<< HEAD
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
=======
    float getVoltage();
    void  setVolyage(float mv);

private slots:
    void EcgRender();

signals:
void voltageChanged();



private:
int test[10]={55,90,30,-52,67,-50,-20,-100,77,-16};
>>>>>>> aa1f01b9d0f3590d9575e9dc1a536fe2aee0f813
//int test[10]={55,10,10,-52,10,10,20,10,10,-16};
 float m_volt=0.0;
 int   _x=0;
 int   _y=0;

 int i=0;
<<<<<<< HEAD
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
=======

 EcgGraph *ecg_graphics_ptr;
 QTimer *ecg_t;
 QList <QPoint> points;
 QPoint pt;
void ConnectPoints(QPainter *painter);
>>>>>>> aa1f01b9d0f3590d9575e9dc1a536fe2aee0f813

};

#endif // ECGGRAPH_H
