/******************************************************************************
  文 件 名   : music.cpp
  版 本 号   : V1.1
  作    者   : wilbur王
  生成日期   : 2023.8.7
  功能描述   :
  修改历史   :
  1.日    期   :
    作    者   :
    修改内容   :
******************************************************************************/

#include "music.h"
#include "ui_music.h"

Music::Music(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Music)
{
    ui->setupUi(this);
    vol_val = 50;

    mAudio_drv = new audio_drv();
    myTimer = new QTimer(this);
    connect(myTimer, SIGNAL(timeout()), this, SLOT(myTimerUpdate()));
    myTimer->start(300);

    mAudio_drv->set_audio_volume(vol_val+27);

    //----设置背景图片----//
    QPalette palette;
    QPixmap pixmap(":/image/main_menu/background2.png");
    palette.setBrush(backgroundRole(),QBrush(pixmap));
    setPalette(palette);
    setAutoFillBackground(true);

    ui->label_15->hide();
    ui->label_vol->hide();
    ui->pushButton_vol_sub->hide();
    ui->pushButton_vol_add->hide();
    ui->pushButton_start_playback->hide();
    ui->pushButton_stop_playback->hide();
    ui->label->hide();
    ui->label_31->hide();
}

Music::~Music()
{
    delete ui;
}

/*** 用于定时器更新的服务函数 ***/
void Music::myTimerUpdate()
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

void Music::on_pushButton_start_playback_clicked()
{
    set_fm_audio_state(0);
    mAudio_drv->aplay_music("/oem/developer/test_44100_one_day.wav &");
}

void Music::on_pushButton_stop_playback_clicked()
{
    ::system("killall aplay");
}

void Music::on_pushButton_vol_add_clicked()
{
    if(vol_val < 100)
    {
        vol_val += 10;
        mAudio_drv->set_audio_volume(vol_val+27);
        ui->label_vol->setText(QString::number(vol_val)+"%");
    }
}

void Music::on_pushButton_vol_sub_clicked()
{
    if(vol_val > 0)
    {
        vol_val -= 10;
        if(vol_val<10)
        {
            vol_val = 10;
        }
        mAudio_drv->set_audio_volume(vol_val+27);
        ui->label_vol->setText(QString::number(vol_val)+"%");
    }
}

void Music::on_pushButton_btExit_clicked()
{
    this->close();
}

void Music::on_beep_Btn_clicked()
{
    if(!beep_flag)
    {
        set_beep_state(1);
        ui->beep_Btn->setText("关闭蜂鸣器");
        beep_flag = true;
    }
    else
    {
        beep_flag = false;
        set_beep_state(0);
        ui->beep_Btn->setText("打开蜂鸣器");
    }
}
