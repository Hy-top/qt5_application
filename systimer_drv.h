/******************************************************************************
  文 件 名   : systimer_drv.h
  版 本 号   : V1.1
  作    者   : wilbur王
  生成日期   : 2023.8.7
  功能描述   :
  修改历史   :
  1.日    期   :
    作    者   :
    修改内容   :
******************************************************************************/

#ifndef SYSTIMER_DRV_H
#define SYSTIMER_DRV_H

#include <QObject>

class sysTimer_drv : public QObject
{
    Q_OBJECT
public:
    explicit sysTimer_drv(QObject *parent = 0);

signals:

public:
    /*** 设置系统时间 ***/
    bool set_sysTimer(QString strTimer);

    /*** 返回cpu负荷率 ***/
    bool get_sysCpuload(QString& cpuload);
    QString get_syscpu();
};

#endif // SYSTIMER_DRV_H
