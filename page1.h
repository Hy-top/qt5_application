/******************************************************************************
  文 件 名   : page1.h
  版 本 号   : V1.1
  作    者   : wilbur王
  生成日期   : 2023.8.7
  功能描述   :
  修改历史   :
  1.日    期   :
    作    者   :
    修改内容   :
******************************************************************************/

#ifndef PAGE1_H
#define PAGE1_H

#include <QWidget>
#include "canreceivethread.h"
#include "cansendthread.h"
#include <QVariant>
#include <QTimer>
#include <QDateTime>
#include <QProcess>

namespace Ui {
class page1;
}

class page1 : public QWidget
{
    Q_OBJECT

public:
    explicit page1(QWidget *parent = 0);
    ~page1();
    void read_can_send_cnt();
    void can0_init();
    void can1_init();

public slots:
    void setcan1Slot(QVariant data);
    void setcan2Slot(QVariant data);
    void timer_handle(void);

signals:
    void sendcanUpdate(char *);

protected slots:
    void myTimerUpdate(void);

private slots:
    void on_closeBtn_clicked();

    void on_can1cleanBtn_clicked();

    void on_can2cleanBtn_clicked();

    void on_can1sendBtn_clicked();

    void on_can2sendBtn_clicked();

    void on_can1sendclearBtn_clicked();

    void on_can2sendclearBtn_clicked();

    void on_button_can_send_interval_clicked();

    void on_comboBox_can0_set_currentIndexChanged(int index);

    void on_comboBox_can1_set_currentIndexChanged(int index);


private:
    Ui::page1 *ui;

    // canbus - can0
    CAN_Drv* mCan1;
    CanSendThread* mCan1SendThread;
    CanReceiveThread* mCan1ReceiveThread;

    // canbus - can1
    CAN_Drv* mCan2;
    CanSendThread* mCan2SendThread;
    CanReceiveThread* mCan2ReceiveThread;
    QTimer *m_pTimer;
    QTimer *myTimer;
    QProcess m_process;

    QString can0_cmd;
    QString running_flag;

    QString can0_name;
    QString can1_name;

    bool can0_time_flag;
    bool can1_time_flag;

    bool can0_run_flag;
    bool can1_run_flag;

    uint32_t can0_Bitrate;
    uint32_t can1_Bitrate;

    uint32_t can_send_interval;
    char update[12] = {0};
    //Update *m_update;
};

#endif // PAGE1_H
