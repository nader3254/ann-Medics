#include "ecggraph.h"


EcgGraph::EcgGraph(QQuickItem *parent,QObject *obj): QQuickPaintedItem(parent)
{
    QObject *graph = obj->findChild<QObject*>("ecg_graph");
    ecg_graphics_ptr= qobject_cast<EcgGraph*>(graph);
<<<<<<< HEAD

    ecf=new FileBrowser("");
    qDebug()<<"starting the ecg script ....";
    ecgscr=new scriptRunner("cd /home/pi/tst/ecgMcp3008/ && sudo python3 simpletest.py ");
    buzzscr=new scriptRunner("cd /home/pi/tst/Buzzer/ && sudo python3 buzzer.py ");
    ecgscr->start();
    buzzscr->start();
=======
>>>>>>> aa1f01b9d0f3590d9575e9dc1a536fe2aee0f813

    ecg_t=new QTimer(this);
    connect(ecg_t, SIGNAL(timeout()), this, SLOT(EcgRender()));
    ecg_t->setInterval(ECG_RTime);
    ecg_t->start();

    buzzTimer=new QTimer(this);
    connect(buzzTimer, SIGNAL(timeout()), this, SLOT(bpmTask()));
    buzzTimer->setInterval(910);
    buzzTimer->start();

}

void EcgGraph::paint(QPainter *painter)
{
    painter->setRenderHint(QPainter::SmoothPixmapTransform,1);
    QPen p ;


    QFont font("Helvetica",18,QFont::Bold);
    painter->setFont(font);


    p.setColor(QColor(0, 255, 200,255));
    painter->save();
    p.setWidth(2);
    painter->setPen(p);
    for(int j=0;j<points.size();j++)
    {
       painter->drawPoint(points.at(j));
    }
    // connect all points
    ConnectPoints(painter);
    painter->restore();


}

float EcgGraph::getVoltage()
{
    return m_volt;
}

void EcgGraph::setVolyage(float mv)
{
    if(m_volt == mv)
              return;
          m_volt = mv;
            update();
            emit voltageChanged();
}

void EcgGraph::isConnection(bool st)
{
    connection=st;
}

int EcgGraph::getEcgAdc()
{
  return  adcValue;
}

void EcgGraph::EcgRender()
{
    getECG();
    pt.setX(_x++);
<<<<<<< HEAD
    if(buzz==true && (normalization>=0.2))
    {
        normalization=0.80;
        buzz=false;
    }
    pt.setY(ECG_Ry-((ECG_Ry-60)*normalization));
=======
    //pt.setY(ECG_Ry-test[i]);
    pt.setY(ECG_Ry);
  //  pt.setY(ECG_Ry-sin(2*i++*0.0174532925 )*50);
>>>>>>> aa1f01b9d0f3590d9575e9dc1a536fe2aee0f813
    points<<pt;
    if(!(points.size()<ECG_RX2))
    {
        _x=0;
<<<<<<< HEAD
        points.clear();
=======
               points.clear();
>>>>>>> aa1f01b9d0f3590d9575e9dc1a536fe2aee0f813

    }
   update();

<<<<<<< HEAD
}

void EcgGraph::bpmTask()
{

    if(connection==true)
    {
        makeBuzz();
    }
}

void EcgGraph::makeBuzz()
{
    buzz=true;
    FileBrowser *ffb=new FileBrowser("");
    ffb->WriteFile("/home/pi/tst/Buzzer/buzzer.txt","on");
=======
   i++;
   if(i==10)
   {
       i=0;
   }
    update();

>>>>>>> aa1f01b9d0f3590d9575e9dc1a536fe2aee0f813
}

void EcgGraph::ConnectPoints(QPainter *painter)
{
    for(int j=0;j<points.size();j++)
    {
        if(j!=points.size()-1)
        {
            if(points.at(j).y()>points.at(j+1).y())
            {
                for(int k =points.at(j+1).y();k<points.at(j).y();k++)
                {

                    QPoint pnt;
                    pnt.setX(points.at(j).x());
                    pnt.setY(k);
                    if(pnt.x()<ECG_RX2)
                             painter->drawPoint(pnt);
                }
            }
            else
            {
                //points.at(j).y()<points.at(j+1).y()
                for(int k =points.at(j).y();k<points.at(j+1).y();k++)
                {

                    QPoint pnt;
                    pnt.setX(points.at(j).x());
                    pnt.setY(k);
                    if(pnt.x()<ECG_RX2)
                             painter->drawPoint(pnt);
                }
            }

        }

    }

}

void EcgGraph::getECG()
{

    QString tmp =ecf->ReadFile("/home/pi/tst/ecgMcp3008/ecg.txt");
    adcValue=tmp.toInt();
    normalization=(adcValue)*0.00027751;

}

    //normalization=(adcValue)*0.00097751;
//    if((adcValue>0)&&(adcValue<1020) )
//    {
//       normalization=(adcValue)*0.00027751;
//    }
//    else
//    {
//        normalization=(adcValue)*0.00097751;

//    }


    //qDebug()<<"ecg is :: "<<normalization;



//    switch (curr_state) {
//    case p:
//        pt.setY(ECG_Ry-i);i++;
//        if(i==50)
//        {
//            curr_state=q;i=0;
//        }
//        break;
//    case q:
//        pt.setY(ECG_Ry);i++;
//        if(i==32)
//        {
//            pt.setY(ECG_Ry+50);
//            curr_state=r;i=0;
//        }
//        break;
//    case r:
//        pt.setY(ECG_Ry-(ECG_Ry-60));
//        curr_state=t;
//        break;
//    case t:
//        pt.setY(ECG_Ry-((20)*sin(i*0.0174532925)));i++;
//        if(i==91)
//        {
//            i=0;
//            curr_state=p;
//        }


//        break;

//    default:
//        break;
//    }
















