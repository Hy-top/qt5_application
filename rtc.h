/******************************************************************************
  文 件 名   : rtc.h
  版 本 号   : V1.1
  作    者   : wilbur王
  生成日期   : 2023.8.7
  功能描述   :
  修改历史   :
  1.日    期   :
    作    者   :
    修改内容   :
******************************************************************************/

#ifndef RTC_H
#define RTC_H

#include <QWidget>
#include <QTimer>
#include <QDateTime>
#include "systimer_drv.h"

namespace Ui {
class Rtc;
}

class Rtc : public QWidget
{
    Q_OBJECT

public:
    explicit Rtc(QWidget *parent = 0);
    ~Rtc();

protected slots:
    void myTimerUpdate(void);

private slots:
    void on_close_Btn_clicked();

    void on_pushButton_setTimer_clicked();

private:
    Ui::Rtc *ui;
    QTimer *myTimer;
    /*** 系统时间设置相关 ***/
    sysTimer_drv *m_sysTimer_drv;
};

#endif // RTC_H
