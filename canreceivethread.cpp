/******************************************************************************
  文 件 名   : canreceivethread.cpp
  版 本 号   : V1.1
  作    者   : wilbur王
  生成日期   : 2023.8.7
  功能描述   :
  修改历史   :
  1.日    期   :
    作    者   :
    修改内容   :
******************************************************************************/

#include "canreceivethread.h"
#include <QDebug>

CanReceiveThread::CanReceiveThread()
{
    memset(&can_recvframe, 0x00, sizeof(can_recvframe));
    can_rx_cnt = 0;
}

void CanReceiveThread::run()
{
    S_CanFrame mCan_recvframe;
    __u8 *precvframe = (__u8 *)&mCan_recvframe;
    int can_frame_len = sizeof(S_CanFrame);
    int ret = 0;

    //qDebug("Can Bus Receive Thread Start Successfully.\n");
    for(;;)
    {
        memset(precvframe, 0x00,  can_frame_len);
        ret = can->can_recv_frame(precvframe,  can_frame_len,  5000);
        if (ret > 0)
        {
            //qDebug("can recv::: id=0x%x, data[0]=0x%x, data[1]=0x%x, data[2]=0x%x, data[3]=0x%x, data[4]=0x%x, data[5]=0x%x, data[6]=0x%x, data[7]=0x%x", mCan_recvframe.can_id & CAN_EFF_MASK, mCan_recvframe.data[0], mCan_recvframe.data[1], mCan_recvframe.data[2], mCan_recvframe.data[3], mCan_recvframe.data[4], mCan_recvframe.data[5], mCan_recvframe.data[6], mCan_recvframe.data[7]);
            this->setCan_recvframe(mCan_recvframe);
            mCan_recvframe.can_id =  mCan_recvframe.can_id & CAN_EFF_MASK;
            can_rx_cnt++;
            QVariant data;
            data.setValue(mCan_recvframe);
            emit sendcanSignal(data);

        }
    }
}

int CanReceiveThread::getCan_rx_cnt() const
{
    return can_rx_cnt;
}

CAN_Drv *CanReceiveThread::getCan() const
{
    return can;
}

void CanReceiveThread::setCan(CAN_Drv *value)
{
    can = value;
}

S_CanFrame CanReceiveThread::getCan_recvframe() const
{
    return can_recvframe;
}

void CanReceiveThread::setCan_recvframe(const S_CanFrame &value)
{
    can_recvframe = value;
}


