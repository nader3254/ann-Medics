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
#define ECG_RX2    527
#define ECG_Ry     162
#define ECG_RTime  2  /* 40 milli second */


class EcgGraph : public QQuickPaintedItem
{
        Q_PROPERTY(int voltage_mv  READ getVoltage  WRITE setVolyage  NOTIFY voltageChanged    );

    Q_OBJECT
public:
    EcgGraph(QQuickItem *parent = nullptr,QObject *obj=nullptr);

    void  paint(QPainter *painter);

    float getVoltage();
    void  setVolyage(float mv);

private slots:
    void EcgRender();

signals:
void voltageChanged();


private:

 float m_volt=0.0;
 int   _x=0;
 int   _y=0;

 int i=0;

 EcgGraph *ecg_graphics_ptr;
 QTimer *ecg_t;
 QList <QPoint> points;
 QPoint pt;


};

#endif // ECGGRAPH_H
