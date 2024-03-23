/******************************************************************************
  文 件 名   : page1.cpp
  版 本 号   : V1.1
  作    者   : wilbur王
  生成日期   : 2023.8.7
  功能描述   :
  修改历史   :
  1.日    期   :
    作    者   :
    修改内容   :
******************************************************************************/

#include "page1.h"
#include "ui_page1.h"
#include <qdebug.h>
#include <QFile>
#include "flatui.h"
#include <QMessageBox>

bool can1_tx_toggle = false;
bool can2_tx_toggle = false;

page1::page1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::page1)
{
    ui->setupUi(this);

    can0_time_flag = false;
    can1_time_flag = false;

    can0_Bitrate = 250000;
    can1_Bitrate = 250000;

    can0_run_flag = false;
    can1_run_flag = false;

    can0_name = "can0";
    can1_name = "can1";
    running_flag = "RUNNING";

    //m_update = new Update();

    can_send_interval = 100;
    ui->comboBox_can0_set->addItem("250K");
    ui->comboBox_can0_set->addItem("500K");
    ui->comboBox_can1_set->addItem("250K");
    ui->comboBox_can1_set->addItem("500K");
   // ui->comboBox_can1_set->addItems(QStringList()<<"250K"<<"500K");

    myTimer = new QTimer(this);
    connect(myTimer, SIGNAL(timeout()), this, SLOT(myTimerUpdate()));
    myTimer->start(300);

    m_pTimer = new QTimer();
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(timer_handle()));
    m_pTimer->start(300);

    ui->can1sendLab->setText("0");
    ui->can2sendLab->setText("0");


    //---美化---//
    FlatUI::setPushButtonQss0(ui->can1sendBtn);
    FlatUI::setPushButtonQss0(ui->can1sendclearBtn);
    FlatUI::setPushButtonQss0(ui->can2sendBtn);
    FlatUI::setPushButtonQss0(ui->can2sendclearBtn);
    FlatUI::setPushButtonQss0(ui->button_can_send_interval);
    FlatUI::setPushButtonQss0(ui->can1cleanBtn);
    FlatUI::setPushButtonQss0(ui->can2cleanBtn);

    //----设置背景图片----//
    QPalette palette;
    QPixmap pixmap(":/image/main_menu/background2.png");
    palette.setBrush(backgroundRole(),QBrush(pixmap));
    setPalette(palette);
    setAutoFillBackground(true);
    //m_update = new Update();
}

page1::~page1()
{
    delete ui;
    delete mCan2SendThread;
    delete mCan2ReceiveThread;
    delete m_pTimer;
    delete mCan2;
}

void page1::timer_handle(void)
{
    m_process.setReadChannel(QProcess::StandardOutput);

    m_process.start("ifconfig -a");
    m_process.waitForFinished();
    can0_cmd = m_process.readAllStandardOutput();

    if (can0_cmd.contains(can0_name))
    {
        can0_time_flag = true;
    }
    if (can0_cmd.contains(can1_name))
    {
        can1_time_flag = true;
    }

    if(can1_time_flag != false || can0_time_flag != false)
    {
        if(can0_time_flag == true &&  can0_run_flag == false)
        {
            can0_init();
        }
        if(can1_time_flag == true &&  can1_run_flag == false )
        {
            can1_init();
        }
    }

    m_process.start("ifconfig can0");
    m_process.waitForFinished();
    can0_cmd = m_process.readAllStandardOutput();

    if (can0_cmd.contains(running_flag))
    {
        //qDebug()<<"can0 runnging";
        can0_run_flag = true;
    }else{
        qDebug()<<"can0 stop";
        can0_run_flag = false;
//        QMessageBox::information(NULL, tr("警告"), tr("未检测到CAN0，请检查硬件"));
//        return;
    }

    m_process.start("ifconfig can1");
    m_process.waitForFinished();
    can0_cmd = m_process.readAllStandardOutput();

    if (can0_cmd.contains(running_flag))
    {
        // qDebug()<<"can1 runnging";
         can1_run_flag = true;
    }else
    {
         qDebug()<<"can1 stop";
         can1_run_flag = false;
//         QMessageBox::information(NULL, tr("警告"), tr("未检测到CAN1，请检查硬件"));
//         return;
    }

    if(can0_time_flag)
    {
        ui->can1len->setText(QString::number(mCan1ReceiveThread->getCan_rx_cnt()));
        if(mCan1SendThread->getcan_send_cnt() < 0)
        {
            ui->can1sendLab->setText("0");
        }else{
            ui->can1sendLab->setText(QString::number(mCan1SendThread->getcan_send_cnt()));
        }

        if(can0_run_flag == false )
        {

        }

    }

    if(can1_time_flag){
        ui->can2len->setText(QString::number(mCan2ReceiveThread->getCan_rx_cnt()));

        if(mCan2SendThread->getcan_send_cnt() < 0)
        {
            ui->can2sendLab->setText("0");
        }else{
            ui->can2sendLab->setText(QString::number(mCan2SendThread->getcan_send_cnt()));
        }

        if(can1_run_flag == false )
        {

        }

    }


}

void page1::setcan1Slot(QVariant data)
{
    S_CanFrame frame = data.value<S_CanFrame>();
    ui->can0_id->setText("CAN1接收:0x" + QString::number((unsigned char)frame.can_id,16).toUpper().rightJustified(2,QChar('0')));
    ui->can0_id->setText("CAN1接收:0x" + QString::number(frame.can_id,16));
    ui->date0->setText(QString::number(frame.data[0],16).toUpper().rightJustified(2,QChar('0')));
    ui->date1->setText(QString::number(frame.data[1],16).toUpper().rightJustified(2,QChar('0')));
    ui->date2->setText(QString::number(frame.data[2],16).toUpper().rightJustified(2,QChar('0')));
    ui->date3->setText(QString::number(frame.data[3],16).toUpper().rightJustified(2,QChar('0')));
    ui->date4->setText(QString::number(frame.data[4],16).toUpper().rightJustified(2,QChar('0')));
    ui->date5->setText(QString::number(frame.data[5],16).toUpper().rightJustified(2,QChar('0')));
    ui->date6->setText(QString::number(frame.data[6],16).toUpper().rightJustified(2,QChar('0')));
    ui->date7->setText(QString::number(frame.data[7],16).toUpper().rightJustified(2,QChar('0')));

    if(frame.can_id == 0x18FF7658)
    {
        qDebug()<<"0x18ff7658";
        snprintf(update,12,"%02x%02x%02x%02x",frame.data[0],frame.data[1],frame.data[2],frame.data[3]);
        emit sendcanUpdate(update);
    }
}

void page1::setcan2Slot(QVariant data)
{
    S_CanFrame frame = data.value<S_CanFrame>();
   ui->can1_id->setText("CAN2接收:0x" + QString::number((unsigned char)frame.can_id,16).toUpper().rightJustified(2,QChar('0')));
    ui->can1_id->setText("CAN2接收:0x" + QString::number(frame.can_id,16));
    ui->data8->setText(QString::number(frame.data[0],16).toUpper().rightJustified(2,QChar('0')));
    ui->data9->setText(QString::number(frame.data[1],16).toUpper().rightJustified(2,QChar('0')));
    ui->data10->setText(QString::number(frame.data[2],16).toUpper().rightJustified(2,QChar('0')));
    ui->data11->setText(QString::number(frame.data[3],16).toUpper().rightJustified(2,QChar('0')));
    ui->data12->setText(QString::number(frame.data[4],16).toUpper().rightJustified(2,QChar('0')));
    ui->data13->setText(QString::number(frame.data[5],16).toUpper().rightJustified(2,QChar('0')));
    ui->data14->setText(QString::number(frame.data[6],16).toUpper().rightJustified(2,QChar('0')));
    ui->data15->setText(QString::number(frame.data[7],16).toUpper().rightJustified(2,QChar('0')));
}

void page1::on_closeBtn_clicked()
{
    this->close();
}

void page1::on_can1cleanBtn_clicked()
{
    if(can0_time_flag == true)
    {
        mCan1ReceiveThread->can_rx_cnt = 0;
    }
}

void page1::on_can2cleanBtn_clicked()
{
    if(can1_time_flag == true)
    {
        mCan2ReceiveThread->can_rx_cnt = 0;
     }
}

void page1::on_can1sendBtn_clicked()
{
//    QMessageBox::information(NULL, tr("提示"), tr("CAN1暂不使用"));
    if(can0_time_flag == true)
    {
        if(can1_tx_toggle == false)
        {
            mCan1SendThread->setCan_tx_flag(true);
            can1_tx_toggle = true;
            ui->can1sendBtn->setText(QString("CAN1停止"));
        }
        else
        {
            mCan1SendThread->setCan_tx_flag(false);
            can1_tx_toggle = false;
            ui->can1sendBtn->setText(QString("CAN1发送"));
        }
     }
}

void page1::on_can2sendBtn_clicked()
{
    if(can1_time_flag == true)
    {
        if(can2_tx_toggle == false)
        {
            mCan2SendThread->setCan_tx_flag(true);
            can2_tx_toggle = true;
            ui->can2sendBtn->setText(QString("CAN2停止"));
        }
        else
        {
            mCan2SendThread->setCan_tx_flag(false);
            can2_tx_toggle = false;
            ui->can2sendBtn->setText(QString("CAN2发送"));
        }
    }
}

void page1::on_can1sendclearBtn_clicked()
{
    if(can0_time_flag == true)
    {
        mCan1SendThread->can_send_cnt = 0;
    }
}

void page1::on_can2sendclearBtn_clicked()
{
    if(can1_time_flag == true)
    {
         mCan2SendThread->can_send_cnt = 0;
    }
}

void page1::read_can_send_cnt()
{
    bool ret;
    QByteArray line;

    QFile flashfile("/oem/developer/can0send");
    ret = flashfile.open(QIODevice::ReadOnly | QIODevice::Text);

    if(ret)
    {
        line = flashfile.readAll();
        flashfile.close();
        ui->can1sendLab->setText(QString(line).remove("\n"));

    }

    QFile flashfile1("/oem/developer/can1send");
    ret = flashfile1.open(QIODevice::ReadOnly | QIODevice::Text);

    if(ret)
    {
        line = flashfile1.readAll();
        flashfile1.close();
        ui->can2sendLab->setText(QString(line).remove("\n"));
    }

}


void page1::on_button_can_send_interval_clicked()
{

    switch(can_send_interval)
    {
    case 1:
        can_send_interval = 2;
        break;

    case 2:
        can_send_interval = 5;
        break;

    case 5:
        can_send_interval = 10;
        break;

    case 10:
        can_send_interval = 100;
        break;

    case 100:
        can_send_interval = 1;
        break;

    default:
        can_send_interval = 1;
        break;
    }

    if(can0_time_flag == true)
    {
        mCan1SendThread->can_set_send_interval(can_send_interval);
    }

    if(can1_time_flag == true)
    {
        mCan2SendThread->can_set_send_interval(can_send_interval);
    }

    ui->label_can_send_interval->setText(QString::number(can_send_interval) + "ms");
}

void page1::on_comboBox_can0_set_currentIndexChanged(int index)
{
   // QMessageBox::information(NULL, tr("提示"), tr("CAN1暂不使用"));
    int bt[2] = {250000, 500000};

    if(index >= (sizeof(bt) / sizeof(bt[0])))
    {
        index = 0;
    }
    if(can0_time_flag == true){
        can0_Bitrate = bt[index];
        mCan1->setCanBitrate(0, bt[index]);
    }
}

void page1::on_comboBox_can1_set_currentIndexChanged(int index)
{
    int bt[2] = {250000, 500000};

    if(index >= (sizeof(bt) / sizeof(bt[0])))
    {
        index = 0;
    }
    if(can1_time_flag == true){
        can1_Bitrate = bt[index];
        mCan2->setCanBitrate(1, bt[index]);
    }
}

/*** 用于定时器更新的服务函数 ***/
void page1::myTimerUpdate()
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

void page1::can0_init()
{
    mCan1 = new CAN_Drv(this, 0, can0_Bitrate); //can0 channel  250kbit/s
    mCan1->setCanBitrate(0,can0_Bitrate);

    mCan1SendThread = new CanSendThread();
    mCan1SendThread->setCan(mCan1);
    mCan1SendThread->setid(0);

    mCan1SendThread->start(QThread::HighestPriority);
    mCan1SendThread->can_set_send_interval(can_send_interval);

    mCan1ReceiveThread = new CanReceiveThread();
    mCan1ReceiveThread->setCan(mCan1);
    connect(mCan1ReceiveThread, SIGNAL(sendcanSignal(QVariant)), this, SLOT(setcan1Slot(QVariant)));
    mCan1ReceiveThread->start();
}

void page1::can1_init()
{
    mCan2 = new CAN_Drv(this, 1, can1_Bitrate); //can1 channel  250kbit/s
    mCan2->setCanBitrate(1,can1_Bitrate);

    mCan2SendThread = new CanSendThread();
    mCan2SendThread->setCan(mCan2);
    mCan2SendThread->setid(1);

    //mCan2SendThread->can_set_send_interval(can_send_interval);

    //qDebug()<<"send_end";
    mCan2ReceiveThread = new CanReceiveThread();
    mCan2ReceiveThread->setCan(mCan2);
    connect(mCan2ReceiveThread, SIGNAL(sendcanSignal(QVariant)), this, SLOT(setcan2Slot(QVariant)));
    mCan2ReceiveThread->start();

    mCan2SendThread->can_set_send_interval(can_send_interval);
    mCan2SendThread->start();
}

