/******************************************************************************
  文 件 名   : filerw.cpp
  版 本 号   : V1.1
  作    者   : wilbur王
  生成日期   : 2023.8.7
  功能描述   :
  修改历史   :
  1.日    期   :
    作    者   :
    修改内容   :
******************************************************************************/

#include "filerw.h"
#include "ui_filerw.h"
#include <QMessageBox>

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

const char *device = "/dev/input/event1";
int fd = 0;
struct input_event ev;
int touchCount = 0;

FileRw::FileRw(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileRw)
{
    ui->setupUi(this);

    stress_ram = 0;
    restart_count();
    g_mThread = new mThread(this);
    g_mThread->start();
    connect(g_mThread, SIGNAL(setfile_error_cnt(int)), this, SLOT(file_errorSlot(int)));

    myTimer = new QTimer(this);
    connect(myTimer, SIGNAL(timeout()), this, SLOT(myTimerUpdate()));
    myTimer->start(300);

    //----设置背景图片----//
    QPalette palette;
    QPixmap pixmap(":/image/main_menu/background2.png");
    palette.setBrush(backgroundRole(),QBrush(pixmap));
    setPalette(palette);
    setAutoFillBackground(true);


    fd = open(device,O_RDONLY);
    if(fd == 1)
    {
        perror("Failed to open input device");
        return;
    }
}

FileRw::~FileRw()
{
    delete ui;
}

void FileRw::on_closeBtn_clicked()
{
    this->close();
}

void FileRw::file_errorSlot(int file_cnt)
{
    ui->file_error_lab->setText("错误次数:" + QString::number(file_cnt));
}

void FileRw::on_file_rw_Btn_clicked()
{
    if(g_write_file_test == 1)
    {
        g_write_file_test = 0;
        ui->file_rw_Btn->setText("Start");
    }
    else
    {
        g_write_file_test = 1;
        ui->file_rw_Btn->setText("Stop");
    }

    g_mThread->set_file_test_enable(g_write_file_test);
}

/*** 用于定时器更新的服务函数 ***/
void FileRw::myTimerUpdate()
{

    /*** show system time ***/
    QDateTime curr_time = QDateTime::currentDateTime();

    QString dis_hour = curr_time.toString("hh:mm");
    ui->time_dis_lab->setText(dis_hour);

    QLocale locale = QLocale::Chinese;
    QString strformat = "yyyy.MM.dd ddd";
    QString strDatetime = locale.toString(curr_time,strformat);
    ui->time_dis_lab->setText(strDatetime);

    /*----CPU tem----*/
    bool ret;
    QByteArray line;

    QFile flashfile("/sys/class/thermal/thermal_zone0/temp");
    ret = flashfile.open(QIODevice::ReadOnly | QIODevice::Text);

    if(ret)
    {
        line = flashfile.readAll();
        flashfile.close();
        int m_tem = line.toInt();
        m_tem = m_tem/1000;
        ui->cpu_tem->setText("CPU温度:" + QString::number(m_tem).remove("\n") +"℃");
    }

}

void FileRw::restart_count()
{
    int cnt = 0;
    QFile start_cnt_file("/oem/developer/testapp/restart_cnt.txt");

    if(start_cnt_file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QByteArray data = start_cnt_file.readAll();
        bool ok;

        if(data.length() > 0)
        {
            cnt = QString(data.data()).toInt(&ok, NULL);
        }

        cnt++;
        ui->restart_lab->setText(QString::number(cnt));
        QString cnt_str = QString::number(cnt);
        start_cnt_file.seek(0);
        start_cnt_file.write(cnt_str.toLatin1());
        start_cnt_file.close();
        system("sync");
    }

}

void FileRw::on_Cpu_Btn_clicked()
{
    if(stress_ram == 1)
    {
        stress_ram = 0;
    }
    else
    {
        stress_ram = 1;
        system("./taskset -c 0 stress -c 1 &");
        system("./taskset -c 1 stress -c 1 &");
//        system("./taskset -c 2 stress -c 1 &");
//        system("./taskset -c 3 stress -c 1 &");
        ui->Cpu_Btn->setEnabled(false);
        QMessageBox::information(NULL, tr("提示"), tr("CPU负载已60%"));
    }


//    system("taskset -c 0 stress --vm 1 --vm-bytes 128M --vm-hang 0 &");
//    system("taskset -c 1 stress --vm 1 --vm-bytes 128M --vm-hang 0 &");
}

