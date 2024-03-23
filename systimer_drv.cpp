/******************************************************************************
  文 件 名   : systimer_drv.cpp
  版 本 号   : V1.1
  作    者   : wilbur王
  生成日期   : 2023.8.7
  功能描述   :
  修改历史   :
  1.日    期   :
    作    者   :
    修改内容   :
******************************************************************************/

#include "systimer_drv.h"
#include <QProcess>
#include <QDebug>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <qthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <QTextStream>
#include <QStringList>
#include <QFile>

sysTimer_drv::sysTimer_drv(QObject *parent) : QObject(parent)
{

}

bool sysTimer_drv::set_sysTimer(QString strTimer)
{
    QString date_str;
    date_str.sprintf("date -s '%s'", strTimer.toLatin1().data());
    system(date_str.toLatin1().data());
    system("hwclock -w");
    system("hwclock -s");

    return true;
}

/*** 返回cpu负荷率 ***/
bool sysTimer_drv::get_sysCpuload(QString &cpuload)
{
    int fd,size;
    char read_buf[200]= {0};
    ::system("top -n 1 | grep Cpu | grep -v grep | awk '{print $4}' > /oem/cpuload");

    fd= ::open("/oem/cpuload", O_RDONLY);//打开文件
    if(fd< 0)
    {
        ::close(fd);
        cpuload ="";
        return false;
    }

    //读操作
    lseek(fd, 0x0, SEEK_SET);//准备读，首先定位地址，因为前面写入的时候更新了当前文件偏移量，所以这边需要重新定位到0x40.
    if((size = read(fd, read_buf, sizeof(read_buf))) < 0)//读数据
    {
        cpuload ="";
    } else {
        QString c1;
        QString c2;
        QString c3;
        QString c4;
        QString str(read_buf);
        QStringList strlist = str.split("/");
        c1 = strlist.at(0).toLocal8Bit().data();
        c2 = strlist.at(2).toLocal8Bit().data();
        c3 = strlist.at(4).toLocal8Bit().data();
        c4 = strlist.at(6).toLocal8Bit().data();

        str  = c2;
        //str = QString::number((c1.toFloat()+c2.toFloat()+c3.toFloat()+c4.toFloat()));
        cpuload = str;
    }
    ::close(fd);
    return  true;
}

QString sysTimer_drv::get_syscpu()
{
    QString c1;
    ::system("top -n 1 | grep Cpu | grep -v grep | awk '{print $4}' > /oem/cpuload");

    QFile file("/oem/cpuload");
    if(!file.open(QIODevice::ReadOnly))
    {
        return "failed";
    }
    QByteArray destData = file.readAll();
    QString a = QString(destData);
    QStringList strlist = a.split("/");
    c1 = strlist.at(0).toLocal8Bit().data();

    return c1;
}
