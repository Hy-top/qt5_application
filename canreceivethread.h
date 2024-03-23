/******************************************************************************
  文 件 名   : canreceivethread.h
  版 本 号   : V1.1
  作    者   : wilbur王
  生成日期   : 2023.8.7
  功能描述   :
  修改历史   :
  1.日    期   :
    作    者   :
    修改内容   :
******************************************************************************/

#ifndef CANRECEIVETHREAD_H
#define CANRECEIVETHREAD_H

#include<can_drv.h>
#include <QThread>
#include <QVariant>

class CanReceiveThread : public QThread
{
    Q_OBJECT

public:
     explicit CanReceiveThread();
     int can_rx_cnt;

     void run();
     CAN_Drv *getCan() const;
     void setCan(CAN_Drv *value);

     S_CanFrame getCan_recvframe() const;
     void setCan_recvframe(const S_CanFrame &value);
     int getCan_rx_cnt() const;

     int can_ch;

signals:
     void sendcanSignal(QVariant);

private:
     CAN_Drv *can;
     S_CanFrame can_recvframe;

};

#endif // CANRECEIVETHREAD_H
