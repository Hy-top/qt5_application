/******************************************************************************
  文 件 名   : cansendthread.h
  版 本 号   : V1.1
  作    者   : wilbur王
  生成日期   : 2023.8.7
  功能描述   :
  修改历史   :
  1.日    期   :
    作    者   :
    修改内容   :
******************************************************************************/

#ifndef CANSENDTHREAD_H
#define CANSENDTHREAD_H

#include<can_drv.h>
#include <QThread>
#include <QTimer>

class CanSendThread : public QThread
{
     Q_OBJECT

public:
    CanSendThread();
    void run();

    int can_send_cnt;
    CAN_Drv *getCan() const;
    void setCan(CAN_Drv *value);
    void setid(int num);

    __u8 *getSend_frame_data() const;
    void setSend_frame_data(__u8 *value);
    void testSendCanframe();
    void setCan_tx_flag(bool value);
    int getcan_send_cnt() const;
    void can_set_send_interval(unsigned int interval);

protected:

private:
    CAN_Drv *can;
    QTimer *m_pTimer;
    S_CanFrame can_sendframe;
    __u8* send_frame_data;
    unsigned int send_frame_id;
    bool extended_frame;
    bool can_tx_flag;
    __u32 can_id;
    unsigned int can_send_interval;
    int can_num;
};

#endif // CANSENDTHREAD_H
