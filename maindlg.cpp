/******************************************************************************
  文 件 名   : maindlg.cpp
  版 本 号   : V1.1
  作    者   : wilbur王
  生成日期   : 2023.8.7
  功能描述   :
  修改历史   :
  1.日    期   :
    作    者   :
    修改内容   :
******************************************************************************/

#include "maindlg.h"
#include "ui_maindlg.h"
#include <stdio.h>
#include <stdlib.h>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QTextCodec>
#include "flatui.h"



MainDlg::MainDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDlg)
{
    ui->setupUi(this);

    myTimer = new QTimer(this);
    connect(myTimer, SIGNAL(timeout()), this, SLOT(myTimerUpdate()));
    myTimer->start(300);

    /***---实例化---***/
    page_1 = new page1();
    m_color = new ColorTest();
    page_rtc = new Rtc();
    page_autoimg = new AutoImage();
    page_touch = new Touch();
}

MainDlg::~MainDlg()
{
    delete ui;
}


/*** 用于定时器更新的服务函数 ***/
void MainDlg::myTimerUpdate()
{
    /*** show system time ***/
    QDateTime curr_time = QDateTime::currentDateTime();
    QString dis_hour = curr_time.toString("hh:mm");
    ui->time_dis_lab->setText(dis_hour);

    QLocale locale = QLocale::Chinese;
    QString strformat = "yyyy.MM.dd ddd";
    QString strDatetime = locale.toString(curr_time,strformat);
    ui->time2_dis_lab->setText(strDatetime);
    ui->time3_dis_lab->setText(strDatetime);
}


void MainDlg::on_touch_Btn_clicked()
{
    page_touch->show();
}

void MainDlg::on_FM_Btn_clicked()
{
    QMessageBox::information(NULL, tr("提示"), tr("功能暂未实现"));
}

void MainDlg::on_bt_Btn_clicked()
{
   QMessageBox::information(NULL, tr("提示"), tr("功能暂未实现"));
}

void MainDlg::on_color_btn_clicked()
{
    m_color->show();
}

void MainDlg::on_AHD_Btn_clicked()
{
   QMessageBox::information(NULL, tr("提示"), tr("功能暂未实现"));
}

void MainDlg::on_WiFi_Btn_clicked()
{
   QMessageBox::information(NULL, tr("提示"), tr("功能暂未实现"));
}

void MainDlg::on_File_Btn_clicked()
{
    QMessageBox::information(NULL, tr("提示"), tr("功能暂未实现"));
}

void MainDlg::on_time_Btn_clicked()
{
    page_rtc->show();
}

void MainDlg::on_SN_Btn_clicked()
{
    QMessageBox::information(NULL, tr("提示"), tr("功能暂未实现"));
}

void MainDlg::on_face_Btn_clicked()
{
    QMessageBox::information(NULL, tr("提示"), tr("功能暂未实现"));
}

void MainDlg::on_ahd2_Btn_clicked()
{
    QMessageBox::information(NULL, tr("提示"), tr("功能暂未实现"));
}

void MainDlg::on_voice_Btn_clicked()
{
    QMessageBox::information(NULL, tr("提示"), tr("功能暂未实现"));
}

void MainDlg::on_health_Btn_clicked()
{
    page_autoimg->show();
}

void MainDlg::on_backlight_Btn_clicked()
{
    QMessageBox::information(NULL, tr("提示"), tr("功能暂未实现"));
}

void MainDlg::on_warn_Btn_clicked()
{
    QMessageBox::information(NULL, tr("提示"), tr("功能暂未实现"));
}

void MainDlg::on_app_Btn_clicked()
{
    QMessageBox::information(NULL, tr("提示"), tr("功能暂未实现"));
}

void MainDlg::on_fm3_Btn_clicked()
{
    QMessageBox::information(NULL, tr("提示"), tr("功能暂未实现"));
}

void MainDlg::on_video2_Btn_clicked()
{
    QMessageBox::information(NULL, tr("提示"), tr("功能暂未实现"));
}

void MainDlg::on_bt2_Btn_clicked()
{
    QMessageBox::information(NULL, tr("提示"), tr("功能暂未实现"));
}

void MainDlg::on_map_Btn_clicked()
{
    QMessageBox::information(NULL, tr("提示"), tr("功能暂未实现"));
}

void MainDlg::on_Set_Btn_clicked()
{
    QMessageBox::information(NULL, tr("提示"), tr("功能暂未实现"));
}

void MainDlg::on_Music_Btn_clicked()
{
    QMessageBox::information(NULL, tr("提示"), tr("功能暂未实现"));
}

void MainDlg::on_canBtn_clicked()
{
    page_1->show();
}
