/******************************************************************************
  文 件 名   : rtc.cpp
  版 本 号   : V1.1
  作    者   : wilbur王
  生成日期   : 2023.8.7
  功能描述   :
  修改历史   :
  1.日    期   :
    作    者   :
    修改内容   :
******************************************************************************/

#include "rtc.h"
#include "ui_rtc.h"
#include <QMessageBox>
#include <QDebug>

Rtc::Rtc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Rtc)
{
    ui->setupUi(this);
    //----设置背景图片----//
    QPalette palette;
    QPixmap pixmap(":/image/main_menu/background2.png");
    palette.setBrush(backgroundRole(),QBrush(pixmap));
    setPalette(palette);
    setAutoFillBackground(true);

    m_sysTimer_drv = new sysTimer_drv();
    myTimer = new QTimer(this);
    connect(myTimer, SIGNAL(timeout()), this, SLOT(myTimerUpdate()));
    myTimer->start(1000);
}

Rtc::~Rtc()
{
    delete ui;
}

/*** 用于定时器更新的服务函数 ***/
void Rtc::myTimerUpdate()
{

    /*** show system time ***/
    QDateTime curr_time = QDateTime::currentDateTime();

//    QString dis_hour = curr_time.toString("hh:mm");
//    ui->time_dis_lab->setText(dis_hour);

    QLocale locale = QLocale::Chinese;
    QString strformat = "yyyy.MM.dd ddd";
    QString strDatetime = locale.toString(curr_time,strformat);
    ui->time_dis_lab->setText(strDatetime);

    QString y_lab = curr_time.toString("yyyy");
    ui->y_label->setText(y_lab);
    QString m_lab = curr_time.toString("MM");
    ui->m_label->setText(m_lab);
    QString d_lab = curr_time.toString("dd");
    ui->d_label->setText(d_lab);
    QString h_lab = curr_time.toString("hh");
    ui->h_label->setText(h_lab);
    QString min_lab = curr_time.toString("mm");
    ui->min_label->setText(min_lab);
    QString sec_lab = curr_time.toString("ss");
    ui->sec_label->setText(sec_lab);
 //   qDebug()<<"rtc runing...";
}

void Rtc::on_close_Btn_clicked()
{
    this->close();
}

void Rtc::on_pushButton_setTimer_clicked()
{
    /***---------set time-----------***/
    QString setTime = ui->yEdit->text() + "-" + ui->mEdit->text() + "-" + \
            ui->dEdit->text() + " " + ui->hEdit->text() + ":" + ui->minEdit->text() + ":" + ui->SecEdit->text();
    bool tmp = m_sysTimer_drv->set_sysTimer(setTime);
    if(tmp == true) {
        QMessageBox::information(NULL, tr("提示"), tr("时间设置成功！"));
    } else {
        QMessageBox::information(NULL, tr("提示"), tr("时间设置失败！"));
    }
}
