/******************************************************************************
  文 件 名   : colortest.cpp
  版 本 号   : V1.1
  作    者   : wilbur王
  生成日期   : 2023.8.7
  功能描述   :
  修改历史   :
  1.日    期   :
    作    者   :
    修改内容   :
******************************************************************************/

#include "colortest.h"
#include "ui_colortest.h"
#include <QDebug>

int i;
ColorTest::ColorTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorTest)
{
    ui->setupUi(this);

    m_timer = new QTimer();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(timer_handle()));
    i = 1;
    //setAttribute(Qt::WA_DeleteOnClose); //关闭窗口，释放资源

    myTimer = new QTimer(this);
    connect(myTimer, SIGNAL(timeout()), this, SLOT(myTimerUpdate()));
    myTimer->start(300);

    //----设置背景图片----//
    QPalette palette;
    QPixmap pixmap(":/image/main_menu/background2.png");
    palette.setBrush(backgroundRole(),QBrush(pixmap));
    setPalette(palette);
    setAutoFillBackground(true);
}

ColorTest::~ColorTest()
{
    delete ui;
    delete m_timer;
}

char l_c8Command[128] = {0};
void ColorTest::timer_handle()
{
    if(i>8)
    {
        QThread::sleep(3);
        i = 0;
    }
    sprintf(l_c8Command, "border-image:url(:/image/%d.png)", i);
    QString str(l_c8Command);
   // qDebug()<<"str:"<<str;
    ui->label_12->setStyleSheet(str);
    i++;
}

/*** 用于定时器更新的服务函数 ***/
void ColorTest::myTimerUpdate()
{

    /*** show system time ***/
    QDateTime curr_time = QDateTime::currentDateTime();

    QString dis_hour = curr_time.toString("hh:mm");
    ui->time_dis_lab->setText(dis_hour);

    QLocale locale = QLocale::Chinese;
    QString strformat = "yyyy.MM.dd ddd";
    QString strDatetime = locale.toString(curr_time,strformat);
    ui->time_dis_lab->setText(strDatetime);
}

void ColorTest::on_close_Btn_clicked()
{
    this->close();
}

void ColorTest::on_run_Btn_clicked()
{
    if(!run_flag)
    {
        ui->run_Btn->setText("关闭颜色测试");
        run_flag = true;
        m_timer->start(1000);
    }else {
        ui->run_Btn->setText("启动颜色测试");
        run_flag = false;
        m_timer->stop();
    }
}
