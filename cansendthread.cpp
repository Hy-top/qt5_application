/******************************************************************************
  文 件 名   : cansendthread.cpp
  版 本 号   : V1.1
  作    者   : wilbur王
  生成日期   : 2023.8.7
  功能描述   :
  修改历史   :
  1.日    期   :
    作    者   :
    修改内容   :
******************************************************************************/

#include "cansendthread.h"
#include <QDebug>

unsigned int g_id_table[] = {0x001, 0x002, 0x12D, 0x191, 0x1F5, 0x259};
CanSendThread::CanSendThread():
    send_frame_id(),extended_frame(false)
{
    can_tx_flag = false;
    can_send_cnt = -1;
    //can_id = id;
    can_num = 0;
    send_frame_data = new __u8[8];
    can_send_interval = 100;
    memset(&can_sendframe, 0x00, sizeof(can_sendframe));
    memcpy(can_sendframe.data, send_frame_data, can_sendframe.can_dlc);
}

void CanSendThread::run()
{
    //qDebug("Can Bus Send thread Start Successfully.\n");
    for(;;)
    {
        if(can_tx_flag == true)
        {
            msleep(can_send_interval);

            extended_frame = false;
            send_frame_id = g_id_table[can_num];
            //send_frame_id = 0x01;
            can_sendframe.can_dlc = 8;
            if (extended_frame) // 指定发送帧类型：扩展帧或标准帧
            {
                can_sendframe.can_id = (send_frame_id & CAN_EFF_MASK) | CAN_EFF_FLAG;
            }
            else
            {
                can_sendframe.can_id = (send_frame_id & CAN_SFF_MASK);
            }

            for(quint8 i=0;i<8;i++)
            {
                send_frame_data[i]=i;
            }
            memcpy(can_sendframe.data, send_frame_data, can_sendframe.can_dlc);
            can->can_send_frame((unsigned char *)&can_sendframe, sizeof(can_sendframe), 100);
            can_send_cnt++;

            //qDebug()<<"cansend runing...";
        }
        else
        {
            sleep(1);
        }
    }
}

CAN_Drv *CanSendThread::getCan() const
{
    return can;
}

void CanSendThread::setCan(CAN_Drv *value)
{
    can = value;
}

void CanSendThread::setid(int num)
{
    can_num = num;
}

__u8 *CanSendThread::getSend_frame_data() const
{
    return send_frame_data;
}

void CanSendThread::setSend_frame_data(__u8 *value)
{
    send_frame_data = value;
}

void CanSendThread::testSendCanframe()
{
    extended_frame = true;
    send_frame_id = 0x01;
    can_sendframe.can_dlc = 8;
    if (extended_frame) // 指定发送帧类型：扩展帧或标准帧
    {
        can_sendframe.can_id = (send_frame_id & CAN_EFF_MASK) | CAN_EFF_FLAG;
    }
    else
    {
        can_sendframe.can_id = (send_frame_id & CAN_SFF_MASK);
    }
    send_frame_data[0]++;
    memcpy(can_sendframe.data, send_frame_data, can_sendframe.can_dlc);
    //qDebug("send can increase.");
    can->can_send_frame((unsigned char *)&can_sendframe, sizeof(can_sendframe), 100);
}

void CanSendThread::setCan_tx_flag(bool value)
{
    can_tx_flag = value;
}

int CanSendThread::getcan_send_cnt() const
{
    return can_send_cnt;
}

void CanSendThread::can_set_send_interval(unsigned int interval)
{
    can_send_interval = interval;
}

